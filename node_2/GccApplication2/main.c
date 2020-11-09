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

uint32_t dutycycle;

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
	
	uint8_t score = 0;
		
	//Assignment 6
	
	//while (1)
	//{
		//can_receive(&message,0);
		//pwm_update_dutycycle(message.data[0]);
		//printf("sucess: %d\n\r", message.data[0]);
	
	
	//}
	//Assignment 7
	/*if (count_score()){
		score++;
	}
	printf("%d \n\r", score);
	*/
	
	//Assignment 8
	motor_init();
	while(1){
		can_receive(&message,0);
		dac_write(message.data[3]);
		printf("%d\n\r", message.data[3]);	
	}
	
}
