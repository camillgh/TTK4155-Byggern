/*
 * dac_arduino.c
 *
 * Created: 08.11.2020 15:57:11
 *  Author: ivartg
 */ 

#include "sam.h"


void dac_init(){
	
	// Enable PMC
	PMC->PMC_PCER1 = PMC_PCER1_PID38;
	
	// Disable trigger, enable free running mode
	DACC->DACC_MR = DACC_MR_TRGEN_DIS;
	
	// Enable channel DAC1
	DACC->DACC_CHER = DACC_CHER_CH1;
	
}

void dac_write(uint16_t data){
	PIOD->PIO_SODR = PIO_SODR_P9;
	DACC->DACC_MR |= DACC_MR_USER_SEL_CHANNEL1;
	DACC->DACC_CDR = DACC_CDR_DATA(data);

}