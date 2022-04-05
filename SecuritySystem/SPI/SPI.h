/*
 * SPI.h
 *
 * Created: 05/04/2022 11:42:01
 *  Author: rick
 */ 

#ifndef SPI
#define SPI

void spi_masterInit(void);
void spi_write( unsigned char data );
char spi_writeRead( unsigned char data );
void spi_slaveSelect(unsigned char chipNumber);
void spi_slaveDeSelect(unsigned char chipNumber);

#endif
