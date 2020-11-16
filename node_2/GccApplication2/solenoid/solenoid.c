#include "sam.h"
#include "../timer/timer.h"
int press;


/**
 * \brief Initializes the solenoid
 *
 *
 * \param void
 * \retval void
 */

void solenoid_init(){
	// Activate PIO in PMC
	PMC->PMC_PCER0 = PMC_PCER0_PID18;
	
	// Set peripheral C on P44
	PIOC->PIO_ABSR |= PIO_ABSR_P18;
	
	// Enable register PIO
	PIOC->PIO_PER = PIO_PC18;
	
	// Set PIO as output
	PIOC->PIO_OER = PIO_PC18;
	
}


/**
 * \brief Clicks the solenoid button on and off
 *
 *
 * \param void
 * \retval void
 */

void solenoid_push(){
	
	// Sets the solenoid data to be driven on the I/O line
	PIOC->PIO_SODR = PIO_PC18;
	
	systick_delay_ms(300);

	// Clears the solenoid data to be driven on the I/O line	
	PIOC->PIO_CODR = PIO_PC18;
}