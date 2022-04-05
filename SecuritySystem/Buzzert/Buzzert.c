/*
 * Buzzert.c
 *
 * Created: 05/04/2022 15:30:07
 *  Author: rick
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Buzzert.h"

#define INTERVAL  		2273

// Initialize timer 1: fast PWM at pin PORTB.6 (hundredth ms)
void Buzzert_init(){	
	ICR1 = INTERVAL;				// TOP value for counting = INTERVAL*us
	OCR1A = INTERVAL/2;				// compare value in between	
}

void Buzzert_start()
{
	TCCR1A = 0b10000010;			// timer, compare output at OC1A=PB5
	TCCR1B = 0b00001011;			// fast PWM, TOP = ICR1, prescaler=8 (1MHz), RUN
}

void Buzzert_stop(){
	TCCR1A = 0;
	TCCR1B = 0;
}

