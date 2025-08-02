#include<REGX52.H>
#include "delay.h"
#include"UART.h"

unsigned char byte = 0x00;
char* str = "hello world!\n";


void URAT_recieve(void) interrupt 4{
    if(RI == 1){
        P2 = SBUF;
    }
    RI = 0;
}

void main(){

    UART_init();
    
    while (1)
    {
        delay(10);
        // UART_send_byte(byte);
        // byte++;
        UART_send_string(str);
    }
    
}