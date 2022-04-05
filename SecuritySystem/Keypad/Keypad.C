/*
 * Keypad.C
 *
 * Created: 05/04/2022 11:23:05
 *  Author: rick
 */ 

#include <xc.h>
#include <stdio.h>
#include "Keypad.h"
#include "../ADCLaser/ADCLaserIO.h"
#include "../8t7seg/8t7seg.h"

#define rotateLeft -1
#define rotateRight 1


static void (*locked_callback)() = NULL;
static void (*unlocked_callback)() = NULL;
static void (*wrongCode_callback)() = NULL;

static const int passcode[4] = {1, 0, 1, 0};
static int inputcode[4];

static int currentNumber = 0;
static int side = 1;
static int inputIndex = 0;

static int locked = 1;

static void Keypad_rotate(int rotate);
static void Keypad_unlock();
static void Keypad_reset();

void Keypad_init(void (*_locked)(), void (*_unlocked)(), void (*_wrongCode)()){
	locked_callback = _locked;
	unlocked_callback = _unlocked;
	wrongCode_callback = _wrongCode;
	DDRA &= ~(0x07);
}

void Keypad_checkKey(){
	int keys = PINA & 0x7;
	if(locked == 0)
	{
		if(keys & 4){
			locked = 1;
			Keypad_reset();
			locked_callback();
			ADCLaserIO_start(NULL);
		}
		return;
	}
	
	if(keys & 1){
		Keypad_rotate(rotateRight);
		}else if(keys & 2){
		Keypad_rotate(rotateLeft);
		}else if(keys & 4){
		Eight7seg_reset();
		Keypad_reset();
		return;
	}
	
}

static void Keypad_reset(){
	inputIndex = 0;
	side = rotateRight;
	currentNumber = 0;
}

static void Keypad_rotate(int rotate){
	if(rotate > 0)
	rotate = rotateRight;
	else
	rotate = rotateLeft;
	
	if(side != rotate){
		if(inputIndex >= 3){
			Keypad_unlock();
			return;
		}
		side = rotate;
		inputcode[inputIndex] = currentNumber;
		inputIndex++;
	}
	
	
	currentNumber += rotate;
	if(currentNumber > 9){
		currentNumber = 0;
		}else if(currentNumber < 0){
		currentNumber = 9;
	}
	Eight7seg_writeToDisplay(inputIndex + 1, currentNumber);
}

static void Keypad_unlock(){
	
	Eight7seg_blink(3);
	Eight7seg_reset();
	Keypad_reset();
	
	for (int i = 0; i < 4; i++)
	{
		if (inputcode[i] != passcode[i]){
			wrongCode_callback();
			Eight7seg_reset();
			return;
		}
	}
	
	locked = 0;
	unlocked_callback();
	ADCLaserIO_stop();
}