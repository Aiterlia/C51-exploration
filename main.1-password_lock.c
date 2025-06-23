#include <REGX52.H>
#include <INTRINS.H>
#include "delay.h"
#include "neon_light.h"
#include "keyborad.h"

unsigned char* password = "12345678";
unsigned char enter[] = "00000000";

unsigned char test(void){
    unsigned char i = 0;
    while(i <= 7){
        if(password[i] != enter[i]){
            return 0;
        }
        i++;
    }
    return 1;
}

void main(){
    unsigned char key_num = 0;
    unsigned char i = 0;
    unsigned char j = 0;
    while(1){
        P1 = 0xf0;
        if(P1 != 0xf0){//矩阵键盘有按键按下
            key_num = key_scan();
            enter[i] = key_num + '0';
            if(key_num == 15){
                for(i = 0; i < 7; i++) { enter[i] = 0; }
                i = 0;
            }
            i++;
        }
        if(i == 8){
            if(test() == 0){
                neon_light(14, 1);
                neon_light(10, 2);
                neon_light(10, 3);//错误
            }else{
                neon_light(12, 1);
                neon_light(0, 2);
                neon_light(10, 3);//正确
            }
        }else{
            for(j = 1; j <= 8; j++){
           // delay(50);
            neon_light(enter[j - 1] - '0', j);
            }
        }
        
    }

}