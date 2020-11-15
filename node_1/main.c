/*
 * TTK4155 Byggern prosjekt.c
 *
 * Created: 27.08.2020 08:45:11
 * Author : thomhagl
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <time.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/pgmspace.h>

#include "config.h"
#include "../uart_printf/UART_driver.h"

#include "../test/test.h"
#include "../sram/SRAM.h"
#include "../adc/adc_driver.h"
#include "../joystick/joystick.h"
#include "../oled/oled_driver.h"
#include "../oled/menu_driver.h"
#include "../can/mcp2515.h"
#include "../can/can.h"
#include "../can/mcp2515_driver.h"


void main(void){
	
	// Init: Assignent 1
	USART_init(MYUBRR);
	
	// Init: Assignent 2
	SRAM_init();

	// Init: Assignent 3
	adc_init();
	adc_clock_signal();
	joystick_init();
	
	int button_l = 0;
	int button_r = 0;
	int button_joy = 0;
	
	joystick_position j_position;
	slider_position s_position;
	
	// Init: Assignent 4
	oled_init();
	oled_reset();
	oled_pos(0,0);
	
	menu_init();
	update_currentmenu();
	
	
	// Init: Assignent 5
	can_init();

	can_message send_message, receive_message, test_message;
	send_message.id = 0;
	send_message.length = 6;
	
	test_message.id = 0;
	test_message.length = 1;
	test_message.data = 1;
	
	// Init: Assignent 8
	int highscore = 0;

	// Start message for the game
	oled_print("Welcome to this");
	oled_pos(1,0);

	oled_print("fabulous game by");
	oled_pos(2,0);

	oled_print("group 17! :)");

	// After some time, the game starts
	_delay_ms(25000);
	
	
	// Display menu for start of the game
	
	/*
	while(game_started())
		{
			oled_reset();
			show_menu();
			update_currentmenu();
			_delay_ms(100);
		}
	*/
	
	// Reset oled display	
	oled_reset();

	while(1)
		{
		
		// Assignment 1
		
		/*
		
		test_program();
		printf("Hello World!");
		
		*/
		
		// Assignment 2
		
		/*
		
		SRAM_test();
		
		*/
		
		// Assignment 3
		
		/*
		
		j_position = joystick_pos();
		j_position = joystick_direction();
		s_position = joystick_slider_position();
		
		//Buttons
		if (joystick_button(0)){
			button_l = 1;
		}
		if (joystick_button(0)==0){
			button_l = 0;
		}
		if (joystick_button(1)){
			button_r = 1;
		}
		if (joystick_button(1)==0){
			button_r = 0;
		}
		if (joystick_button(2)){
			button_joy = 1;
		}
		if (joystick_button(2)==0){
			button_joy = 0;
		}
		
		// Print joystick
		printf("Joystick-x: %d, Joystick-y: %d \n\r", j_position.position_x, j_position.position_y);
		
		// Print direction
		printf("Direction: %d \n\r", j_position.dir);
		
		// Print sliders
		printf("Slider-left: %d, Slider-right: %d \n\r", s_position.position_left, s_position.position_right);
		
		// Print Button:
		printf("Left button: %d, Right Button: %d, Joystick Button: %d", button_l, button_r, button_joy);
		
		*/
		
		// Assignment 4
		
		/*
		
		// Run start game screen
		printf("%s \n \r", current_menu.name);
		
		*/
		
		// Assignment 5
		
		/*
		
		can_send(&test_message);
		can_receive(&test_message);
		
		printf("Data: %d \n\r", test_message.data[0]);
		
		*/
		
		// Assignment 6, 8 and main game
		
		/*
		
		send_message.data[0] = adc_read(0);
		send_message.data[1] = adc_read(1);
		send_message.data[2] = adc_read(3);
		send_message.data[3] = adc_read(2);
		send_message.data[4] = button_joy;
		
		can_send(&send_message);
	
		*/
		
	
	}
	
}
