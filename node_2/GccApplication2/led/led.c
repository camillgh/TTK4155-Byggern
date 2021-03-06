#include "sam.h"

/**
 * \brief Turns on led on pin 42 and 43 on the Due.
 *
 *
 * \param void
 * \retval void
 */


void led_init(void){
	// Activate PIO in PMC
	PMC->PMC_PCER0 = PMC_PCER0_PID11;
	
	// Enable register PIO
	PIOA->PIO_PER = PIO_PA19;
	PIOA->PIO_PER = PIO_PA20;
	
	// Set PIO as output
	PIOA->PIO_OER = PIO_PA19;
	PIOA->PIO_OER = PIO_PA20;
	
	// Set output data register PA19 and PA20, or pin 42 and 43 on the Due, to be driven on the I/O line.	
	PIOA->PIO_SODR = PIO_PA19;
	PIOA->PIO_SODR = PIO_PA20;
	
}
