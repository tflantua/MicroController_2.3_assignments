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

#define  timeBeforeAlarm 30

void main_alarm(){
	lcd_clear();
	char text[] = "Alarm";
	display_text(text);
}

void main_laserCallback(uInt16 value){
	lcd_clear();
	char text[] = "Triggered";
	display_text(text);
	
	Timer_init(main_alarm, timeBeforeAlarm);
}

void main_lcd_locked(){
	lcd_clear();
	char text[] = "locked";
	display_text(text);
}

void main_lcd_unlocked(){
	lcd_clear();
	char text[] = "unlocked";
	display_text(text);
	
	Timer_deInit();
}

void main_lcd_wrongCode(){
	lcd_clear();
	char text[] = "wrong code try again";
	display_text(text);
}


int main(void)
{
	
	
	lcd_init();
	
	Eight7seg_Init();
	Keypad_init(main_lcd_locked, main_lcd_unlocked, main_lcd_wrongCode);
	
	ADCLaserIO_start(main_laserCallback);
	
	while(1){
		Keypad_checkKey();
		waitFunction(100);
	}
}