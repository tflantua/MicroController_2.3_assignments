/*
 * Buzzert.h
 *
 * Created: 05/04/2022 15:29:58
 *  Author: rick
 */ 
// Initialize timer 1: fast PWM at pin PORTB.6 (hundredth ms)

#ifndef Buzzert
#define Buzzert

void Buzzert_init();

void Buzzert_start();

void Buzzert_stop();

#endif

