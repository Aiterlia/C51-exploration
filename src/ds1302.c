#include<REGX52.H>

#define DS_SECOND 0x80
#define DS_MINUTE 0x82
#define DS_HOUR 0x84
#define DS_DATE 0x86
#define DS_MONTH 0x88
#define DS_DAY 0x8a
#define DS_YEAR 0x8c //定义各数值对应写指令

sbit ds_SCLK = P3^6;
sbit ds_IO = P3^4;
sbit ds_CE = P3^5;

unsigned char ds_cnt;
unsigned char ds_read_data = 0x00;
unsigned char ds_temp;

unsigned char ds_time[] = {25, 8, 5, 19, 35, 55, 2};//年 月 日 小时 分钟 秒 周几

void ds1302_init(void){
    ds_CE = 0;
    ds_SCLK = 0;
}

void ds1302_writeByte(unsigned char command, unsigned char dat){
    ds_CE = 1;
    
    for(ds_cnt = 0; ds_cnt < 8; ds_cnt++){
        ds_IO = command & (0x01 << ds_cnt);
        ds_SCLK = 1;
        ds_SCLK = 0;//模拟时钟刻
    }
    for(ds_cnt = 0; ds_cnt < 8; ds_cnt++){
        ds_IO = dat & (0x01 << ds_cnt);
        ds_SCLK = 1;
        ds_SCLK = 0;
    }

    ds_CE = 0;
}

unsigned char ds1302_readByte(unsigned char command){
    ds_CE = 1;
    ds_read_data = 0x00;
    command |= 0x01;//写指令的指令码与读指令只差1，且都是单数，所以这里直接令最低为1
    for(ds_cnt = 0; ds_cnt < 8; ds_cnt++){
        ds_IO = command & (0x01 << ds_cnt);
        ds_SCLK = 0;
        ds_SCLK = 1;
    }
    

    for(ds_cnt = 0; ds_cnt < 8; ds_cnt++){
        ds_SCLK = 1;
        ds_SCLK = 0;
       if(ds_IO){
            ds_read_data |= (0x01 << ds_cnt);
        } 
    }
    

    ds_CE = 0;
    ds_IO = 0;
    return ds_read_data;
}


void ds1302_settime(void){
    ds1302_writeByte(0x8e, 0x00);//解除写保护
    ds1302_writeByte(DS_YEAR, ds_time[0] / 10 * 16 + ds_time[0] % 10);
    ds1302_writeByte(DS_MONTH, ds_time[1] / 10 * 16 + ds_time[1] % 10);
    ds1302_writeByte(DS_DATE, ds_time[2] / 10 * 16 + ds_time[2] % 10);
    ds1302_writeByte(DS_HOUR, ds_time[3] / 10 * 16 + ds_time[3] % 10);
    ds1302_writeByte(DS_MINUTE, ds_time[4] / 10 * 16 + ds_time[4] % 10);
    ds1302_writeByte(DS_SECOND, ds_time[5] / 10 * 16 + ds_time[5] % 10);
    ds1302_writeByte(DS_DAY, ds_time[6] / 10 * 16 + ds_time[6] % 10);


}

void ds1302_readtime(void){
    ds_temp = ds1302_readByte(DS_YEAR);
    ds_time[0] = ds_temp / 16 * 10 + ds_temp % 16;

    ds_temp = ds1302_readByte(DS_MONTH);
    ds_time[1] = ds_temp / 16 * 10 + ds_temp % 16;

    ds_temp = ds1302_readByte(DS_DATE);
    ds_time[2] = ds_temp / 16 * 10 + ds_temp % 16;

    ds_temp = ds1302_readByte(DS_HOUR);
    ds_time[3] = ds_temp / 16 * 10 + ds_temp % 16;

    ds_temp = ds1302_readByte(DS_MINUTE);
    ds_time[4] = ds_temp / 16 * 10 + ds_temp % 16;

    ds_temp = ds1302_readByte(DS_SECOND);
    ds_time[5] = ds_temp / 16 * 10 + ds_temp % 16;

    ds_temp = ds1302_readByte(DS_DAY);
    ds_time[6] = ds_temp / 16 * 10 + ds_temp % 16;
}