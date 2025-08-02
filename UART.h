#ifndef __UART_H__
#define __UART_H__

void UART_init(void);

void UART_send_byte(unsigned char byte);

void UART_send_string(char* str);

#endif