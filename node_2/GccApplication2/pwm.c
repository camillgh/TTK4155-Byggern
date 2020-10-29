#include "sam.h"

#define TC_RC_20MS = 0.0020;
#define TC_RA_2000US = 0.0020;

void timer_init(void){
	// Enable Clock on TC0
	PMC->PMC_PCER0 = (1<< ID_TC0);
	
	// Enable Clock IO port 8
	PMC->PMC_PCER0 = (1<< ID_PIOB);
	
	// Disable input, used by PWM 
	PIOB->PIO_PDR |= PIO_PDR_P25;
	
	// Set peripheral A
	PIOB->PIO_ABSR = PIO_PB25B_TIOA0;
	
	// Waveform mode
	TC0->TC_CHANNEL[0].TC_CMR = TC_CMR_WAVE;
	
	// USe timer clock 1 (MCK/2)
	TC0->TC_CHANNEL[0].TC_CMR = TC_CMR_TCCLKS_TIMER_CLOCK1;
	
	// Waveform selection: UP mode with autrigger on RC-compare
	TC0->TC_CHANNEL[0].TC_CMR = TC_CMR_WAVSEL_UP_RC;
	
	// Set at RC Compare
	TC0->TC_CHANNEL[0].TC_CMR = TC_CMR_ACPC_SET;
	
	// Clear at RC Compare
	TC0->TC_CHANNEL[0].TC_CMR = TC_CMR_ACPC_CLEAR;
	
	// Makes the period 20ms (50Hz)
	TC0->TC_CHANNEL[0].TC_RC = TC_RC_20MS;
		
	// Make the pulse width 1.5ms	
	TC0->TC_CHANNEL[0].TC_RA = TC_RA_2000US;
	
	// Enable interrupt on RA amd RC compare
	TC0->TC_CHANNEL[0].TC_TER = TC_IER_CPAS | TC_IER_CPCS;
	
	// Enable counter clock
	TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;
	
	

}
