/*
* main.c
*
* Created: 3/23/2022 2:11:34 PM
*  Author: thoma
*/

#include <xc.h>
#include "waiting.h"
#include "LCD.H"

void adcInit(void){
	ADMUX = 0b01100001;
	ADCSRA = 0b11100110;
}

int main(void)
{
	DDRC = 0xFF;			// PORTD(7) output, PORTD(6:0) input
	PORTC = 0xFF;
	init();
	
	DDRF = 0x00;
	DDRA = 0xFF;
	DDRB = 0xFF;
	adcInit();
	
	char text_print[20];
	unsigned long int waarde;
	long l = 0;
	long h  = 0;
	
	DDRD = 0x00;
	while(1){
		l = ADCL;
		h  = ADCH;
		PORTA = l;
		PORTB = h;
		
		waarde = (h << 8) | l;
		
		sprintf(text_print, "waarde %lu", waarde);
		
		display_text(text_print);
		waitFunction(100);
		
		lcd_clear();
	}
	
	//
	//PORTD = 0x01;

	//
	//while(1){
	//int value = ADCH << 8 | ADCL;
	//display_text((char *) value);
	//waitFunction(100);
	//}
}