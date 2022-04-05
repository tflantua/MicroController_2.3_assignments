/*
* _8t7seg.c
*
* Created: 05/04/2022 11:37:15
*  Author: rick
*/
#include <stdio.h>
#include <xc.h>
#include <avr/io.h>
#include "8t7seg.h"
#include "../SPI/SPI.h"
#include "../waiting.h"

#define slaveAddress 0

// Initialize the driver chip (type MAX 7219)
void Eight7seg_Init()
{
	DDRB=0x01;					  	// Set PB0 pin as output for display select
	spi_masterInit();
	
	spi_slaveSelect(slaveAddress);				// Select display chip (MAX7219)
	spi_write(0x09);      			// Register 09: Decode Mode
	spi_write(0xFF);				// 	-> 1's = BCD mode for all digits
	spi_slaveDeSelect(slaveAddress);			// Deselect display chip

	spi_slaveSelect(slaveAddress);				// Select display chip
	spi_write(0x0A);      			// Register 0A: Intensity
	spi_write(0x04);    			//  -> Level 4 (in range [1..F])
	spi_slaveDeSelect(slaveAddress);			// De select display chip

	spi_slaveSelect(slaveAddress);				// Select display chip
	spi_write(0x0B);  				// Register 0B: Scan-limit
	spi_write(0x07);   				// 	-> 1 = Display digits 0..1
	spi_slaveDeSelect(slaveAddress);			// Deselect display chip
	
	Eight7seg_displayOn();
	Eight7seg_reset();
}

void Eight7seg_blink(int times){
	for (int i=0; i < times; i++)
	{
		Eight7seg_displayOff();
		waitFunction(300);
		Eight7seg_displayOn();
		waitFunction(300);
	}
}

void Eight7seg_reset(){
	for (int i = 1; i < 9; i++)
	{
		Eight7seg_writeToDisplay(i, 10);
	}
}

// Set display on ('normal operation')
void Eight7seg_displayOn()
{
	spi_slaveSelect(slaveAddress);				// Select display chip
	spi_write(0x0C); 				// Register 0B: Shutdown register
	spi_write(0x01); 				// 	-> 1 = Normal operation
	spi_slaveDeSelect(slaveAddress);			// De select display chip
}

// Set display off ('shut down')
void Eight7seg_displayOff()
{
	spi_slaveSelect(slaveAddress);				// Select display chip
	spi_write(0x0C); 				// Register 0B: Shutdown register
	spi_write(0x00); 				// 	-> 1 = Normal operation
	spi_slaveDeSelect(slaveAddress);			// De select display chip
}

void Eight7seg_writeToDisplay(char display, char number){
	
	if(display < 1 || display > 8) return;
	
	spi_slaveSelect(slaveAddress); 		// Select display chip
	spi_write(9 - display);  		// 	digit address: (digit place)
	spi_write(number);			// 	digit value: 0
	spi_slaveDeSelect(slaveAddress);		// Deselect display chip
}