#ifndef __ONEWIRE_NEW_H__
#define __ONEWIRE_NEW_H__

unsigned char OneWire_init(void);

void OneWire_sendBit(unsigned char my_bit);

unsigned char OneWire_receiveBit(void);

void OneWire_sendByte(unsigned char byte);

unsigned char OneWire_receiveByte(void);

#endif