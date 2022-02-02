/*
 * main.c
 *
 * Created: 2/2/2022 11:11:23 AM
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

int opdracht2();
int opdracht3();
int opdracht4();
int opdracht5();
int opdracht6();

int main(void)
{
	return opdracht6();
}

int opdracht2()
{
		DDRD = 0xFF;
		
		while(1)
		{
			PORTD = 0x80;
			waitFunction(5000);
			PORTD = 0x40;
			waitFunction(5000);
		}
		
		return 1;
}

int opdracht3()
{
	DDRD = 0xFF;
	PORTC = 0x10;
	
	while (1)
	{
		PORTD = PINC << 7;
		waitFunction(5000);
		PORTD = 0x00;
		waitFunction(5000);
	}
	
	return 1;
}

int opdracht4()
{
	DDRD = 0xFF;
	
	while (1)
	{
		for (int i = 0; i < 8; i++)
		{
			PORTD = 0x01 << i;
			waitFunction(500);
		}
		
		for (int i = 0; i < 8; i++)
		{
			PORTD = 0x80 >> i;
			waitFunction(500);
		}
	}
	
	return 1;
}

int opdracht5()
{
	DDRD = 0xFF;
	
	char pattern[] = {0x01, 0x04, 0x10, 0x40, 0xFF, 0x00, 0xFF, 0xAA};
		
	while(1)
	{
		for (int i = 0; i < sizeof(pattern); i++)
		{
			PORTD = pattern[i];
			waitFunction(1000);
		}
	}
	
	return 1;
}

int checkButton(int ms)
{
	const int oneHrz = 10000;
	const int fourHrz = oneHrz/4;
	
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	
	if (PINC & 0x01)
	{
		if (ms == oneHrz) ms = fourHrz;
		else ms = oneHrz;
	}
	}
	return ms;
}

int opdracht6()
{	
	int ms = 10000;
	DDRD = 0xFF;
	PORTC = 0x10;
	
	while(1)
	{
		PORTD = 0x80;
		ms = checkButton(ms);
		PORTD = 0x00;
		ms = checkButton(ms);
	}
	
	return 1;
}