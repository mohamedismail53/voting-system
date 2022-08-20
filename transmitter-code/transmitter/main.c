#include <avr/io.h>
#include <util/delay.h>

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#define COUNT_YES 0x11
#define COUNT_NO 0x22
#define COUNT_ABST 0x33


int main(void)
{
	DDRB=0x00;
	DDRD=0XFF;
	PORTD=0X00;
	while(1)
	{
		if (PINB&(1<<PB0))
		{
		   PORTD=(COUNT_YES);
		   
		}
	    if (PINB&(1<<PB1))
		{
			PORTD=(COUNT_NO);
			
		}
		if (PINB&(1<<PB2))
		{
			PORTD=(COUNT_ABST);
			
		}
	}
	return 0;
}