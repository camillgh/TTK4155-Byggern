#include <avr/io.h>
#include <avr/pgmspace.h>
#include <time.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include "fonts.h"
#include "oled_driver.h"


volatile char *oled_command = (char *) 0x1000;
volatile char *oled_data = (char *) 0x1200;

const int FONTWIDTH = 4;
uint8_t col, page;


void oled_init(void){
	// Enable external memory
	MCUCR |= (1 << SRE);
	SFIOR |= (1 << XMM2);
	
	// Display off
	*oled_command = 0xAE;
	
	//Segment remap
	*oled_command = 0xA1;
	
	//Common pads hardware: alternative
	*oled_command = 0xDA;
	*oled_command = 0x12;
	
	// Common output scan direction: com63~com0
	*oled_command = 0xC8;
	
	// Mulitplex ration mode: 63
	*oled_command = 0xA8;
	*oled_command = 0x3F;
	
	// Display divide ratio/osc. freq. mode
	*oled_command = 0xD5;
	*oled_command = 0x80;
	
	// Contrast control
	*oled_command = 0x81;
	*oled_command = 0x50;
	
	// Set pre-charged period
	*oled_command = 0xD9;
	*oled_command = 0x21;
	
	// Set Memory Adressing mode
	*oled_command = 0x20;
	*oled_command = 0x02;
	
	// VCOM deselect level mode
	*oled_command = 0xDB;
	*oled_command = 0x30;
	
	// Master configuration 
	*oled_command = 0xAD;
	*oled_command = 0x00;
	
	// Out follows RAM content
	*oled_command = 0xA4;
	
	// Set normal display 
	*oled_command = 0xA6;
	
	// Display On
	*oled_command = 0xAF;
	
	//Set page start address
	*oled_command = 0xB0;
	//Set lower column start address
	*oled_command = 0x00;
	//Set higher column start address
	*oled_command = 0x10;
	
	oled_clear();
	oled_home();
	
	
	
}

void oled_write(void){
	*oled_data = 0b01000010;
	*oled_data = 0b01000010;
	*oled_data = 0b01111111;
	*oled_data = 0b01111111;
	*oled_data = 0b01000000;
	*oled_data = 0b01000000;
	*oled_data = 0b00000000;
	*oled_data = 0b00000000;
}

int oled_write_char(char c){
	for (int i = 0; i < FONTWIDTH; i++){
		*oled_data = pgm_read_byte(&font4[c-' '][i]);
	}
	return 0;
}

// int oled_write(char *c){
// 	int i = 0;
// 	
// 	while (c[i] != '/0'){
// 		oled_write_char(c[i]);	
// 		
// 		i++;
// 	}
// 	return 0;	
// };

int oled_home(void) {
	//Reset the page and column
	page = 0;
	col = 0;
	
	//Set the cursor to the start of the screen
	*oled_command = 0x21;
	*oled_command = 0x00;
	*oled_command = 0x7F;
	
	*oled_command = 0x22;
	*oled_command = 0x00;
	*oled_command = 0x7;
	
	return 0;
	
}

int oled_clear(void) {
	//Clear every page
	for (uint8_t k = 0; k < 8; k++) {
		oled_clear_line(k);
	}
	
	return 0;
}

int oled_clear_line(uint8_t line) {
	oled_goto_line(line);
	
	//Clear the page
	for (int i = 0; i < 128; i++) {
		*oled_data=0x00;
	}
	
	oled_home();
	
	return 0;
}



int oled_goto_line(uint8_t line) {
	oled_home();
	
	//Check if it's a valid page
	if (line < 8) {
		//Save the page we are moving to
		page = line;
		//Set lower column address
		*oled_command = 0x00;
		//Set higher column address
		*oled_command = 0x10;
		//Set page address
		*oled_command = 0xB0 | line;
	}

	return 0;
}

int oled_pos(uint8_t line, uint8_t column) {
	
	oled_goto_line(line);
	
	//Check if it's a valid column according to the font
	if (column < (128/FONTWIDTH)) {
		//Save the column we are moving to
		col = column*FONTWIDTH;
		//Set lower column start address
		*oled_command = 0x00 + (column*(FONTWIDTH)>>4);
		//Set higher column start address
		*oled_command = 0x10 + (column*(FONTWIDTH)>>4);
	}
	
	return 0;
}


