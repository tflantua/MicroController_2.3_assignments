/*
* main.c
*
* Created: 3/23/2022 2:11:34 PM
*  Author: thoma
*/

#include <xc.h>
#include <avr/interrupt.h>
#include "waiting.h"
#include "LCD/LCD.h"
#include "ADCLaser/ADCLaserIO.h"
#include "Keypad/Keypad.h"
#include "8t7seg/8t7seg.h"
#include "Timer/Timer.h"
#include "Buzzert/Buzzert.h"

#define  timeBeforeAlarm 20

void main_alarm(){
	lcd_clear();
	char text[] = "Alarm";
	display_text(text);
	
	Buzzert_start();
}

void main_laserCallback(uInt16 value){
	lcd_clear();
	char text[] = "Triggered";
	display_text(text);
	
	Timer_init(main_alarm, timeBeforeAlarm);
}

void main_start_laser(){
	ADCLaserIO_start(main_laserCallback);
}

void main_lcd_locked(){
	lcd_clear();
	char text[] = "locked";
	display_text(text);
	Timer_init(main_start_laser, 10);
}

void main_lcd_unlocked(){
	lcd_clear();
	char text[] = "unlocked";
	display_text(text);
	
	Timer_deInit();
	Buzzert_stop();
}

void main_lcd_wrongCode(){
	lcd_clear();
	char text[] = "wrong code try again";
	display_text(text);
}


int main(void)
{
	lcd_init();
	
	DDRB = 0xFF;					// set PORTB for compare output
	DDRA = 0xFF;					// set PORTA for output in main program
	Buzzert_init();
	Buzzert_start();
	
	Eight7seg_Init();
	Keypad_init(main_lcd_locked, main_lcd_unlocked, main_lcd_wrongCode);
	
	main_lcd_unlocked();
	
	while(1){
		Keypad_checkKey();
		waitFunction(100);
	}
}