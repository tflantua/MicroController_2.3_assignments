//
///*
 //* LCD.C
 //*
 //* Created: 09/02/2022 11:25:25
 //*  Author: Test
 //*/ 
//
//#include "LCD.H"
//
//void init(){
	//// return home
	//lcd_command( 0x02 );
	//// mode: 4 bits interface data, 2 lines, 5x8 dots
	//lcd_command( 0x28 );
	//// display: on, cursor off, blinking off
	//lcd_command( 0x0C );
	//// entry mode: cursor to right, no shift
	//lcd_command( 0x06 );
	//// RAM adress: 0, first position, line 1
	//lcd_command( 0x80 );
//}
//
//void display_text(char *str){
	//lcd_writeChar(*str);
//}
//
//void display_text(char str[]){
	//int stringSize = (sizeof(str)/sizeof(char));
	//for (int i = 0; i < stringSize; i++)
	//{
		//lcd_writeChar(stringSize);
	//}
//}
//
//void set_cursor(int position){
	//
//}
//
//void lcd_writeChar( unsigned char dat ){
	//PORTC = dat & 0xF0; // hoge nibble
	//PORTC |= 0x0C; // data (RS=1),
	//// start(EN=1)
	//_delay_ms(1); // wait 1 ms
	//PORTC = 0x04; // stop (EN = 0)
	//PORTC = (dat & 0x0F) << 4; // lage nibble
	//PORTC |= 0x0C; // data (RS=1),
	//// start (EN=1)
	//_delay_ms(1); // wait 1 ms
	//PORTC = 0x00; // stop (EN=0 RS=0)
//}
//
//void lcd_command ( unsigned char dat ){
	//PORTC = dat & 0xF0; // hoge nibble
	//PORTC |= 0x08; // data (RS=0),
	//// start (EN=1)
	//_delay_ms(1); // wait 1 ms
	//PORTC = 0x04; // stop (EN = 0)
	//PORTC = (dat & 0x0F) << 4; // lage nibble
	//PORTC |= 0x08; // data (RS=0),
	//// start (EN=1)
	//_delay_ms(1); // wait 1 ms
	//PORTC = 0x00; // stop (EN=0 RS=0)
//}