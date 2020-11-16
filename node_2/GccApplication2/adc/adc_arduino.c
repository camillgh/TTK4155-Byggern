#include "sam.h"
#include "../timer/timer.h"

/**
 * \brief Initializes the ADC
 *
 * \param void
 *
 * \retval void
 */
void adc_init(){

	// Peripheral clock enable. Peripheral ID 37 corresponds to the ADC instance.
	PMC->PMC_PCER1 = PMC_PCER1_PID37;
	
	// Enables the PIO to control SAM3X pin PA2 and Due pin 61 (disables peripheral control of the pin).
	PIOA->PIO_PER |= PIO_PA2;
	
	// Enable channel 0
	ADC->ADC_CHER = ADC_CHER_CH0;
	
	// Enable freerun mode
	ADC->ADC_MR |= ADC_MR_FREERUN;
	
	
}


/**
 * \brief Reads from channel 0 in the ADC
 *
 * \param void
 *
 * \retval  returns the analog-to-digital conversion data
 */

uint32_t adc_read(void){
	
	// Start conversion
	ADC->ADC_CR = ADC_CR_START;
	
	uint32_t data;
	
	// Read from channel 0
	data = ADC->ADC_CDR[0];
		
	return data;
}


/**
 * \brief Checks for scores in the game.
 *
 * \param void
 *
 * \retval Returns 1 when light from IR transceiver to receiver gets blocked.
 */

uint8_t adc_count_score(void){
	
	uint16_t data;
	data = adc_read();
	
	// When blocked IR is blocked, the value from adc is below 10000
	while (data < 1000){
		data = adc_read();
		if (data > 1000){
			return 1;
			break;
		}
	}
	return 0;
	
}

