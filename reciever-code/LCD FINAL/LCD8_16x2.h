/*
 * LCD8_16x2.h
 *
 * Created: 17/03/2019 02:03:26 ص
 *  Author: Khaled
 */ 


#ifndef LCD8_16X2_H_
#define LCD8_16X2_H_

#include <util/delay.h>
#include "DIO_reg.h"

#define LCD_Data_Dir DDRA_Register		/* Define LCD data port direction */
#define LCD_Command_Dir DDRC_Register		/* Define LCD command port direction register */
#define LCD_Data_Port PORTA_Register		/* Define LCD data port */
#define LCD_Command_Port PORTC_Register		/* Define LCD data port */
#define RS PC0				/* Define Register Select (data/command reg.)pin */
#define RW PC1				/* Define Read/Write signal pin */
#define EN PC2				/* Define Enable signal pin */


void LCD_Command(unsigned char cmnd)
{
	LCD_Data_Port= cmnd;
	LCD_Command_Port &= ~(1<<RS);	/* RS=0 command reg. */
	LCD_Command_Port &= ~(1<<RW);	/* RW=0 Write operation */
	LCD_Command_Port |= (1<<EN);	/* Enable pulse */
	_delay_us(1);
	LCD_Command_Port &= ~(1<<EN);
	_delay_ms(3);
}

void LCD_Init (void)			/* LCD Initialize function */
{
	LCD_Command_Dir = 0xFF;		/* Make LCD command port direction as o/p */
	LCD_Data_Dir = 0xFF;		/* Make LCD data port direction as o/p */
	_delay_ms(20);			/* LCD Power ON delay always >15ms */
	
	LCD_Command (0x38);		/* Initialization of 16X2 LCD in 8bit mode */
	LCD_Command (0x0C);		/* Display ON Cursor OFF */
	LCD_Command (0x06);		/* Auto Increment cursor */
	LCD_Command (0x01);		/* Clear display */
	LCD_Command (0x80);		/* Cursor at home position */
}

void LCD_Set_Cursor(char row, char colm){
	char i;
	if(row==1){
		LCD_Command(0x80);
		for(i=0; i<colm; i++){
			LCD_Command(0x14);
		}
	}
	if(row==2){
		LCD_Command(0xC0);
		for(i=0; i<colm; i++){
			LCD_Command(0x14);
		}
	}
}

void LCD_Shift_Right(char T){
	char i;
	for(i=0; i<T; i++){
		LCD_Command(0x1C);
		_delay_ms(500);
	}
}

void LCD_Shift_Left(char T){
	char i;
	for(i=0; i<T; i++){
		LCD_Command(0x18);
		_delay_ms(500);
	}
}

void LCD_Char (unsigned char char_data)	/* LCD data write function */
{
	LCD_Data_Port= char_data;
	LCD_Command_Port |= (1<<RS);	/* RS=1 Data reg. */
	LCD_Command_Port &= ~(1<<RW);	/* RW=0 write operation */
	LCD_Command_Port |= (1<<EN);	/* Enable Pulse */
	_delay_us(1);
	LCD_Command_Port &= ~(1<<EN);
	_delay_ms(1);
}

void LCD_String (char *str)		/* Send string to LCD function */
{
	int i;
	for(i=0;str[i]!=0;i++)		/* Send each char of string till the NULL */
	{
		LCD_Char (str[i]);
	}
}

void LCD_String_xy (char row, char pos, char *str)/* Send string to LCD with xy position */
{
	LCD_Set_Cursor(row,pos);
	LCD_String(str);		/* Call LCD string function */
}

void LCD_Clear()
{
	LCD_Command (0x01);		/* clear display */
	LCD_Command (0x80);		/* cursor at home position */
}

#endif /* LCD8_16X2_H_ */
