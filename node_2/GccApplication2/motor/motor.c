#include "sam.h"

void motor_init(){

	 //Enable !OE
	 PIOD->PIO_PER = PIO_PD0;
	 
	 // Enable EN
	 PIOD->PIO_PER = PIO_PD9;
	 
	 // Enable DIR
	 PIOD->PIO_PER = PIO_PD10;
	 

	 // Set PIO as output
 	 PIOD->PIO_OER = PIO_PD0;  //!OE
	 PIOD->PIO_OER = PIO_PD9;  //EN
	 PIOD->PIO_OER = PIO_PD10; //DIR

	
	// Set pin High
	 PIOD->PIO_SODR = PIO_PD9;
	 PIOD->PIO_SODR = 1u<<10;
}

uint16_t motor_read_encoder(void){
	
	//Set !OE low
	PIOD->PIO_SODR = (0 << PIO_PD0);
	 
	//Set SEL low
	PIOD->PIO_SODR = (0 << PIO_PD2);
	
	//Delay 20us
	
	//Read MSB
	encoderdata |= (PIO_PC1 << 8) | (PIO_PC2 << 9) | (PIO_PC3 << 10) | (PIO_PC4 << 11) | (PIO_PC5 << 12) | (PIO_PC6 << 13) | (PIO_PC7 << 14) | (PIO_PC8 << 15);
	
	//Set SEL high
	PIOD->PIO_SODR = (1 << PIO_PD2);

	//Delay 20us
		
	//Read LSB
	encoderdata |= (PIO_PC1 << 0) | (PIO_PC2 << 1) | (PIO_PC3 << 2) | (PIO_PC4 << 3) | (PIO_PC5 << 4) | (PIO_PC6 << 5) | (PIO_PC7 << 6) | (PIO_PC8 << 7);	

	//Toggle !RST 
	PIOD->PIO_SODR = (PIO_PD1 << 0);
	PIOD->PIO_SODR = (PIO_PD1 << 1);
	
	//Set !OE low
	PIOD->PIO_SODR = (1 << PIO_PD0);
	
			
	return encoderdata;
}
'