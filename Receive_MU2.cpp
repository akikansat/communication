/**
*@author TakedaShinji
*@dateで2019/07/01
**/

#include "mbed.h"
#include "stdint.h"
#include <string.h>
#include <stdio.h>

/**
*引数の文字列と同じ文字列を受信したら返り値0を返す関数
*@param (目的とする受信文字列, グループID，チャンネル, 機器局ID )グループID,チャンネル，機器局IDは2桁の文字列
*@return 目的とする文字列を受信したら0
*@todo テスト用のLEDのコードを削除する．受信失敗のことを考える
**/

DigitalOut myled3(LED3);     //return 0した時に光る用

int Receive_MU2 (char *Receive, char *GI, char *CH, char *EI){    
   
    Serial muport(p13, p14);      //tx, rx  (p9,p10)    (p13,p14)   (p28,p27)シリアル通信で使うピンの配置
       
    muport.baud(19200);                 //ボーレート
    uint8_t last_data[] = {0x0d, 0x0a};
    
    muport.printf("@GI%s", GI);     //GI設定
    for (int i = 0; i < 2; i++){  
    muport.putc(last_data[i]);
    }
    
    muport.printf("@CH%s", CH);     //CH設定
    for (int i = 0; i < 2; i++){  
    muport.putc(last_data[i]);
    }

    muport.printf("@EI%s", EI);     //EI(機器ID)設定
    for (int i = 0; i < 2; i++){  
    muport.putc(last_data[i]);
    }
    
        
    
    char s;             //MU2からくるデータを受け取る用
    char data[30];    //もっと節約できそう
    int data_index = 0;
   // int f = 0;           //受信失敗用の変数です．
    while(1){
   
        while(muport.readable()) {      //送られてくるデータを貯めてます
        s = muport.getc();
        data[data_index++] = s;
        } 
 
        data_index = 0;   
    
    
        if ( data[6] == Receive[0]     //data[0]〜data[5]は受信コマンドなので省きます
          && data[7] == Receive[1]
          && data[8] == Receive[2]
          && data[9] == Receive[3]
          && data[10] == Receive[4]){
 
            myled3 = 1;       //ここはあとで削除できますします．mbedの3つ目のLEDが光れば成功. 返り血0で関数終了です
            break;
         } 
         
        wait(3);    //wait中に受信しても大丈夫です．waitを入れることで例えば1分受信しないから-1を返すということもできると思います．wait省くことできます. 
                    //wait中に受信が集中するとMU2が受信するデータがおかしくなるから，送信周期はこのwaitより大きくしてね
   //     f++; if(f > TBD) return -1;
    }

    return 0;
}


int main(){
 
 char ggg[10] = "PPPPP";
 Receive_MU2(ggg, "01", "0A", "09");        //GI, CH, EIは2桁の文字列として引数に入れてください
 
 return 0;
 
 }
 