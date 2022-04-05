/*
* Timer.c
*
* Created: 05/04/2022 13:26:21
*  Author: rick
*/

#include <xc.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "../Buzzert/Buzzert.h"

#define BIT(x) (1 << (x))

volatile long int remainingTime = 30;
volatile int msCount;

static void (*alarmCallback)(void) = NULL;

void Timer_init(void (*_alarmCallback)(void), int _remainingTime){
	alarmCallback = _alarmCallback;
	remainingTime = _remainingTime;
	msCount = 1000;
	OCR2 = 150; // Compare value of counter 2
	TIMSK |= BIT(7); // T2 compare match interrupt enable
	sei(); // turn_on intr all
	TCCR2 = 0b00001011; // Initialize T2: timer, prescaler=32, compare output disconnected,CTC,RUN
}

void Timer_deInit(){
	TIMSK &= ~(BIT(7));		// T1 compare match A interrupt enable
}

ISR( TIMER2_COMP_vect ) {
	msCount--; // Increment ms counter
	if(msCount <= 0){
		msCount = 1000;
		remainingTime--;
		if(remainingTime % 2){
			Buzzert_start();
		}else{
			Buzzert_stop();
		}
	}
	if ( remainingTime < 1) {
		Timer_deInit();
		alarmCallback();
	}
}
