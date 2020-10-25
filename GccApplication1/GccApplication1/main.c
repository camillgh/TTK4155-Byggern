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
#include "sam.h"


void main(void){

	joystick_position j_position;
	slider_position s_position;
	can_message message;
	adc_init();
	USART_init(MYUBRR);
	
	adc_clock_signal();
	joystick_init();
	SRAM_init();
	can_init();

	oled_init();
	oled_reset();
	oled_pos(0,0);	
//
	//menu_init();
	
	message.id = 1;
	message.length = 5;
	message.data[0] = 10;
	message.data[1] = 2;
	message.data[2] = 3;
	message.data[3] = 4;
	message.data[4] = 5;
	//update_currentmenu();
	//SRAM_test();
	
	//spi_send(MCP_WRITE);
	//spi_send(MCP_CANCTRL);
	//spi_send(MODE_LOOPBACK);

	while(1){
		//Assignment 3
		/*
		int button_l = 0;
		int button_r = 0;	
		int button_joy = 0;
		
		j_position = joystick_pos();
		//printf("Position 1: %d\n\r", j_position.position_x);
		//j_position = joystick_direction();
		s_position = joystick_slider_position();
		
		// Print joystick position and direction:
		//printf("(x: %d, y: %d) %s \n \r", j_position.position_x, j_position.position_y, j_position.dir);
		
		// Slider position
		//printf("(Left slider: %d, Right slider: %d) \n \r", s_position.position_left, s_position.position_right);
		/*
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
		
		//printf("Joystick button: %d \n \r", button_joy);
		
		//printf("(%d,%d)", j_position.position_x, j_position.position_y);
		_delay_ms(1);*/
		
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
		printf("BEFORE SENDING Canstat: %x \n \r", mcp2515_read(MCP_CANSTAT));
		_delay_ms(100);
		can_send(&message);
		printf("AFTER SENDING Canstat: %x \n \r", mcp2515_read(MCP_CANSTAT));
		printf("AFTER SENDING RXSTAT: %x \n \r", mcp2515_read(MCP_RX_STATUS));
		_delay_ms(100);
		//printf("TXBControl: %x \n \ r", mcp2515_read(MCP_TXB0CTRL));
		printf("STAT: %d \n \r", mcp2515_read_status());
		can_receive(&message);
	
		printf("DATA: %d %d %d %d %d \n \r",message.data[0], message.data[1], message.data[2], message.data[3], message.data[4]);
		_delay_ms(100);
		//printf("%d", mcp2515_read(0x0e));
		//can_receive();
		
		// Assignment 6
		// can_init_def_tx_rx_mb(0x143555);
		
	}
	
}