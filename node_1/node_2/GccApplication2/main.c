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

#define CAN_BR 0x00290561

#define K_P 1.00
#define K_I 0.00
#define K_D 0.00

int main(void)
{
	// System Initialization
	SystemInit();

	// Initialization: Assignment 6
	configure_uart();
	can_init(CAN_BR, 1,1);
	//can_init_def_tx_rx_mb(CAN_BR);
	WDT->WDT_MR = WDT_MR_WDDIS;

	CAN_MESSAGE message;

	// Initialization: Assignment 7
	pwm_timercounter_init();
	adc_init();
	dac_init();

	uint32_t dutycycle;
	uint8_t score = 0;

	// Initialization: Assignment 8
	motor_init();
	
	while (1)
	{
		// Assignment 6:

		/*
		can_receive(&message,0);
		*/
	
		//Assignment 7:

		/*
		can_receive(&message,0);
		pwm_update_dutycycle(message.data[0]);
		if (count_score()){
		score++;
		}
		*/
	
		//Assignment 8
		
		/*
		can_receive(&message,0);
		dac_write(message.data[3]);
		*/
	}
	
}
