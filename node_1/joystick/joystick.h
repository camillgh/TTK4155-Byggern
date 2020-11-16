#ifndef JOYSTICK_H
#define JOYSTICK_H

// Start values for x, y direction joystick
uint8_t x_mid, y_mid;

// Struct for x, y position and direction for joystick
typedef struct {
	int8_t position_x;
	int8_t position_y;
	char dir;
	
} joystick_position;

// Struct for x, y sliders
typedef struct {
	uint8_t position_left;
	uint8_t position_right;
} slider_position;


void joystick_calibration(void);
void joystick_init(void);
int joystick_button(int button);
joystick_position joystick_pos(void);
joystick_position joystick_direction(void);
slider_position joystick_slider_position(void);

#endif