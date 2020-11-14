#define "sam.h"

void solenoid_init(){
	// Activate PIO in PMC
	PMC->PMC_PCER1 = PMC_PCER1_PID40;
	
	// Enable register PIO
	PIOC->PIO_PER = PIO_PC8;
	
	// Set PIO as output
	PIOC->PIO_OER = PIO_PC8;
	
}

void solenoid_push(int button){
	if button{
		PIOC->PIO_SODR = PIO_PC8;
	}
	else{
		PIOC->PIO_SODR = (0u<<8);
	}
}