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

 void led_init(void){
	 // Activate PIO in PMC
	 PMC->PMC_PCER0 = PMC_PCER0_PID11;
	 
	 // Enable register PIO
	 PIOA->PIO_PER = PIO_PA19;
	 PIOA->PIO_PER = PIO_PA20;
	 
	 // Set PIO as output
	 PIOA->PIO_OER = PIO_PA19;
	 PIOA->PIO_OER = PIO_PA20;
	 
	 //PMC_PCER0 ENABLE PERIPHERALS ON PMC! s.566
	 
	 PIOA->PIO_SODR = PIO_PA19;
	 PIOA->PIO_SODR = PIO_PA20;
	 
 }

CAN_MESSAGE message;


//! Parameters for regulator

/*! \brief Sampling Time Interval
 *
 * Specify the desired PID sample time interval
 * With a 8-bit counter (255 cylces to overflow), the time interval value is calculated as follows:
 * TIME_INTERVAL = ( desired interval [sec] ) * ( frequency [Hz] ) / 255
 */
//! \xref item todo "Todo" "Todo list"
#define TIME_INTERVAL 157



int main(void)
{
	// Assignment 6
	SystemInit();
	
	
	configure_uart();
	can_init(CAN_BR, 1,1);
	//can_init_def_tx_rx_mb(CAN_BR);
	WDT->WDT_MR = WDT_MR_WDDIS;
	pwm_timercounter_init();
	adc_init();
	dac_init();
	solenoid_init();
	motor_init();
	pid2_init();
	//systick_delay_ms(1000);

	pid_timercounter_init();
	//pid_Init(K_P, K_I, K_D);
	//pid_Reset_Integrator(pid);
	
		 
	uint8_t score = 0;
	uint8_t number = 0;	
	//Assignment 6
	int max_lives = 3;
	printf("Ye haveth %d lives left in yer soul \r\n", max_lives);
	while (max_lives)
	{
		can_receive(&message,0);
		
		
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

	
	//Assignment 8
	
	/*
	void pid2_init(void);
	void pid2_ref(position_x);
	int32_t pid2_controller(encoderdata);
	void pid2_update_controller(void);
	//motor_init();
	*/
	/*
	while(1){
		can_receive(&message,0);
		dac_write(message.data[0]);
		printf("%d\n\r", message.data[3]);	
	}
	*/
	
}
