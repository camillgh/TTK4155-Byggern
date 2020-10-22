#include <avr/io.h>
#include <avr/pgmspace.h>
#include <time.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include "oled_driver.h"
#include "joystick.h"
#include "menu_driver.h"
#include "config.h"
#include "adc_driver.h"

#include <util/delay.h>

menu main, start_game, options, high_score;
uint8_t cursor_page;

void menu_init(void){
	main.name = "Main Menu";
	main.parent = NULL;
	main.children[0] = &start_game;
	main.children[1] = &options;
	main.children[2] = &high_score;
	main.children[3] = NULL;

	start_game.name = "Start Game";
	start_game.parent = &main;
	start_game.children[0] = NULL;
	start_game.children[1] = NULL;
	start_game.children[2] = NULL;

	options.name = "Options";
	options.parent = &main;
	options.children[0] = NULL;
	options.children[1] = NULL;
	options.children[2] = NULL;

	high_score.name = "High Scores";
	high_score.parent = &main;
	high_score.children[0] = NULL;
	high_score.children[1] = NULL;
	high_score.children[2] = NULL;
	
	current_menu = main;
	cursor_page = 2;
};


int show_menu(void){
	oled_reset();
	oled_home();
	
	/*
	if (current_menu.name == "Main Menu"){
		oled_pos(0,0);
		oled_print(main.name);

		oled_pos(2,0);
		oled_print(start_game.name);
			
		oled_pos(3,0);
		oled_print(options.name);

		oled_pos(4,0);
		oled_print(high_score.name);
	}
	
	if (current_menu.name == "Start Game"){
		oled_pos(0,0);
		oled_print(start_game.name);

		oled_pos(2,0);
		oled_print("Let's go!");
		
	}
	
	if (current_menu.name == "Options"){
		oled_pos(0,0);
		oled_print(options.name);

		oled_pos(2,0);
		oled_print("Nothing here!");
		}
	
	if (current_menu.name == "High Score"){
		oled_pos(0,0);
		oled_print(high_score.name);

		oled_pos(2,0);
		oled_print("The winners:");
		
		oled_pos(3,0);
		oled_print("ME");
		
		oled_pos(4,0);
		oled_print("MEE");
	}
	
	*/
	oled_print(current_menu.name);

	menu child;
	
	
	int i = 0;
	while (current_menu.children[i] != NULL){
		oled_pos(i+2,0);
		menu *child = current_menu.children[i];
		oled_print(child->name);
		//oled_print(current_menu.children[i]->name);
		i++;		
	}
	
	
	oled_pos(cursor_page, 10);
	oled_print(" <--");
	
	return 0;
};
 
void navigate_menu(joystick_position position){
	//Move the cursor
	
	int deadzone = 63;
	
	if ((position.position_y > deadzone ) && (cursor_page != 2)){
		cursor_page--;
		_delay_ms(1000);
		
	}
	if ((position.position_y < -deadzone) && (cursor_page != 4)){
		cursor_page++;
		_delay_ms(1000);
	}

	//current_menu = *current_menu.children[cursor_page-2]; //The two first pages are the header and a whitespace
}

//joystick_position joystick_direction(void){



//Function that updates currentmenu from buttonpresses
void update_currentmenu(void){
	
	// Go into submenu
	if (!test_bit(PINB, PINB3) && current_menu.children[cursor_page-2] != NULL){
		current_menu = *current_menu.children[cursor_page-2]; //The two first pages are the header and a whitespace
		cursor_page = 2;
		printf("We are entering the submenu: %s \n\r", current_menu.name);
	}
	
	// Go back from submenu
	if (test_bit(PINB, PINB2) && current_menu.parent != NULL){
		current_menu = *current_menu.parent;
		cursor_page = 2;
		printf("We are going back to: %s \n\r", current_menu.name);
	}

}
