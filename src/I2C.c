#include<REGX52.H>

sbit I2C_SCL = P2^1;
sbit I2C_SDA = P2^0;

// unsigned char I2C_SCL;
// unsigned char I2C_SDA;


void I2C_start(void){
    I2C_SDA = 1;//拉高起始电平
    I2C_SCL = 1;

    I2C_SDA = 0;//在clk高电平期间sad跳变为零表示start信号

    I2C_SCL = 0;
}

void I2C_stop(void){
    I2C_SDA = 0;//拉低起始电平
    I2C_SCL = 1;
    I2C_SDA = 1;//在clk高电平期间sad跳变为1表示stOP信号
    
}

void I2C_sendByte(unsigned char byte){
    unsigned char i;
    for(i = 0; i < 8; i++){
        I2C_SDA = byte & (0x80 >> i);

        I2C_SCL = 1;
        I2C_SCL = 0;//给scl一个脉冲使其读取一位数据
    }
}

unsigned char I2C_receiveByte(void){
    unsigned char byte = 0x00, i;
    I2C_SDA = 1;
    for(i = 0; i < 8; i++){
        I2C_SCL = 1;
        if(I2C_SDA) { byte |= (0x80 >> i); }
        I2C_SCL = 0;
    }
    return byte;
}

void I2C_sendAnswer(unsigned char answerBit){

    I2C_SDA = answerBit;//如果应答给0，不应答给1，由answerBit决定
    I2C_SCL = 1;
    I2C_SCL = 0;
}

unsigned char I2C_receiveAnswer(void){
    unsigned char answerBit;
    I2C_SDA = 1;//开放数据线
    I2C_SCL = 1;
    answerBit = I2C_SDA;
    I2C_SCL = 0;
    return answerBit;
}