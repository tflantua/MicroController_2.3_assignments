/*
* main.c
*
* Created: 2/8/2022 12:42:06 PM
*  Author: thoma
*/

#define F_CPU 8e6

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
		for (int i = 0; i < 6; i++)
		{
			setCharliePlexingLed(i);
			waitFunction(500);
		}
	}
	
	return 0;
}

typedef struct {
	int ddr;
	int port;
} LED_SETTINGS;

LED_SETTINGS leds[6] = {
	{0x03, 0x01},
	{0x03, 0x02},
	{0x06, 0x02},
	{0x06, 0x04},
	{0x05, 0x04},
	{0x05, 0x01},
};

void setCharliePlexingLed(int lednr)
{
	DDRD = leds[lednr].ddr;
	PORTD = leds[lednr].port;
}