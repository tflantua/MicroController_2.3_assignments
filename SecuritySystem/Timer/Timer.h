/*
 * Timer.h
 *
 * Created: 05/04/2022 13:26:34
 *  Author: rick
 */ 

#ifndef Timer
#define Timer

void Timer_init(void (*_alarmCallback)(void), int _remainingTime);
void Timer_deInit();

#endif
