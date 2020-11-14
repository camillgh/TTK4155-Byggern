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
#include "pid/pid.h"
#include "timer/timer.h"
#include "solenoid/solenoid.h"
#include "motor/motor.h"

#define CAN_BR 0x00290561

#define K_P 1.0
#define K_I 1.0
#define K_D 0.0

uint32_t dutycycle;

pidData_t *pid;
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


struct GLOBAL_FLAGS {
	//! True when PID control loop should run one time
	uint8_t pidTimer : 1;
	uint8_t dummy : 7;
} gFlags = {0, 0};

//! Parameters for regulator
struct PID_DATA pidData;

/*! \brief Sampling Time Interval
 *
 * Specify the desired PID sample time interval
 * With a 8-bit counter (255 cylces to overflow), the time interval value is calculated as follows:
 * TIME_INTERVAL = ( desired interval [sec] ) * ( frequency [Hz] ) / 255
 */
//! \xref item todo "Todo" "Todo list"
#define TIME_INTERVAL 157

ISR(TIMER0_OVF_vect)
{
	static uint16_t i = 0;

	if (i < TIME_INTERVAL) {
		i++;
	} else {
		gFlags.pidTimer = 1;
		i               = 0;
	}
}


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
	
	//systick_delay_ms(1000);

	motor_init();
	pid_timercounter_init();
	pid_Init(K_P, K_I, K_D, pid);
	pid_Reset_Integrator(pid);
	
		 
	uint8_t score = 0;
	uint8_t number = 0;	
	//Assignment 6
	
	while (1)
	{
		can_receive(&message,0);
		//pwm_update_dutycycle(message.data[0]);
		solenoid_push(message.data[4]);

		//printf("sucess: %d\n\r", message.data[0]);
		//printf("%d\n\r", message.data[4]);
		
		/*
		if (gFlags.pidTimer){
			gFlags.pidTimer = 0;
			position_x = message.data[0];
			encoderdata = motor_read_encoder();
			printf("%d\n\r", encoderdata); 
			motor_control(encoderdata, position_x, message, pid, encoderdata);
		}
		*/
		//printf("%d \n\r", score);
		
		
		//For every 20ms:
		
		if (PWM_ISR1_CHID3){
			//Save the received joystick output and encoder data into variables
			position_x = message.data[0];
			encoderdata = motor_read_encoder();
			
			//Set a new direction and voltage to the motor, using PID
			motor_control(encoderdata, position_x, message, pid, encoderdata);
			
		}
		printf("hello");		
	
	}

	
	//Assignment 8
	
	//motor_init();
	
	/*
	while(1){
		can_receive(&message,0);
		dac_write(message.data[0]);
		printf("%d\n\r", message.data[3]);	
	}
	*/
	
}
