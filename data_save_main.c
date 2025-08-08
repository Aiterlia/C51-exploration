#include<REGX52.H>
#include"../include/keyborad.h"
#include"../include/LCD1602.h"
#include"../include/AT24C02.h"
#include"../include/delay.h"

unsigned char rom_data;

void main(){
    LCD_Init();
    LCD_ShowString(1, 1, "Hello!");
    at24c02_writeByte(78,2);
    delay(5);//写周期为5ms


    
    rom_data = at24c02_readByte(2);
    LCD_ShowNum(2, 1, rom_data, 3);
    while(1){

    }
}