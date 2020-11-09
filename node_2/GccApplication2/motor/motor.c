#include "sam.h"

void motor_init(){
	 
	 // Enable EN
	 PIOD->PIO_PER = PIO_PD9;
	 
	 // Enable DIR
	 PIOD->PIO_PER = PIO_PD10;
	 
	 // Set PIO as output
	 PIOD->PIO_OER = PIO_PD9;
	 PIOD->PIO_OER = PIO_PD10;
	
	// Set pin High
	 PIOD->PIO_SODR = PIO_PD9;
	 PIOD->PIO_SODR = 1u<<10;
}