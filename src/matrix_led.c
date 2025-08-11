#include<REGX52.H>
#include"../include/delay.h"

unsigned char cnt_595;

sbit RCK = P3^5;
sbit SCK = P3^6;
sbit SER = P3^4;

/** 
* @param byte 
*/
void _74HC595_WriteByte(unsigned char byte){
    SCK = 0;
    RCK = 0;
    
    for(cnt_595 = 0; cnt_595 < 8; cnt_595++){
        SER = byte & (0x80 >> cnt_595);
        SCK = 1;
        SCK = 0;//模拟时钟跳变操作，将数据推入元件
    }
    RCK = 1;
    RCK = 0;//将数据输出
}

void led_show_col(unsigned char col,unsigned char dt){
    _74HC595_WriteByte(dt);
    P0 = ~(0x80 >> col);//0为选中，视P0_7为第一列
    delay(1);//加了delay，点阵会频闪比较亮，不加就很很暗但不频闪(护眼说是)
    P0 = 0xff;//延时+位清零
}

void draw_smile(void){
    led_show_col(0, 0x3c);
    led_show_col(1, 0x42);
    led_show_col(2, 0xa9);
    led_show_col(3, 0x85);
    led_show_col(4, 0x85);
    led_show_col(5, 0xa9);
    led_show_col(6, 0x42);
    led_show_col(7, 0x3c); 
}
void draw_sad(void){
    led_show_col(0, 0x3c);
    led_show_col(1, 0x42);
    led_show_col(2, 0xa5);
    led_show_col(3, 0x89);
    led_show_col(4, 0x89);
    led_show_col(5, 0xa5);
    led_show_col(6, 0x42);
    led_show_col(7, 0x3c); 
}