#include "sam.h"
#include "adc.h"
#include "adc_arduino.h"

void adc_arduino_init(){
	
	// Enable channel 0
	ADC->ADC_CHER |= ADC_CHER_CH0;
	
	// Enable freerun mode
	ADC->ADC_MR |= ADC_MR_FREERUN;
	
	
}

void read_adc_arduino(void){
	
	// Start conversion
	ADC->ADC_CR |= ADC_CR_START;
	
	// Read from channel 0
	&adc_read |= ADC->ADC_CDR[0];
}