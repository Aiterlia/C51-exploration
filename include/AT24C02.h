#ifndef __AT24C02_H__
#define __AT24C02_H__

/**
 * @brief 向rom写入一个字节,注意需要延时5ms来完成写入周期
 * @param address rom的地址，范围0~255
 * @param my_data 写入的字节信息
 */
void at24c02_writeByte(unsigned char address, unsigned char my_data);

/**
 * @brief 读取rom中某地址里的数据
 * @param address 想要读取数据在rom中的地址，范围0~255
 */
unsigned char at24c02_readByte(unsigned char address);

#endif