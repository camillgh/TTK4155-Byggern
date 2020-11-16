#include <avr/io.h>
#include <avr/pgmspace.h>
#include <time.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include "fonts.h"
#include "oled_driver.h"

// Pointer with start adress for oled commands
volatile char *oled_command = (char *) 0x1000;

// Pointer with start adress for oled data
volatile char *oled_data = (char *) 0x1200;

const int FONTWIDTH = 8;

// Global variable to keep track of wich page and col we are on 
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
	
	// Clear screen
	oled_reset();

	// Set cursor to the start of the screen
	oled_home();
	
}

// Function to print a char
int oled_print_char(char c){

	// Convert char 
	int print_char = c-' ';
	
	// Print char on oled screen
	for (int i = 0; i < FONTWIDTH; i++){
		*oled_data = pgm_read_byte(&font8[print_char][i]);
	}
	
	return 0;
}

// Function to print a string on oled
void oled_print(char *c){
 	
	 int i = 0;
 	
	// Write the string on oled
 	while (i < strlen(c)){
 		oled_print_char(c[i]);
 		i++;

 	}	
}

int oled_home(void) {

	//Reset the global variables page and column
	page = 0;
	col = 0;

	//Set up column start and end address
	*oled_command = 0x21;
	*oled_command = 0x00;
	*oled_command = 0x7F;
	
	// Set up page start and end address
	*oled_command = 0x22;
	*oled_command = 0x00;
	*oled_command = 0x7;
	
	return 0;
	
}

// Function to reset every line
int oled_reset(void) {

	int line = 8;
	
	// Reset every line
	for (uint8_t i = 0; i < line; i++) {
		oled_clear_line(i);
	}
	return 0;
}

// Function to clear a line on oled
int oled_clear_line(uint8_t line) {

	// Go to line to be cleared
	oled_goto_line(line);
	
	//Clear the line
	for (int i = 0; i < 128; i++) {
		*oled_data=0x00;
	}
	
	// Set cursor to the start of the screen
	oled_home();

	return 0;

}


// Function to go to a specific line on oled
int oled_goto_line(uint8_t line) {
	
	//Set the global variable page 
	page = line;

	//Set lower column address
	*oled_command = 0x00;
	
	//Set higher column address
	*oled_command = 0x10;
	
	//Set page address
	*oled_command = 0xB0 + line;

	return 0;
}

// Function to go to a specific col and line on oled
int oled_pos(uint8_t line, uint8_t column) {
	
	// Go to line
	oled_goto_line(line);
	
	//Set the global variable col
	col = column;

	//Set lower column start address
	*oled_command = 0x00 + ((column*FONTWIDTH)>>4);
		
	//Set higher column start address
	*oled_command = 0x10 + ((column*FONTWIDTH)>>4);
	
	return 0;
}


