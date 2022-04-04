/*
* main.c
*
* Created: 3/23/2022 2:11:34 PM
*  Author: thoma
*/

#define TRIGGER_VALUE 80

#include <xc.h>
#include "waiting.h"
#include "LCD.H"
#include "ADCLaserIO.h"

void main_lcd_print(uInt16 value){
	lcd_clear();
	char text[] = "Triggered";
	display_text(text);
}

void init_keyPad(){
	DDRA &= ~(0x07);
}

int passcode[4] = {1, 0, 1, 0};
int inputcode[4];

int currentNumber = 0;
int side = 0;
int inputIndex = 0;

int locked = 1;

void unlock(){
	for (int i = 0; i < 4; i++)
	{
		if (inputcode[i] != passcode[i]){
			return;
		}
	}
	
	ADCLaserIO_stop();
	locked = 0;
}

void checkKey(){
	int keys = PINA & 0x7;
	if(locked == 0)
	{
		if(keys & 4){
		locked = 1;
		ADCLaserIO_start(main_lcd_print);
		}
		
		//enable laser
		
		return;
	}
	
	if(keys & 1){
		if(side != 0){
			if(inputIndex >= 4){
				unlock();
				return;
			}
			side = 0;
			inputcode[inputIndex] = currentNumber;
			inputIndex++;
		}
		currentNumber++;
		if(currentNumber > 9){
			currentNumber = 0;
		}
		}else if(keys & 2){
		if(side != 1){
			if(inputIndex >= 4){
				unlock();
				return;
			}
			side = 1;
			inputcode[inputIndex] = currentNumber;
			inputIndex++;
		}
		currentNumber--;
		if(currentNumber < 0){
			currentNumber = 9;
		}
		
		}else if(keys & 4){
		inputIndex = 0;
		return;
	}
	
}

int main(void)
{
	lcd_init();
	ADCLaserIO_start(main_lcd_print);
	init_keyPad();
	char test[15];
	while(1){
		checkKey();
		sprintf(test, "c:%d l:%d, in%d", currentNumber, locked, inputIndex);
		lcd_clear();
		display_text(test);
		waitFunction(100);
	}
}