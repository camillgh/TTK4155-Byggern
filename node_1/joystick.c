#include <stdio.h>
#include <avr/io.h>
#include "joystick.h"
#include "config.h"
#include "adc_driver.h"


uint8_t x_mid, y_mid;

struct direction_joystick{
	int direction_x;
	int direction_y;
};

struct position_joystick_perc{
	int position_x;
	int position_y;
}joystick_positions;

struct position_slider_perc{
	int position_x;
	int position_y;
}slider_positions;


struct control_channels{
	uint8_t JOYSTICK_X = 0x0;
	uint8_t JOYSTICK_Y = 0x4;
	uint8_t RIGHT_SLIDER = 0x2;
	uint8_t LEFT_SLIDER = 0x6;
}channels;

enum direction_enum{RIGHT, LEFT, UP, DOWN, NEUTRAL};



int joystick_position(float voltage_x, float voltage_y)
{	
	joystick_positions.position_y = ((voltage_y - y_mid)/y_mid)*100;
	joystick_positions.position_x = ((voltage_x - x_mid)/x_mid)*100;
	
	return dir;
}


enum joystick_direction(float voltage_x, float voltage_y){
	int x_dir, y_dir;
	
	if voltage_x > x_mid{
		x_dir = RIGHT;
	}
	
	if voltage_x < x_mid{
		x_dir = LEFT;
	}
	
	if voltage_y > y_mid{
		y_dir = UP;
	}
	if voltage_y <  y_mid{
		y_dir = DOWN;
	}
	if voltage_x == x_mid && voltage_y == y_mid{
		return NEUTRAL;
	}
	
	direction_joystick dir = {x_dir, y_dir};

	return dir;
	
};

void joystick_calibration(void){
	x_mid = adc_read(channels.JOYSTICK_X);
	y_mid = adc_read(channels.JOYSTICK_Y);
}



int joystick_slider_position(float voltage_x, float voltage_y)
{
	slider_positions.position_y = (voltage_x/(x_mid*2))*100;
	slider_positions.position_x = (voltage_y/(y_mid*2))*100;
	
	return slider_positions;
}