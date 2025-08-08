#include<REGX52.H>
#include "delay.h"
#include<string.h>

unsigned char i = 0;
unsigned char len;

void UART_init(){
    PCON = 0x80;		//波特率倍速
	SCON = 0x50;		//8位数据,可变波特率,REN置1，运行接收数据
	TMOD &= 0x0F;		//清除定时器1模式位 
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xFA;		//设定定时初值
	TH1 = 0xFA;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1

    EA = 1;
    ES = 1;//启动串口中断
}

void UART_send_byte(unsigned char byte){
    SBUF = byte;
    while(TI = 0);//等待TI置1，标志串口输出完毕
    TI = 0;//TI需手动重装 
}

void UART_send_string(char* str){
    len = strlen(str);
    for(i = 0;i < len; i++){
        delay(10);
        SBUF = str[i];
        while(TI = 0);//等待TI置1，标志串口输出完毕
        TI = 0;//TI需手动重装 
    }
}