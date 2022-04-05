/*
 * ADCLaserIO.h
 *
 * Created: 04/04/2022 15:21:57
 *  Author: rick
 */ 
#ifndef ADCLaserIO
#define ADCLaserIO

typedef unsigned long int uInt16;

/************************************************************************/
/* _ptr is a function pointer called when below TRIGGER value threshold */
/************************************************************************/
void ADCLaserIO_start(void (*_ptr)(uInt16));

void ADCLaserIO_stop();
#endif
