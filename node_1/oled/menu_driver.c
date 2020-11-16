#include <avr/io.h>
#include <avr/pgmspace.h>
#include <time.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

#include "../oled/oled_driver.h"
#include "../joystick/joystick.h"
#include "../oled/menu_driver.h"
#include "config.h"
#include "../adc/adc_driver.h"

#include <util/delay.h>

menu main, start_game;
uint8_t cursor_page; 

/**
 * \brief oled initialization
 *
 *
 * \param void
 * \retval void
 */



// Set start display
void menu_init(void){
	main.name = "Main Menu";
	main.parent = NULL;
	main.children[0] = &start_game;

	start_game.name = "Start Game";
	start_game.parent = &main;
	start_game.children[0] = NULL;
	
	current_menu = main;
	
	cursor_page = 2;
};


/**
 * \brief Command to show current menu
 *
 *
 * \param void
 * \retval void
 */


// Show current menu
int show_menu(void){

	oled_reset();

	oled_home();

	menu child;
	
	// Display all menus
	int i = 0;
	while (current_menu.children[i] != NULL){
		
		oled_pos(i+2,0);
		menu *child = current_menu.children[i];
		oled_print(child->name);
		//oled_print(current_menu.children[i]->name);
		i++;		
	}
	
	// Arrow indicating position of cursor
	oled_pos(cursor_page, 10);
	oled_print(" <--");
	
	return 0;
};

/**
 * \brief Command to navigate current menu
 *
 *
 * \param button_l navigate down using left touch button
 * \param button_r navigate up using right touch button
 * \retval void
 */

 
// Navigate menu using sliders
void navigate_menu(int button_l, int button_r){
	
	//Move the cursor
	
	if ((button_l) && (cursor_page != 2)){
		cursor_page--;
		_delay_ms(1000);
		
	}
	if ((button_r) && (cursor_page != 4)){
		cursor_page++;
		_delay_ms(1000);
	}

}

/**
 * \brief command to update menu using joystick button
 *
 *
 * \param void
 * \retval void
 */


//Function that updates currentmenu from buttonpresses
void update_currentmenu(void){
	
	// Go into submenu
	if (!test_bit(PINB, PINB3) && current_menu.children[cursor_page-2] != NULL){
		current_menu = *current_menu.children[cursor_page-2]; //The two first pages are the header and a whitespace
		cursor_page = 2;
		printf("We are entering the submenu: %s \n\r", current_menu.name);
	}
	
}
