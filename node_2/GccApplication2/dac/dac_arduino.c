/*
 * dac_arduino.c
 *
 * Created: 08.11.2020 15:57:11
 *  Author: ivartg
 */ 

#include "sam.h"
#include "dac_arduino.h"

/**
 * \brief Initialize DAC
 *
 *
 * \param void
 * \retval void
 */

void dac_init(){
	
	// Enable PMC
	PMC->PMC_PCER1 |= PMC_PCER1_PID38;
	
	// Disable trigger, enable free running mode
	DACC->DACC_MR |= DACC_MR_TRGEN_DIS;
	
	// Select channel 1
	DACC->DACC_MR |= DACC_MR_USER_SEL_CHANNEL1;
	
	// Select half-word transfer
	DACC->DACC_MR |= DACC_MR_WORD_HALF;
	
	// Enable channel DAC1
	DACC->DACC_CHER |= DACC_CHER_CH1;
	
	// Set output data register PD9, or pin 30 on the Due, to be driven on the I/O line.
	PIOD->PIO_SODR |= PIO_SODR_P9;
		
}


/**
 * \brief Converts digital servo position to analogue
 *
 *
 * \param data Input calculated from PID regulator
 * \retval void
 */

void dac_write(uint16_t data){
	
	// Add data to register, scale value such that DAC1 = [0.5-2.75], AOUT = [0,5V]
	DACC->DACC_CDR = DACC_CDR_DATA(data*16);
	
}