#ifndef JOYSTICK_H
#define JOYSTICK_H

uint8_t x_mid, y_mid;


//enum direction_enum{RIGHT, LEFT, UP, DOWN, NEUTRAL};

typedef struct {
	int8_t position_x;
	int8_t position_y;
	char dir;
	
} joystick_position;

typedef struct {
	uint8_t position_left;
	uint8_t position_right;
} slider_position;


// struct control_channels{
// 	uint8_t JOYSTICK_X = 0x0;
// 	uint8_t JOYSTICK_Y = 0x4;
// 	uint8_t RIGHT_SLIDER = 0x2;
// 	uint8_t LEFT_SLIDER = 0x6;
// }channels;



void joystick_calibration(void);
void joystick_init(void);
int joystick_button(int button);
joystick_position joystick_pos(void);
joystick_position joystick_direction(void);
slider_position joystick_slider_position(void);

#endif