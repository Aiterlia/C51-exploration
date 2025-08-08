#ifndef __I2C_H__
#define __I2C_H__

void I2C_start(void);

void I2C_stop(void);

void I2C_sendByte(unsigned char byte);

unsigned char I2C_receiveByte(void);

void I2C_sendAnswer(unsigned char answerBit);

unsigned char I2C_receiveAnswer(void);

#endif