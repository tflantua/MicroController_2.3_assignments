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

volatile int remainingTime = 30;
static int beepOn = 0;

static void (*alarmCallback)(void) = NULL;

void Timer_init(void (*_alarmCallback)(void), int _remainingTime){
	alarmCallback = _alarmCallback;
	remainingTime = _remainingTime;
	OCR1B = 31500;			// 16-bits compare value of counter 1
	TIMSK |= BIT(4);		// T1 compare match A interrupt enable
	sei();
	TCCR1B = 0b00001100;	// compare output disconnected, CTC, RUN
}

void Timer_deInit(){
	TIMSK &= ~(BIT(4));		// T1 compare match A interrupt enable
}



ISR(TIMER1_COMPb_vect) {
	remainingTime--;
	
	if(remainingTime % 10){
		beepOn =0;
		Buzzert_start();
	}
	else{
		beepOn =1;
		Buzzert_stop();
	}
	
	if (remainingTime < 1){
		Timer_deInit();
		alarmCallback(); 
	}
}
