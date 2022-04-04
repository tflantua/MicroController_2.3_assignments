/*
* main.c
*
* Created: 3/23/2022 2:11:34 PM
*  Author: thoma
*/

#include <xc.h>
#include "waiting.h"
#include "LCD.H"
#include "ADCLaserIO.h"

void main_lcd_print(uInt16 value){
	lcd_clear();
	char text[] = "Triggered";
	display_text(text);
}

int main(void)
{
	lcd_init();
	ADCLaserIO_start(main_lcd_print);
	
	while(1){
		waitFunction(100);
	}
}