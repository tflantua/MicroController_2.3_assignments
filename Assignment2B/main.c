/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** ioisr.c
**
** Beschrijving:	ISR on PORTD demonstrattion
** Target:			AVR mcu
** Build:			avr-gcc -std=c99 -Wall -O3 -mmcu=atmega128 -D F_CPU=8000000UL -c ioisr.c
**					avr-gcc -g -mmcu=atmega128 -o ioisr.elf ioisr.o
**					avr-objcopy -O ihex ioisr.elf ioisr.hex
**					or type 'make'
** Author: 			dkroeske@gmail.com
** -------------------------------------------------------------------------*/

#include <avr/io.h>

#include <avr/interrupt.h>
#include "LCD.H"

volatile int led = 1;

const unsigned char digits[16] = {
	0b00111111, // 0
	0b00000110, // 1
	0b01011011, //2
	0b01001111, //3
	0b01100110, //4
	0b01101101, //5
	0b01111101, //6
	0b00000111, //7
	0b01111111, //8
	0b01101111, //9	0b01110111, //A	0b01111111, //B	0b00111001, //C	0b00111111, //D	0b01111001, //E	0b01110001  //F};

/*****************************************************************
short:			ISR INT0
inputs:
outputs:
notes:			Set PORTD.5
Version :    	DMK, Initial code
*******************************************************************/

ISR( INT0_vect ) {
	//PORTD |= (1<<5);
	led++;
	if(led > 15 || led < 0)
	{
		PORTC = digits[14];
		}else{
		PORTC = digits[led];
	}
}

/******************************************************************
short:			ISR INT1
inputs:
outputs:
notes:			Clear PORTD.5
Version :    	DMK, Initial code
*******************************************************************/
ISR( INT1_vect ) {
	//PORTD &= ~(1<<5);
	led--;
	if(led > 15 || led < 0)
	{
		PORTC = digits[14];
	}
	else{
		PORTC = digits[led];
	}
}



/******************************************************************
short:			main() loop, entry point of executable
inputs:
outputs:
notes:			Slow background task after init ISR
Version :    	DMK, Initial code
*******************************************************************/

void opdracht1en2( void );
void opdracht3( void );
int opdracht5( void );
void display( int digit );


int main( void ) {
	_delay_ms(500);
	opdracht5();
	return 1;
}

int opdracht5()
{
	// Init I/O
	DDRC = 0xFF;			// PORTD(7) output, PORTD(6:0) input
	PORTC = 0xFF;
	
	init();
	
	char test[] = "hello";

	// Write sample string
	display_text(test);

	// Loop forever
	while (1) {
		PORTC ^= (1<<0);	// Toggle PORTD.7
		wait( 250 );
	}

	return 1;
}

void opdracht3(){
	DDRC = 0xFF;
	while(1){
		for (int i = -1; i < 17; i++)
		{
			wait(1);
		}
	}
}

void display(int digit){
	if(digit > -1 && digit < 16)
	{
		PORTC = digits[digit];
		}else{
		PORTC = digits[0xE];
	}
}

void opdracht1en2( void ){
	// Init I/O
	DDRD = 0xF0;			// PORTD(7:4) output, PORTD(3:0) input
	DDRC = 0xFF;

	// Init Interrupt hardware
	EICRA |= 0x0B;			// INT1 falling edge, INT0 rising edge
	EIMSK |= 0x03;			// Enable INT1 & INT0
	
	// Enable global interrupt system
	//SREG = 0x80;			// Of direct via SREG of via wrapper
	sei();

	while (1) {
		//PORTD ^= (1<<7);	// Toggle PORTD.7
		wait( 500 );
	}
}