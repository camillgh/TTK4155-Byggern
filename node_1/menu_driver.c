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

	start_game.name = "Start Game";
	start_game.parent = &main;
	start_game.children[0] = NULL;
	
	current_menu = main;

	game_status = 0;
	
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
	//oled_print(current_menu.name);

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
 
 
void navigate_menu(int button_l, int button_r){
	//Move the cursor
	
	int deadzone = 63;
	
	if ((button_l) && (cursor_page != 2)){
		cursor_page--;
		_delay_ms(1000);
		
	}
	if ((button_r) && (cursor_page != 4)){
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
	
	if (current_menu.name == "Start Game"){
		oled_reset();
		oled_pos(1,0);
		oled_print("The game has");
		oled_pos(2,0);
		oled_print("started!");
		_delay_ms(25000);
		oled_reset();
		game_status=1;
	}
	
	/*
	// Go back from submenu
	if (test_bit(PINB, PINB2) && current_menu.parent != NULL){
		current_menu = *current_menu.parent;
		cursor_page = 2;
		printf("We are going back to: %s \n\r", current_menu.name);
	}
	*/
}

uint8_t game_started(void){
	if (game_status == 1){
		return 0;
	}
	else{
		return 1;
	}
}