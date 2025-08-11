#include<REGX52.H>
#include"../include/LCD1602.h"
#include"../include/delay.h"
#include"../include/keyborad.h"
#include"../include/ds18b20.h"
#include"../include/AT24C02.h"
#include"../include/I2C.h"
#include"../include/buzzer.h"

float t;

unsigned char high_temp = 32;
unsigned char low_temp = 16;
unsigned char key;

void main(){


    LCD_init();
    LCD_ShowString(1, 1, "H:  L:  ");
    // at24c02_writeByte(0, high_temp);
    // delay(5);
    // at24c02_writeByte(1, low_temp);
    // delay(5);//这是一开始存储器没有存入温度数据时用的，里面有数据之后掉电保存也就不需要了
    while(1){
        /*上下限温度显示及修改模块*/
        high_temp = at24c02_readByte(0);
        low_temp = at24c02_readByte(1);
        LCD_ShowNum(1, 3, high_temp, 2);
        LCD_ShowNum(1, 7, low_temp, 2);
        key = key_loney_scan();
        if(key){
            if(key == 1) { high_temp++; }
            if(key == 2) { high_temp--; }
            if(key == 3) { low_temp++; }
            if(key == 4) { low_temp--; }
            at24c02_writeByte(0, high_temp);
            delay(5);
            at24c02_writeByte(1, low_temp);
            delay(5);
        }

        /*温度显示模块*/
        ds18b20_convert();
        t = ds18b20_readT();

        if(t >= high_temp || t <= low_temp){
            buzzer_time();
        }

        if(t < 0){
            LCD_ShowString(2, 1, "-");
            t = -t;
        }else{
            LCD_ShowString(2, 1, "+");
        }
        LCD_ShowNum(2, 2, t, 3);
        LCD_ShowString(2, 5, ".");
        LCD_ShowNum(2, 6, (unsigned long)(t * 10000) % 10000, 4);
    }
}