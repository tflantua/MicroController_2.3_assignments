/*
* main.c
*
* Created: 3/23/2022 2:11:34 PM
*  Author: thoma
*/

#include <xc.h>
#include "waiting.h"
#include "LCD.H"
#include <avr/interrupt.h>

void adc_init()// ADC configuration
{
	ADMUX=0b11100001;//Vref=AVcc
	// ADSC=1 ADC Enable
	// ADPS[2:0]=111, prescaler=128
	// ADIE=1, ADC interrupt Enable
	//ADATE=1, ADC Auto Triggering Enable
	ADCSRA=(1<<ADEN)|(6<<ADPS0)|(1<<ADSC)|(1<<ADIE)|(1<<ADFR);
	
	//ADTS[2:0]= 100 , Timer0 overflow select as trigger source
	SFIOR=(4<<5);
}

void adc_deinit(){
	ADMUX = 0x00;
	ADCSRA = 0x00;
	SFIOR = 0x00;
}
unsigned long int waarde;
char text_print[20];
ISR(ADC_vect) {
	lcd_clear();
	
	waarde =(ADC) / 655;
	
	if (waarde < 80){
		char text[] = "Triggered";
		display_text(text);
		
		adc_deinit();
	}
	waitFunction(100);
}

ISR(TIMER0_OVF_vect){
	
}

int main(void)
{
	DDRC = 0xFF;			// PORTD(7) output, PORTD(6:0) input
	PORTC = 0xFF;
	init();
	
	DDRF = 0x00;
	DDRA = 0xFF;
	DDRB = 0xFF;
	
	//ADC interrupts
	adc_init();
	
	TCCR0=(5<<CS00);
	TIMSK=(1<<TOIE0);
	
	sei();
	
	//Testing for waarde from light resistor
	unsigned long int waarde;
	long l = 0;
	long h  = 0;
	
	DDRD = 0x00;
	while(1){
		//l = ADCL;
		//h  = ADCH;
		//PORTA = l;
		//PORTB = h;
		//
		//waarde = ((h << 8) | l) / 650;
		//
		//sprintf(text_print, "waarde %lu", waarde);
		//
		//display_text(text_print);
		//waitFunction(100);
		//
		//lcd_clear();
		
		waitFunction(100);
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