/*
 * ADCLaserIO.h
 *
 * Created: 04/04/2022 15:21:57
 *  Author: rick
 */ 

#ifndef ADCLaserIO
#define ADCLaserIO

#define TRIGGER_VALUE 80

typedef unsigned long int uInt16;

void ADCLaserIO_start(void (*_ptr)(uInt16));

#endif
