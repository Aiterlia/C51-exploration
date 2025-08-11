#include<REGX52.H>
#include"../include/OneWire_new.h"
#include"../include/delay.h"

#define SKIP_ROM         0xcc
#define CONVERT_T        0x44
#define READ_SCRATCHPAD  0Xbe

void ds18b20_converT(void){
    OneWire_init();
    // delay(1);
    OneWire_sendByte(SKIP_ROM);
    OneWire_sendByte(CONVERT_T);
}

float ds18b20_readT(void){
    unsigned char TLSB, TMSB;
    int temp;
    float t;
    OneWire_init();
    // delay(1);
    OneWire_sendByte(SKIP_ROM);
    OneWire_sendByte(READ_SCRATCHPAD);
    TLSB = OneWire_receiveByte();
    TMSB = OneWire_receiveByte();
    temp = (TMSB << 8) | TLSB;
    t = temp / 16.0;
    return t;
}
