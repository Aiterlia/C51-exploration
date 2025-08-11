#include<REGX52.H>
#include<INTRINS.H>

sbit OneWire_DQ = P3^7;

// unsigned char OneWire_DQ = 1;

void Delay480us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 218;
	while (--i);
}

void Delay70us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 29;
	while (--i);
}

void Delay10us()		//@11.0592MHz
{
	unsigned char i;

	i = 2;
	while (--i);
}

void Delay50us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 20;
	while (--i);
}

void Delay5us()		//@11.0592MHz
{
}


unsigned char OneWire_init(void){
    unsigned char answer_bit;

    OneWire_DQ = 1;
    OneWire_DQ = 0;
    Delay480us();
    OneWire_DQ = 1;
    Delay70us();

    answer_bit = OneWire_DQ;
    Delay480us();
    return answer_bit;
}

void OneWire_sendBit(unsigned char my_bit){
    OneWire_DQ = 1;
    OneWire_DQ = 0;
    Delay10us();
    OneWire_DQ = my_bit;
    Delay50us();
    OneWire_DQ = 1;
}

unsigned char OneWire_receiveBit(void){
    unsigned char my_bit;

    OneWire_DQ = 0;
    Delay5us();
    OneWire_DQ = 1;
    Delay5us();
    my_bit = OneWire_DQ;
    Delay50us();
    return my_bit;
}

void OneWire_sendByte(unsigned char byte){
    unsigned char i;

    for(i = 0; i < 8; i++){
        OneWire_sendBit(byte & (0x01 << i));
    }

}

unsigned char OneWire_receiveByte(void){
    unsigned char i;
    unsigned char byte = 0x00;
    for(i = 0; i < 8; i++){
        if(OneWire_receiveBit()){ byte |= (0x01 << i); }
    }

    return byte;
}