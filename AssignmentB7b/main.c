/*
 * main.c
 *
 * Created: 2/8/2022 12:42:06 PM
 *  Author: thoma
 */ 

#include <xc.h>
#include <util/delay.h>

void waitFunction( int ms )
/* 
short:			Busy wait number of millisecs
inputs:			int ms (Number of millisecs to busy wait)
outputs:	
notes:			Busy wait, not very accurate. Make sure (external)
				clock value is set. This is used by _delay_ms inside
				util/delay.h
***********************/
{
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

void setCharliePlexingLed(int lednr);

int main(void)
{
    while(1)
    {
        setCharliePlexingLed(0);
		waitFunction(5000);
		setCharliePlexingLed(1);
		waitFunction(5000);
//		setCharliePlexingLed(2);
//		waitFunction(500);
//		setCharliePlexingLed(3);
//		waitFunction(5000);
//		setCharliePlexingLed(4);
//		waitFunction(5000);
//		setCharliePlexingLed(5);
//		waitFunction(5000);
    }
	
	return 0;
}

void setCharliePlexingLed(int lednr) 
{
	
	
	switch (lednr)
	{
		case 0:
		DDRD = 0x03;
		PORTD = 0x01;
		break;
		case 1:
		DDRD = 0x03;
		PORTD = 0x02;
		break;
		case 2:
		DDRD = 0x06;
		PORTD = 0x02;
		break;
		case 3:
		DDRD = 0x06;
		PORTD = 0x04;
		break;
		case 4:
		DDRD = 0x05;
		PORTD = 0x04;
		break;
		case 5:
		DDRD = 0x05;
		PORTD = 0x01;
		break;
	}
}