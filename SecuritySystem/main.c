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
	init();
	
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRD = 0xFF;
	DDRF = 0x00;
	
    PORTD = 0x01;
	adcInit();
	
	while(1){
		int value = ADCH << 8 | ADCL;
		display_text((char *) value);
		waitFunction(100);
	}
}