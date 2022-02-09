
/*
 * LCD.H
 *
 * Created: 09/02/2022 11:23:51
 *  Author: Test
 */ 

#ifndef (LCD_Module)
#define LCD_Module

void init();
void display_text(char *str);
void display_text(char str[]);
void set_cursor(int position); 

#endif
