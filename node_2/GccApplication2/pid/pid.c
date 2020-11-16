/*
 * pid.c
 *
 * Created: 15.11.2020 09:52:10
 *  Author: ivartg
 */ 
#include "pid.h"
#include "../motor/motor.h"
#include "stdint.h"
#include "sam.h"


int16_t kp = 10;
int16_t ki = 6;
int16_t kd = 1;


/**
 * \brief Initializes the PID regulator
 *
 *
 * \param void
 * \retval void
 */

void pid_init(void){
	sum_error = 0;
	last_error = 0;
	
	// Limit the summing of errors
	max_sum_error = (DEC_INT12/2)/(ki+1);
}


/**
 * \brief Upscales the joystick position
 *
 *
 * \param joy_pos Joystick position in the range [0, 255].
 * \retval void
 */

void pid_ref(uint8_t joy_pos){
	
	// Sets joy_ref = 0 when inside of deadzone.

	if (joy_pos < 6){
		
		joy_ref = 0;
		
	} else {
		
		// Scales joy_pos range to the same range as the encoder position is in.
		joy_ref = ((int32_t) (ENC_MAX)*(int32_t)joy_pos)/JOY_MAX; //PLS ENDRE
	}
}


/**
 * \brief Runs the PID regulator
 *
 *
 * \param enc_pos Servo position from encoder data.
 * \retval input Control input.
 */

int32_t pid_controller(int16_t enc_pos){
	int32_t temp, p_term, i_term, d_term, error, input;
	
	// Limits the encoder data range.
	if (enc_pos < 0){
		enc_pos = 0;
	} else if (enc_pos > 8500){
		enc_pos = 8500;
	}

	// Sets servo direction	
	error = joy_ref - enc_pos;
	
	if(error < 0){
		PIOD->PIO_SODR = PIO_PD10;
		}else{
		PIOD->PIO_CODR = PIO_PD10;
	}
	
	error = abs(error);
	
	
	// Calculates p_term
	p_term = kp*error;
	
	// Calculates i_term, with dt
	temp = (sum_error+error)/10;
	sum_error = temp;
	i_term = ki*sum_error;
	
	// Calculates d_term, with dt
	d_term = kd*(error-last_error)*10;
	last_error = error;
	
	// Calculates (scaled) control function
	input = (p_term+i_term+d_term)/SCALING_FACTOR;


	// Limits control input range
	if(input > DEC_INT12){
		input = DEC_INT12;
		sum_error = sum_error-error;

	} else if(input < -DEC_INT12){
		input = -DEC_INT12;
		sum_error = sum_error-error;
	}
	
	return input;
}


/**
 * \brief Updates PID controller at an interval
 *
 *
 * \param void
 * \retval void
 */

void pid_update(void){

	// Checks for interrupts
	if(PWM_ISR1_CHID3){
		
		// Declares the upscaled control input
		int16_t input = pid_controller(motor_read_encoder())*6;	
			
		// Writes the input to a_out on the shield		
		dac_write(abs(input));
	}
}


/**
 * \brief Initializes the PWM signal for the PID interval
 *
 *
 * \param void
 * \retval void
 */

void pid_timercounter_init(void){
	
	// Interrupt enable
	PWM->PWM_IER1 = PWM_IER1_CHID3;
	
	// Enable clock
	PMC->PMC_PCER1 |= (1 << ID_PWM-32);
	
	// Select CLKA, MCK/2
	PWM->PWM_CLK |= PWM_CLK_DIVA(1) | PWM_CLK_PREA(6);
	
	// Select pre-scaler CLKA
	PWM->PWM_CH_NUM[3].PWM_CMR |= (PWM_CMR_CPRE_CLKA);
	
	// Set period, 20 ms
	PWM->PWM_CH_NUM[3].PWM_CPRD = 1640*16;
	
	// Set start duty cycle, 1.5ms (7.5% pulse width)
	PWM->PWM_CH_NUM[3].PWM_CDTY = 24272; //CPRD - CPRD*7.5%
	
	// Enable channel 3
	PWM->PWM_ENA |= (PWM_ENA_CHID3);
	
}

