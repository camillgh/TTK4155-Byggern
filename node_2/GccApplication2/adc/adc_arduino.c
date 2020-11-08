#include "sam.h"
#include "adc_arduino.h"


void adc_init(){
	
	PMC->PMC_PCER1 = PMC_PCER1_PID37;
	
	PIOA->PIO_PER |= PIO_PA2;
	
	// Enable channel 0
	ADC->ADC_CHER = ADC_CHER_CH0;
	
	// Enable freerun mode
	ADC->ADC_MR |= ADC_MR_FREERUN;
	
	
}

uint32_t read_adc(void){
	
	// Start conversion
	ADC->ADC_CR = ADC_CR_START;
	
	uint32_t data;
	
	// Read from channel 0
	data = ADC->ADC_CDR[0];
		
	return data;
}

uint8_t count_score(void){
	
	uint16_t data;
	data = read_adc();
	
	//DelayMs(1000);
	
	// When blocked IR is blocked, the value from adc is below 10000
	if (data < 1000){
		return 1;
	}
	else{
		return 0;
	}
	
}