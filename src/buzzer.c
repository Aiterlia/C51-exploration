#include<REGX52.H>
#include<INTRINS.H>


sbit buz = P2^5;
unsigned int buzzer_i = 0;

void my_delay_10us(unsigned int ms){
	while(ms--);
}

/**
 * @brief 调用此函数，使蜂鸣器响一下
 * @bug 由于神秘力量，有时候调用此函数蜂鸣器不会响
 */
void buzzer_time(void){
    for(buzzer_i = 0; buzzer_i < 100; buzzer_i++){
        buz = !buz;
        my_delay_10us(100);
		
    }
	buz = 0;
}