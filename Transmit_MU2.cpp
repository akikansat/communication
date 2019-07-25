/**
*@author TakedaShinji
*@dateで2019/07/01
**/

#include "mbed.h"
#include "stdint.h"
#include <string.h>
#include <stdio.h> 


/**
*引数の文字列を一回だけ送信する関数
*@param (送りたい文字列, グループID，チャンネル, 目的局ID )グループID,チャンネル，目的局IDは2桁の文字列
*@return なし
*@todo 送信出力をいじるかどうか
**/




void Transmit_MU2(char *transmitdata, char *group_id, char *channel, char *dest_id){ 
  //GPS_MU2(送りたい文字列, グループID "01" "02"など，チャンネル "09" "0A"など, 目的局ID 受信するMU2のEIと同じにしてください)   

    Serial muport(p13, p14); // tx, rx  (p9,p10)    (p13,p14)   (p28,p27)　シリアル通信で使うピンの配置
    uint8_t last_data[] = {0x0d, 0x0a};
    
    muport.baud(19200);

    
    muport.printf("@GI%s", group_id);     //GI設定
    for (int i = 0; i < 2; i++){  
    muport.putc(last_data[i]);
    }
    
    muport.printf("@CH%s", channel);     //CH設定
    for (int i = 0; i < 2; i++){  
    muport.putc(last_data[i]);
    }

    muport.printf("@DI%s", dest_id);     //DI(目的局ID)設定
    for (int i = 0; i < 2; i++){  
    muport.putc(last_data[i]);
    }

    int mojisuu = strlen(transmitdata);          //送りたい文字のバイト数を数える
    muport.printf("@DT%02x", mojisuu);      
    muport.printf("%s", transmitdata);
    for (int i = 0; i < 2; i++){  
    muport.putc(last_data[i]);
    }      
}

int main(){
  
  while(1){
    char ggg[] = "PPPPP";
    Transmit_MU2(ggg, "07", "08", "09");
    wait(1);
    }
}