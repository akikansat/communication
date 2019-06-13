#include <SoftwareSerial.h>
 
SoftwareSerial tkdport(8,9);
 char date ;
String s;
int k = 0;          ///まじで疲れた．．．
int n = 0;

void setup(){ 
  Serial.begin(19200);
  tkdport.begin(19200);
  Serial.println("Conneted");
  Serial.println("コマンドは下記URL第5章を参照してください");
  Serial.println("http://www.circuitdesign.jp/jp/products/EOL/doc/MU2_429_v1.pdf");
  Serial.println("簡易送信コマンド一覧(全てのコマンドの最後に必ず';'をつけてください.';'をつけなければならないのはこのプログラムだけの話です.付け忘れたら';'だけ打てば直ります.)");
  Serial.println("ユーザ ID 設定\n@UI XXXX,XXXX\n\nグループ ID 設定\n@GI XX\n\n機器 ID 設定\n@EI XX\n\n目的局 ID 指定\n@DI XX\n\n使用チャンネル設定\n@CH XX\n\nデータ送信コマンド\n@DT+'データサイズ'+'データ'\n(例)@DT09AMANOGAWA;(送信後に*DT=09がレスポンスされる) 受信機側には*DR=09AMANOGAWAと受信されます.\n最後に'/A'をつけると相手から受信確認通知として送信機が'*DR=00'を受信します.\n");
  Serial.println("==重要==");
  Serial.println("TXはD9ピン, RXはD8ピンになっています.\n");
}
 
void loop() { 
int i;
  char terminal[2]= {'\r','\n'};
  char c;

  if(tkdport.available()){
  
  if(n == 0)
  Serial.print("\n受信");
  else if(n != 0)
  Serial.print("\n送信 : ");
  Serial.println(s);

    s = '\r';
  n = 0;

  }
  while(tkdport.available()){
  c = tkdport.read();
 
   Serial.print( c );

}

if (Serial.available()) {
              while(Serial.available()){
                
                date = Serial.read();
              
            
               

           if(date != ';')
             s += date;
             
           if(date == ';'){
             k = 1;
             
             break;
             }
              
             }
          }
                              


             
             if(k ==1){
       
           n = 725;
                tkdport.print(s);
                

for(i=0;i<2;i++){          //必要
  tkdport.write(terminal[i]);   //必要
  }                          //必要

                
                k = 0;
          
                }

      Serial.flush();
  
 delay(100);
}



