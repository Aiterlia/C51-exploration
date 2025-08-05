/*
    8*8led点阵相关控制头文件，通过此文件可实现控制led点阵点亮某一列的led
    本程序由伊莎蒂开发
*/


#ifndef __MATRIX_LED_H__
#define __MATRIX_LED_H__


/*
@brief 向74595芯片写入一个十六进制数并输出
@param 一个unsigned char 类型的16进制数，如0xff
@return null
*/
void _74HC595_WriteByte(unsigned char byte);

/*
@brief 点亮led点阵里某一列的灯，点亮灯的位置由传入的16进制参数决定
        例如：0xff使某一列的上半部分点亮下半部分灭
@param  位选的列数col，从0到7;控制该列亮灯情况的16进制数
*/
void led_show_col(unsigned char col,unsigned char dt);

/*
@brief 使led点阵亮起预设的表情符号，smile即为笑脸，sad为哭脸，直接调用即可
*/
void draw_smile(void);
void draw_sad(void);

#endif