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

int main(void)
{
	DDRD = 0xFF;
	
    while(1)
    {
        PORTD = 0xAA;
        waitFunction(2000);
        PORTD = 0x55;
        waitFunction(2000);
    }
	
	return 1;
}