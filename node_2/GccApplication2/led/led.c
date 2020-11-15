#include "sam.h"

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
