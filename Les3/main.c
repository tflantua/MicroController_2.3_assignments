/*
* main.c
*
* Created: 4/3/2022 10:14:14 PM
*  Author: Test
*/

#include <xc.h>
#include <stdio.h>
#include "LCD.H"

void opdracht1();
void opdracht2();


int main(void)
{
	_delay_ms(500);
	opdracht1();
}


void opdracht1(){
	DDRC = 0xFF;			// PORTD(7) output, PORTD(6:0) input
	PORTC = 0xFF;
	
	init();
	
	DDRA=0xff;
	DDRD = 0x00;
	
	TCCR2 = 0b00000111;

	while(1){
		char text[20];
		sprintf(text, "Hoeveel keer: %d", TCNT2);
		
		display_text(text);
		
		wait(100);
		
		lcd_clear();
	}
}

void opdracht2(){
	
}