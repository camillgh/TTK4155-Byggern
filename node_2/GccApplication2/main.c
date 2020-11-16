/*
 * GccApplication2.c
 *
 * Created: 22.10.2020 18:14:34
 * Author : ivartg
 */ 

#include "sam.h"
#include "uart/uart.h"
#include "uart/printf-stdarg.h"
#include "can/can_controller.h"
#include "can/can_interrupt.h"
#include "pwm/pwm.h"
#include "adc_arduino.h"
#include "motor/motor.h"
//#include "pid/pid.h"
#include "pid2/pid2.h"
#include "timer/timer.h"
#include "solenoid/solenoid.h"
#include "motor/motor.h"

#define CAN_BR 0x00290561

uint32_t dutycycle;


uint8_t position_x;
uint16_t encoderdata;

#define TIME_INTERVAL 157



int main(void)
{
	// Systeminit
	SystemInit();
	
	// Init: Assignment 6
	configure_uart();
	can_init(CAN_BR, 1,1);
	//can_init_def_tx_rx_mb(CAN_BR);
	WDT->WDT_MR = WDT_MR_WDDIS;
	
	CAN_MESSAGE message;
	
	// Init: Assignment 7
	pwm_timercounter_init();
	adc_init();
	
	// Init: Assignment 8
	dac_init();
	solenoid_init();
	motor_init();
	pid2_init();
	pid_timercounter_init();
		 
	uint8_t score = 0;
	int max_lives = 3;

	
	//while(1){
		
		/*
		
		// Assignment 6
		can_receive(&message);
		printf("Joystick-x: %d, Joystick-y: %d \n\r", message.data[0], message[1]);
		
		*/
		
		// Assignment 7
		
		/*
		
		if (count_score()){
			score++;
		}
		printf("Score: %d \n\r", )
		
		*/
		
		// Assignment 8 
		
		/*
		
		can_receive(&message,0);
		
		//Move the servo angle (slider)
		pwm_update_dutycycle(message.data[3]);
		
		//Push the servo (joystick button)
		if (message.data[4]){
			solenoid_push();
			systick_delay_ms(300);
		}		
		
		position_x = message.data[0];
		
		//Move the motor position (joystick)
		pid2_ref(position_x);
		pid2_update_controller();
		
		*/
	//}
	
	
	
	// Main game
	printf("Ye haveth %d lives left in yer soul \r\n", max_lives);
	while (max_lives)
	{
		can_receive(&message,0);
		
		
		printf("%d \n\r", message.data[0]);
		
		//Move the servo angle (slider)
		pwm_update_dutycycle(message.data[3]);
		
		
		//Push the servo (joystick button)
		if (message.data[4]){
			solenoid_push();
			systick_delay_ms(300);
		}
		//printf("Joystick button: %d \r\n", message.data[4]);
		
		
		
		position_x = message.data[0];
		
		//Move the servo position (joystick)
		pid2_ref(position_x);
		pid2_update_controller();
		
		
		
		
		//Send highscore back to oled!
		if(count_score()){
			max_lives -= 1;
			printf("Lives left: %d \r\n: ", max_lives);
		}
		if(max_lives==0){
			printf("Game Over kek!");
		}
		
		
	}
	

	
}
