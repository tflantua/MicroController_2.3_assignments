/*
 * waiting.c
 *
 * Created: 05/04/2022 12:53:41
 *  Author: rick
 */ 

#define F_CPU 8e6

#include <util/delay.h>
#include "waiting.h"

void waitFunction( int ms )
/* 
short:			Busy wait number of millisecond
inputs:			int ms (Number of millisecond to busy wait)
outputs:	
notes:			Busy wait, not very accurate. Make sure (external)
				clock value is set. This is used by _delay_ms inside
				until/delay.h
***********************/
{
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}
