/*
 * TTK4155 Byggern prosjekt.c
 *
 * Created: 27.08.2020 08:45:11
 * Author : thomhagl
 */ 

#include <avr/io.h>
#include <time.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/pgmspace.h>

#include "UART_driver.h"
#include "config.h"
#include "SRAM.h"
#include "adc_driver.h"
#include "joystick.h"
#include "oled_driver.h"


void main(void){
	joystick_position j_position;
	slider_position s_position;
	
	USART_init(MYUBRR);
	adc_clock_signal();
	//joystick_init();
	oled_init();
	oled_clear();
	oled_pos(0,0);
	oled_write();

	while(1){
		/* Assignment 3
		
		int button_l = 0;
		int button_r = 0;
		int button_joy = 0;
		
		j_position = joystick_pos();
		j_position = joystick_direction();
		s_position = joystick_slider_position();
		
		// Print joystick position and direction:
		//printf("(x: %d, y: %d) %s \n \r", j_position.position_x, j_position.position_y, j_position.dir);
		
		// Slider position
		//printf("(Left slider: %d, Right slider: %d) \n \r", s_position.position_left, s_position.position_right);
		
		// Buttons
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
		
		printf("Joystick button: %d \n \r", button_joy);
		
		//printf("(%d,%d)", j_position.position_x, j_position.position_y);
		_delay_ms(1000);*/
		
		/* Assignment 4*/
	
		//char testern[] PROGMEM = "HEI"
	

	}
		
	
}