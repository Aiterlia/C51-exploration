#include <INTRINS.H>

void delay(int ms)		//@11.0592MHz
{
	unsigned char i, j;
    for( ; ms > 0; ms--){
    	_nop_();
	    _nop_();
	    _nop_();
    	i = 11;
    	j = 190;
	    do
	    {
    		while (--j);
    	} while (--i);
    }

}
