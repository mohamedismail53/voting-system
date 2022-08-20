
#include <avr/io.h>
#include <util/delay.h>
#include "AllHeaders.h"


#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#define COUNT_YES 0x11
#define COUNT_NO 0x22
#define COUNT_ABST 0x33

unsigned int y=0,n=0,a=0;
unsigned char str_yes[10],str_no[10],str_abstain[10];



void fun_no(void)
{  
	n++;
	LCD_Set_Cursor(2,6);
	itoa(n, str_no,10);
	LCD_String(str_no);
	
}
void fun_abs(void)
{
	a++;
	LCD_Set_Cursor(2,12);
	itoa(a,str_abstain,10);
	LCD_String(str_abstain);
}
void fun_yes (void)
{ 	
	y++;
	LCD_Set_Cursor(2,2);
	itoa(y, str_yes,10);
	LCD_String(str_yes);	
}


int main(void)
{
	LCD_Init();
	LCD_Set_Cursor(1,1);
	LCD_String(" YES  ");
	LCD_String("NO  ");
	LCD_String("ABST ");
	DDRC=0xff;
	DDRA=0xff;
	
	DDRD=0X00;
	
	
	while(1)
	{
		if ((PIND==COUNT_YES)&&y==0)
			fun_yes;
		if ((PIND==COUNT_NO)&&n==0)
			fun_no;
		if ((PIND==COUNT_ABST)&&a==0)
			fun_abs;	
	}
	return 0;
}