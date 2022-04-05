/*
 * _8t7seg.h
 *
 * Created: 05/04/2022 11:36:55
 *  Author: rick
 */ 
#ifndef Eight7seg
#define Eight7seg

void Eight7seg_Init();

// Set display on ('normal operation')
void Eight7seg_displayOn();

// Set display off ('shut down')
void Eight7seg_displayOff();

void Eight7seg_writeToDisplay(char display, char number);

void Eight7seg_reset();

void Eight7seg_blink(int times);

#endif
