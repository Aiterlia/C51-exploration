#include <REGX52.H>
#include <INTRINS.H>
#include "neon_light.h"
#include "delay.h"
#include "keyborad.h"

unsigned char timers = 0;//定时器中断次数，用于定时一秒
unsigned char second = 0;
unsigned char minute = 0;
unsigned char hour = 0;//显示在数码管上的时间

unsigned char i = 0;
unsigned char key;//更改时间用到的变量

unsigned char enter[] = "00";//临时储存修改时间用的数组

void interrupt_init(){
    EA = 1;//总中断允许
    ET0 = 1;//使用定时器0
    TMOD = 0X01;//定时器方式1
    TH0 = (65535 - 50000) / 256;
    TL0 = (65535 - 50000) % 256;//装入定时器初值
    TR0 = 1;//定时器启动
}

void timer() interrupt 1{
    TR0 = 0;
    TH0 = (65535 - 50000) / 256;
    TL0 = (65535 - 50000) % 256;//装入定时器初值
    if(timers == 20){
        timers = 0;
        second++;
        if(second == 60){
            second = 0;
            minute++;
            if(minute == 60){
                minute = 0;
                hour++;
                if(hour == 60){
                    hour = 0;
                }
            }
        }//时间增加以及进位处理
    }else{
        timers++;
    }
    TR0 = 1;
}

void set_time(unsigned char num, unsigned char loc1, unsigned char loc2){
    TR0 = 0;

    while(1){
        key = key_scan();//获取键盘数值，无按键按下时，默认返回-1
        if(key != -1 && i < 2){
            if(key <= 9 && key >= 0){
                enter[i] = key + '0';
                i++;
            }
        }//仅当key值在十以内且位数不超过二时载入临时数组
        if(key == 15){
            i = 0;
            switch (num)
            {
            case 1:
                hour = (enter[0] - '0') * 10 + (enter[1] - '0');
                break;
            case 2:
                minute = (enter[0] - '0') * 10 + (enter[1] - '0');
                break;
            case 3:
                second = (enter[0] - '0') * 10 + (enter[1] - '0');
                break;
            }
            break;
        }//确认修改当前时间了，把临时数组的值载入对应小时/分钟/秒
        if(key == 14){
            enter[0] = '0';
            enter[1] = '0';
            i = 0;
        }//如果按超了两位数，会直接无视按键操作，此时按下s14来重置当前输入
        neon_light(enter[0] - '0', loc1);
        neon_light(enter[1] - '0', loc2);//在完成修改前，数码管显示临时数组的值
    }
    TR0 = 1;
}

void main(){
    interrupt_init();
    while(1){
        if(P3_1 == 0){
            delay(20);
            while(P3_1 == 0);
            set_time(1, 3, 4);
            set_time(2, 5, 6);
            set_time(3, 7, 8);//分别从小时/分钟/秒来进入函数并之一修改
        }
        neon_light(hour / 10, 3);
        neon_light(hour % 10, 4);
        neon_light(minute / 10, 5);
        neon_light(minute % 10, 6);
        neon_light(second / 10, 7);
        neon_light(second % 10, 8);//数码管显示当前时间
    }

}