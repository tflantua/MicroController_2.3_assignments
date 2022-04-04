/*
 * ADCLaserIO.c
 *
 * Created: 04/04/2022 15:16:44
 *  Author: rick
 */ 

#include <xc.h>
#include <avr/interrupt.h>
#include "LCD.H"
#include "ADCLaserIO.h"

//Callback function triggered by interrupt of the ADC
static void (*callback)(uInt16) = NULL;

static void adc_init();
static void adc_deinit();

void ADCLaserIO_start(void (*_ptr)(uInt16)){
	callback = _ptr;
	adc_init();
	
	TCCR0=(5<<CS00);
	TIMSK=(1<<TOIE0);
	
	//Set port F1 to input
	DDRF &= ~(0x02);
	//Set port D0 to output
	DDRD |= 0x01;
	//Set port D0 high
	PORTD |= 0x01;
	
	//Enable global interrupts
	sei();
}

static void ADCLaserIO_stop(){
	adc_deinit();
	PORTD &= ~(0x01);
}

static void adc_init()
{
	//Vref=5V
	//channel 1 at pin PF1
	ADMUX=0b11100001;
	// ADSC=1 ADC Enable
	// ADPS[2:0]=111, prescaler=128
	// ADIE=1, ADC interrupt Enable
	//ADATE=1, ADC Auto Triggering Enable
	ADCSRA=(1<<ADEN)|(6<<ADPS0)|(1<<ADSC)|(1<<ADIE)|(1<<ADFR);
	
	//ADTS[2:0]= 100 , Timer0 overflow select as trigger source
	SFIOR=(4<<5);
}

static void adc_deinit(){
	ADMUX = 0x00;
	ADCSRA = 0x00;
	SFIOR = 0x00;
}

/* 
	Interrupt service routine for ADC to check if
	laser has been interrupted.
*/
ISR(ADC_vect){
	//Calculates the light value in percentages
	uInt16 value = (ADC) / 655;
	
	if (value < TRIGGER_VALUE){
		ADCLaserIO_stop();
		callback(value);
	}
}

/* 
	Necessary timer.
*/
ISR(TIMER0_OVF_vect){}