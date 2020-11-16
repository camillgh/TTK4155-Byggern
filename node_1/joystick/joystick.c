#include <stdio.h>
#include <avr/io.h>
#include <time.h>
#include <stdbool.h>
#include <util/delay.h>

#include "../joystick/joystick.h"
#include "config.h"
#include "../adc/adc_driver.h"

/**
 * \brief Joystick initialization
 *
 *
 * \param void
 * \retval void
 */



void joystick_init(void){
	
	// Set PINB1, PINB2 and PINB3 as inputs
	DDRB &= ~(1<<PINB1) & ~(1<<PINB2) & ~(1<<PINB3);
	
	// Calibrate joystick
	joystick_calibration();

}

/**
 * \brief Return value of selected button
 *
 *
 * \param button variable to select button
 * \retval True(1) if pushed, or False(0) if not pushed
 */


int joystick_button(int button){
	
	switch (button){
		
		// Left touch button
		case 0: 
			if (test_bit(PINB, PINB1)){
				return 1;
				break;
			}
		
		// Right touch button
		case 1: 
			if (test_bit(PINB, PINB2)){
				return 1;
				break;
			}
		
		// Joystick button
		case 2:
			if (!test_bit(PINB, PINB3)){
				return 1;
				break;
			}
		default:
			break;
	}
	return 0;
}

/**
 * \brief Calculated x, y position for joystick in percentages
 *
 *
 * \param void
 * \retval position struct containing calculated joystick positions
 */



joystick_position joystick_pos(void)
{	
	joystick_position position = {0,0};
	uint8_t x,y;
	
	// Read analog value for x and y direction joystick
	x = adc_read(0);
	y = adc_read(1);
	
	// Calculate position x percentage
	if(x > x_mid) {
		position.position_x = 100*(x-x_mid)/(0xFF - x_mid);
	} 
	
	if (x < x_mid) {
		position.position_x = 100*(x-x_mid)/(x_mid-0);
	} 
		
	if (x == x_mid) {
		position.position_x = 0;
	}
	
	
	//Calculate position y percentage
	if(y > y_mid) {
		position.position_y = 100*(y-y_mid)/(255 - y_mid);
	}
	if (y < y_mid) {
		position.position_y = 100*(y-y_mid)/y_mid;
	} if (y == y_mid) {
		position.position_y = 0;
	}
	
	return position;
}

/**
 * \brief Calculates direction to joystick
 *
 *
 * \param void
 * \retval position struct containing direction of joystick
 */



joystick_position joystick_direction(void){
	
	// Deadzone for joystick
	int deadzone = 3;
	
	joystick_position position;
	
	// Get x and y position for joystick
	position = joystick_pos();
	
	// Calculate direction
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

/**
 * \brief Joystick calibration
 *
 *
 * \param void
 * \retval void
 */


void joystick_calibration(void){
	
	uint8_t x,y;
	
	// Get x, y start value for joystick
	x = adc_read(0);
	y = adc_read(1);
	
	_delay_ms(1);
	
	// Set start value for joystick to the global variables: x_mid, y_mid
	x_mid = x;
	y_mid = y;
	
}

/**
 * \brief Calculated left, right slider position in percentages  
 *
 *
 * \param void
 * \retval position struct containing calculated slider positions 
 */


slider_position joystick_slider_position(void)
{
	slider_position position = {0,0};
	uint8_t left, right;
	
	// Get analog value for sliders
	left = adc_read(3);
	right = adc_read(2);
	
	// Calculate slider position in percentage
	position.position_right = right*100/255;
	position.position_left = left*100/255;
		
	return position;
}

