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

#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


/******************************************************************
short:			Busy wait number of millisecs
inputs:			int ms (Number of millisecs to busy wait)
outputs:
notes:			Busy wait, not very accurate. Make sure (external)
clock value is set. This is used by _delay_ms inside
util/delay.h
Version :    	DMK, Initial code
*******************************************************************/
void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

volatile int led = 1;

/*****************************************************************
short:			ISR INT0
inputs:
outputs:
notes:			Set PORTD.5
Version :    	DMK, Initial code
*******************************************************************/
ISR( INT0_vect ) {
	if(led >= 1<<7)
	{
		led = 1;
	}
	led = led << 1;
	PORTC = (led);
	
}

/******************************************************************
short:			ISR INT1
inputs:
outputs:
notes:			Clear PORTD.5
Version :    	DMK, Initial code
*******************************************************************/
ISR( INT1_vect ) {
	if(led <= 1)
	{
		led = 1<<7;
	}
	led = led >> 1;
	PORTC = (led);
	
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
void display( int digit );

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

int main( void ) {
	opdracht3();
	return 1;
}

void opdracht3(){
	DDRC = 0xFF;
	while(1){
		for (int i = -1; i < 17; i++)
		{
			if(button1Pressed && button2Pressed){
				
			}else if(button1Pressed){
				
			}else if(button2Pressed){
				
			}
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
		PORTD ^= (1<<7);	// Toggle PORTD.7
		wait( 500 );
	}
}