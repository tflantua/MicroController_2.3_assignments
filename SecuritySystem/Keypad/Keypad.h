/*
 * Keypad.H
 *
 * Created: 05/04/2022 11:23:18
 *  Author: rick
 */ 
#ifndef Keypad
#define Keypad

void Keypad_init(void (*_locked)(), void (*_unlocked)(), void (*_wrongCode)());
void Keypad_checkKey();

#endif