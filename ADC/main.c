/*
 * main.c
 *
 * Created: 5/22/2022 8:39:14 PM
 *  Author: Test
 */ 

#include <xc.h>
#include "waiting.h"
#include "lcd.h"
int main(void)
{
	lcd_init();
	char text[20];
	
	DDRF = 0x00;
	DDRB = 0xff;
	
	ADMUX = 0b11100011; 
	ADCSRA = 0b11100001;
	
	
    while(1)
    {
		uint16_t temp = ADCH;
		PORTB = temp;
		sprintf(text, "temp = %d", temp );
		lcd_clear();
		display_text(text);
				
		waitFunction(500);
    }
}