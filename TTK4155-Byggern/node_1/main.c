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
#include "UART_driver.h"

#include "SRAM.h"
#include "adc_driver.h"
#include "joystick.h"
#include "oled_driver.h"
#include "menu_driver.h"
#include "mcp2515.h"
#include "can.h"
#include "mcp2515_driver.h"


void main(void){

	// Initialization: Assignment 2
	USART_init(MYUBRR);
	SRAM_init();
	
	// Initialization: Assignment 3
	adc_init();
	adc_clock_signal();
	joystick_init();

	// Struct initialization: Assignment 3
	joystick_position j_position;
	slider_position s_position;
	can_message message_test, message_receive, message;
	
	// Initialization: Assignment 4
	oled_init();
	oled_reset();
	oled_pos(0,0);
	menu_init();

	// Initialization: Assignment 5
	can_init();
	message_test.id = 0;
	message_test.length = 4;
	message_test[0] = 1;
	message_test[1] = 2;
	message_test[2] = 3;
	message_test[3] = 4;

	// Initialization: Assignment 6, 7 and 8
	message.id = 0;
	message.length = 4;
	
	//spi_send(MCP_WRITE);
	//spi_send(MCP_CANCTRL);
	//spi_send(MODE_LOOPBACK);

	while(1){

		// Assignment 1
		/*

		*/

		// Assignment 2
		/*

		*/

		//Assignment 3
		/*
		int button_l = 0;
		int button_r = 0;	
		int button_joy = 0;
		
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
			button_joy = 0;
		}
		if (joystick_button(2)==0){
			button_joy = 1;
		}
				
		// Print joystick position and direction:
		//printf("(x: %d, y: %d) %c \n \r", j_position.position_x, j_position.position_y, j_position.dir);
		
		// Slider position
		//printf("(Left slider: %d, Right slider: %d) \n \r", s_position.position_left, s_position.position_right);
		
		// Print Buttons
		//printf("Joystick button: %d , Left button: %d, Right Button: %d \n \r", button_joy, button_l, button_r);
		
		*/
		
		// Assignment 4 
		/*

		j_position = joystick_pos();
		s_position = joystick_slider_position();

		show_menu();
		navigate_menu(j_position);
		update_currentmenu();
		printf("%s \n \r", current_menu.name);
		_delay_ms(1000); 
		*/
		
		// Assignment 5 
		/*
		
		can_send(&message_test);
		can_receive(&message_receive);

		//printf("DATA: %d %d %d %d %d \n \r",message_receive.data[0], message_receive.data[1], message_receive.data[2], message_receive.data[3], message_receive.data[4]);
		
		*/
		
		// Assignment 6, 7 and 8
		/*

		message.data[0] = adc_read(0);
		message.data[1] = adc_read(1);
		message.data[2] = adc_read(3);
		message.data[3] = adc_read(2);
		can_send(&message);
		
		*/

	}
	
}

