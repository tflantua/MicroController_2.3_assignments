
/*
 * LCD.C
 *
 * Created: 09/02/2022 11:25:25
 *  Author: Rick
 */ 

#include "LCD.H"

void lcd_Command(unsigned char dat)
{
	PORTC = dat & 0xF0;
	PORTC |= 0x08;
	
	_delay_ms(1);
	
	PORTC = 0x04;
	PORTC = (dat & 0x0F) << 4;
	
	PORTC |= 0x08;
	
	_delay_ms(1);
	
	PORTC = 0x00;
}

void init()
{
	lcd_Command(0x02); //return home
	lcd_Command(0x28); //set 4 bit mode
	lcd_Command(0x0C); //Display on, Curser off, blinker off
	lcd_Command(0x06); //entry mode: cursert to right no shift
	lcd_Command(0x80); //RAM addr 0, First position line 1 
	
}

void lcd_writeChar(unsigned char dat){
	PORTC = dat & 0xF0;
	PORTC |= 0x0C;
	
	_delay_ms(1);
	
	PORTC = 0x04;
	PORTC = (dat & 0x0F) << 4;
	
	PORTC |= 0x0C;
	
	_delay_ms(1);
	
	PORTC = 0x00;
}

void display_text(char *str)
{
	lcd_Command(0x80);
	
	int i = 0;
	
	while(NULL != (*str+i) )
	{
		lcd_writeChar(*str+i);
	}
}

void set_cursor(int position)
{
	
}