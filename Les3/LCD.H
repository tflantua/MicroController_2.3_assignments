
/*
 * LCD.H
 *
 * Created: 09/02/2022 11:23:51
 *  Author: Test
 */ 

#ifndef LCD_Module
#define LCD_Module


#define F_CPU 8e6
#include <stdio.h>
#include <util/delay.h>
#include <avr/io.h>

void init();
void display_text(char *str);
void set_cursor(int position); 
void lcd_clear(void);
void wait(int ms);

#endif
