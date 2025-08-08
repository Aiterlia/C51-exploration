#ifndef __DS1302_H__
#define __DS1302_H__

extern unsigned char ds_time[];
/**
 * @brief 将CE端，SCLK段置零
 */
void ds1302_init(void);

/**
 * @brief 向1302写入一个数据
 * @param command 1302的指令码
 * @param dat 写入1302的一个16进制数据（我用data不知道为什么报错）
 */
void ds1302_writeByte(unsigned char command, unsigned char dat);

/**
 * @brief 向1302读取一个数据，读取什么类型的数据由指令码决定
 * @param command 时间类型，已宏定义为DS_YEAR，_MONTH等常量
 */
unsigned char ds1302_readByte(unsigned char command);

/**
 * @brief 1302内置一个外部的时间数组，调用该函数将数组内的时间载入到1302中
 */
void ds1302_settime(void);

/**
 * @brief 读取1302内的时间，会将最新的时间更新到时间数组ds_time中
 */
void ds1302_readtime(void);

#endif