#include<REGX52.H>
#include"../include/I2C.h"

#define at24c02_address   0xa0//元件的写地址，读地址为0x01


void at24c02_writeByte(unsigned char address, unsigned char my_data){
    I2C_start();
    I2C_sendByte(at24c02_address);
    I2C_receiveAnswer();
    I2C_sendByte(address);
    I2C_receiveAnswer();
    I2C_sendByte(my_data);
    I2C_receiveAnswer();
    I2C_stop();
}

unsigned char at24c02_readByte(unsigned char address){
    unsigned char read_data;
    I2C_start();
    I2C_sendByte(at24c02_address);
    I2C_receiveAnswer();
    I2C_sendByte(address);
    I2C_receiveAnswer();
    I2C_start();
    I2C_sendByte(at24c02_address | 0x01);
    I2C_receiveAnswer();
    read_data = I2C_receiveByte();
    I2C_sendAnswer();
    I2C_stop();

    return read_data;
}