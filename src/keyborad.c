#include <REGX52.H>
#include "delay.h"

/**
 * @brief 矩阵键盘扫描，返回一个值，范围0~15，当没有按键按下时返回-1
 */
unsigned char key_scan(void){
    unsigned char key_num = -1;
    
	P1 = 0xff;
	P1_3 = 0;
	if (P1_7 == 0) { delay(20); while(P1_7 == 0); delay(20); key_num =1; }
	if (P1_6 == 0) { delay(20); while(P1_6 == 0); delay(20); key_num =5; }
	if (P1_5 == 0) { delay(20); while(P1_5 == 0); delay(20); key_num =9; }
	if (P1_4 == 0) { delay(20); while(P1_4 == 0); delay(20); key_num =13; }
	
	P1 = 0xff;
	P1_2 = 0;
	if (P1_7 == 0) { delay(20); while(P1_7 == 0); delay(20); key_num =2; }
	if (P1_6 == 0) { delay(20); while(P1_6 == 0); delay(20); key_num =6; }
	if (P1_5 == 0) { delay(20); while(P1_5 == 0); delay(20); key_num =10; }
	if (P1_4 == 0) { delay(20); while(P1_4 == 0); delay(20); key_num =14; }
	
	P1 = 0xff;
	P1_1 = 0;
	if (P1_7 == 0) { delay(20); while(P1_7 == 0); delay(20); key_num =3; }
	if (P1_6 == 0) { delay(20); while(P1_6 == 0); delay(20); key_num =7; }
	if (P1_5 == 0) { delay(20); while(P1_5 == 0); delay(20); key_num =11; }
	if (P1_4 == 0) { delay(20); while(P1_4 == 0); delay(20); key_num =15; }
	
	P1 = 0xff;
	P1_0 = 0;
	if (P1_7 == 0) { delay(20); while(P1_7 == 0); delay(20); key_num =4; }
	if (P1_6 == 0) { delay(20); while(P1_6 == 0); delay(20); key_num =8; }
	if (P1_5 == 0) { delay(20); while(P1_5 == 0); delay(20); key_num =12; }
	if (P1_4 == 0) { delay(20); while(P1_4 == 0); delay(20); key_num =0; }
	
	return key_num;
}

unsigned char key_loney_scan(void){
	if(P3_0 == 0) { delay(20); while(P3_0 == 0); return 2; }
	if(P3_1 == 0) { delay(20); while(P3_0 == 0); return 1; }
	if(P3_2 == 0) { delay(20); while(P3_0 == 0); return 3; }
	if(P3_3 == 0) { delay(20); while(P3_0 == 0); return 4; }
}