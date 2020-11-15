/*
 * pid2.c
 *
 * Created: 15.11.2020 09:52:10
 *  Author: ivartg
 */ 
#include "pid2.h"
#include "../motor/motor.h"
#include "stdint.h"
#include "sam.h"


int16_t kp = 3;
int16_t ki = 8;
int16_t kd = 1;


void pid2_init(void){
	//init values
	sum_error = 0;
	last_error = 0;
	
	//limit the summing of errors
	max_sum_error = (INT12_MAX/2)/(ki+1);
}

//!!!!!
void pid2_ref(uint8_t joy_pos){
	//deadzone 

	if (joy_pos<6){
		ref = 0;
	}else{
		ref = (((int32_t) (ENCODER_MAX-2*ENCODER_SAFEZONE)*(int32_t)joy_pos)/SETPOINT_MAX) + ENCODER_SAFEZONE; //PLS ENDRE
	}
	
//	printf("JOY:	  %d \r\n", joy_pos);

	
//	printf("REf: %d \r\n", ref);
}

int32_t pid2_controller(int16_t measurement){
	int32_t temp, p_term, i_term, d_term, error, input;
	
	if (measurement < 0){
		measurement = 0;
	} else if (measurement > 8500){
		measurement = 8500;
	}
	
	error = ref - measurement;
	
	if(error < 0){
		PIOD->PIO_SODR = PIO_PD10;
		}else{
		PIOD->PIO_CODR = PIO_PD10;
	}
	error = abs(error);
	
	p_term = kp*error;
	


	temp = (sum_error+error)/10;
	sum_error = temp;
	i_term = ki*sum_error;
	
	d_term = kd*(error-last_error)*10;
	last_error = error;
	
	//set input
	input = (p_term+i_term+d_term)/SCALING_FACTOR;


	if(input > INT12_MAX){
		input = INT12_MAX;
		sum_error = sum_error-error;

	} else if(input < -INT12_MAX){
		input = -INT12_MAX;
		sum_error = sum_error-error;
	}
	
	return input;
}

void pid2_update_controller(void){
	//update PID contoller values at time interval
	if(PWM_ISR1_CHID3){
		int16_t input = pid2_controller(motor_read_encoder())*6;		
		dac_write(abs(input));
		//printf("Input: %d \r\n\r\n", input);


	
	}
}