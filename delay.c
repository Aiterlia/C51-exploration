#include <INTRINS.H>

void delay(int ms)		//@11.0592MHz
{
	unsigned char i_delay, j_delay;
    for( ; ms > 0; ms--){
    	_nop_();
	    _nop_();
	    _nop_();
    	i_delay = 11;
    	j_delay = 190;
	    do
	    {
    		while (--j_delay);
    	} while (--i_delay);
    }

}
