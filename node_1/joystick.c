#include <stdio.h>
#include <avr/io.h>
#include "joystick.h"
#include "config.h"
#include "adc_driver.h"
#include <time.h>
#include <stdbool.h>

#include <util/delay.h>


void joystick_init(void){
	
	// Initialize external units
	//adc_init();
	
	// Set PINB1, PINB2 and PINB3 as inputs
	DDRB &= ~(1<<PINB1) & ~(1<<PINB2) & ~(1<<PINB3);
	
	// Calibrate joystick
	joystick_calibration();

}

int joystick_button(int button){
	switch (button){
		// Left touch button
		case 0: 
			if (test_bit(PINB, PINB1)){
				return 1;
				break;
			}
		/*
		// Right touch button
		case 1: 
			if (test_bit(PINB, PINB2)){
				return 1;
				break;
			}
		*/
		// Joystick button
		/*case 2:
			if (!test_bit(PINB, PINB3)){
				return 1;
				break;
			}
		default:
			break;*/
	}
	return 0;
}



joystick_position joystick_pos(void)
{	
	joystick_position position = {0,0};
	uint8_t x,y;
	
	x = adc_read(0);
	y = adc_read(1);
	
	//printf("(%d, %d) \n \r", x, y);
	
	
	//_delay_ms(1);
	
	//uint8_t x_diff = x-x_mid;
	
	//position.position_x = (x-x_mid)*200/255;
	//position.position_y = (y-y_mid)*200/255;
	
	//printf("(%d, %d) \n \r", position.position_x, position.position_y);
	int8_t diff_x = x - x_mid;
	
	
	if(x > x_mid) {
		position.position_x = 100*(x-x_mid)/(0xFF - x_mid);
	} 
	
	if (x < x_mid) {
		position.position_x = 100*(x-x_mid)/(x_mid-0);
	} 
		
	if (x == x_mid) {
		position.position_x = 0;
	}
	
	//int8_t y_diff = y-y_mid;
	
	//Calculate position y percentage
	if(y > y_mid) {
		position.position_y = 100*(y-y_mid)/(255 - y_mid);
	}
	if (y < y_mid) {
		position.position_y = 100*(y-y_mid)/y_mid;
	} if (y == y_mid) {
		position.position_y = 0;
	}
	
	
	
	//printf("%d \n \r", position.position_x);

	return position;
}


joystick_position joystick_direction(void){
	
	int deadzone = 3;
	
	joystick_position position;
	
	position = joystick_pos();
	
	if (position.position_x > deadzone){
		position.dir = 'R';
	}
	
	if (position.position_x < -deadzone){
		position.dir = 'L';
	}
	
	if (position.position_y > deadzone){
		position.dir = 'U';
	}
	if (position.position_y <  -deadzone){
		position.dir = 'D';
	}
	if (abs(position.position_x) <= deadzone && abs(position.position_y) <= deadzone){
		position.dir = 'N';
	}
	return position;
	
};

void joystick_calibration(void){
	
	uint8_t x,y;
	
	x = adc_read(0);
	y = adc_read(1);
	_delay_ms(1);
	x_mid = x;
	y_mid = y;
}



slider_position joystick_slider_position(void)
{
	slider_position position = {0,0};
	uint8_t left, right;
	
	left = adc_read(3);
	right = adc_read(2);
	//printf("%d \n",left);
	position.position_right = right*100/255;
	position.position_left = left*100/255;
		
	return position;
}

