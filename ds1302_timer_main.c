#include<REGX52.H>
#include"../include/LCD1602.h"
#include"../include/ds1302.h"
#include"../include/delay.h"
#include"keyborad.h"

unsigned char eidt_time_tag = 0;
unsigned char key = -1;
unsigned char loc = 0;//修改时间位选标志
unsigned char temp;
unsigned char lcd_col,lcd_raw;//定位1602显示位置

void int0_init(void){
    EA = 1;
    EX0 = 1;
    IT0 = 1;//0为低电平触发，1为从高到低跳变触发
}

void changeTime(void) interrupt 0{
    eidt_time_tag = 1;
    IE0 = 0;
}

void select_time(void){
    key = key_scan();
    if(key == 15){//确定并转到下一个，最后一个时自动退出
        if(loc <= 6){
            ds_time[loc] = temp;
            LCD_ShowNum(lcd_col, lcd_raw, temp, 2);
            temp = 0;
            loc++;
        }
        
    }
    switch (loc)
    {
    case 0:
        lcd_col = 1;
        lcd_raw = 1;
        break;
    case 1:
        lcd_col = 1;
        lcd_raw = 4;
        break;
    case 2:
        lcd_col = 1;
        lcd_raw = 7;
        break;
    case 3:
        lcd_col = 2;
        lcd_raw = 1;
        break;
    case 4:
        lcd_col = 2;
        lcd_raw = 4;
        break;
    case 5:
        lcd_col = 2;
        lcd_raw = 7;
        break;
    case 6:
        lcd_col = 2;
        lcd_raw = 10;
        break;
    }//定位位选各时间单位时1602的闪烁位置

    if(key >= 0 && key <= 9){
        temp = temp * 10 + key;
        if(temp / 100 != 0){
            temp = 0;
        }
    }
    
    if(key == 14){
        temp = 0;//重新输入
    }
    LCD_ShowNum(lcd_col, lcd_raw, temp, 2);
    delay(100);
    LCD_ShowNum(lcd_col, lcd_raw, ds_time[loc], 2);
    // LCD_ShowNum(2, 10, loc, 1);
    // LCD_ShowNum(2, 11, key, 2);
    delay(100);

}

void edit_time(void){
    temp = 0;
    while(1){
        select_time();
        if(loc > 6){
            loc = 0;
            eidt_time_tag = 0;
            LCD_ShowString(2, 10, "  ");
            ds1302_settime();
            return;
        }
        if(P3_0 == 0){
            delay(10);
            if(P3_0 == 0){
                while(P3_0 == 0);
                eidt_time_tag = 0;
                loc = 0;
                ds1302_settime();//直接退出修改模式，并将已修改的写入1302
                return;
            }
            
        }
        

    }
}

unsigned char second,min;

void main(){
  
    int0_init();
    LCD_Init();//初始化1602

    ds1302_init();
    
    ds1302_settime();//将内置的时间数组写入ds1302
    

    LCD_ShowString(1, 1, "  -  -  |Hello!");
    LCD_ShowString(2, 1, "  -  -  -");
    while(1){
        if(eidt_time_tag == 1) {edit_time();}
        
        ds1302_readtime();
        LCD_ShowNum(1, 1, ds_time[0], 2);
        LCD_ShowNum(1, 4, ds_time[1], 2);
        LCD_ShowNum(1, 7, ds_time[2], 2);
        LCD_ShowNum(2, 1, ds_time[3], 2);
        LCD_ShowNum(2, 4, ds_time[4], 2);
        LCD_ShowNum(2, 7, ds_time[5], 2);
        switch (ds_time[6])
        {
        case 1:
            LCD_ShowString(2, 14, "MON");
            break;
        case 2:
            LCD_ShowString(2, 14, "TUE");
            break;
        case 3:
            LCD_ShowString(2, 14, "WED");
            break;
        case 4:
            LCD_ShowString(2, 14, "THU");
            break;
        case 5:
            LCD_ShowString(2, 14, "FRI");
            break;
        case 6:
            LCD_ShowString(2, 14, "SAT");
            break;
        case 7:
            LCD_ShowString(2, 14, "SUN");
            break;
        }
        //LCD_ShowNum(2, 10, ds_time[6], 2);//用switch表示周几
        
    }
}