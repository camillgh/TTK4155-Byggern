#include "sam.h"
#include "../timer/timer.h"
#include "../pid/pid.h"
#include "../dac/dac_arduino.h"
#include "../can/can_controller.h"

uint8_t encoderdataLSB;
uint8_t encoderdataMSB;
uint16_t encoderdata;



/**
 * \brief Initializes the motor
 *
 *
 * \param void
 * \retval void
 */

void motor_init(){
	
	// Enables the Write Protect Mode Register
	PMC->PMC_WPMR |= PMC_WPMR_WPEN;
	PMC->PMC_WPMR |= PMC_WPMR_WPKEY_PASSWD;

	//Enable PMC on peripheral C and D	
	PMC->PMC_PCER0 |= 1<<(ID_PIOD);
	PMC->PMC_PCER0 |= 1<<(ID_PIOC);
	
	 //Enable !OE
	 PIOD->PIO_PER = PIO_PD0;
	 
	 // Enable EN
	 PIOD->PIO_PER = PIO_PD9;
	 
	 // Enable DIR
	 PIOD->PIO_PER = PIO_PD10;
	 
	 // Enable SEL
	 PIOD->PIO_PER = PIO_PD2;
	 
	 // Enable !RST
	 PIOD->PIO_PER = PIO_PD1;
	 
	 // Enable D0-D7
	 PIOC->PIO_PER |= PIO_PC1 | PIO_PC2 | PIO_PC3 | PIO_PC4 | PIO_PC5 | PIO_PC6 | PIO_PC7 | PIO_PC8;
	 
	 // Enable write
	 PIOD->PIO_OWER |= PIO_PD0 | PIO_PD9 | PIO_PD10 | PIO_PD2 | PIO_PD1;

	// Disable write
	 PIOC->PIO_OWDR |= PIO_PC1 | PIO_PC2 | PIO_PC3 | PIO_PC4 | PIO_PC5 | PIO_PC6 | PIO_PC7 | PIO_PC8;
	
	// Disable interrupts
	PIOD->PIO_IDR |= PIO_PD0 | PIO_PD9 | PIO_PD10 | PIO_PD2 | PIO_PD1;
	PIOC->PIO_IDR |= PIO_PC1 | PIO_PC2 | PIO_PC3 | PIO_PC4 | PIO_PC5 | PIO_PC6 | PIO_PC7 | PIO_PC8;
	
	// Output enable 
	PIOD->PIO_OER |= PIO_PD0 | PIO_PD9 | PIO_PD10 | PIO_PD2 | PIO_PD1;
	
	// Disable output
	PIOC->PIO_ODR |= PIO_PC1 | PIO_PC2 | PIO_PC3 | PIO_PC4 | PIO_PC5 | PIO_PC6 | PIO_PC7 | PIO_PC8;

	// Set output data register PD9, or pin 30 on the Due, to be driven on the I/O line.
	 PIOD->PIO_SODR = PIO_PD9;
	 
}


/**
 * \brief Reads from the motor encoder
 *
 *
 * \param void
 * \retval Returns the servo position from the encoder
 */

uint16_t motor_read_encoder(void){
	
	//Set SEL og !OE low
	PIOD->PIO_CODR = PIO_PD0;
	PIOD->PIO_CODR = PIO_PD2;
	
	//Delay 20us
	systick_delay_us(20);
	
	//Read MSB
	encoderdataMSB = PIOC->PIO_PDSR;
	
	//Set SEL high
	PIOD->PIO_SODR = PIO_PD2;

	//Delay 20us
	systick_delay_us(20);
		
	//Read LSB	
	encoderdataLSB = PIOC->PIO_PDSR;
	
	//Toggle !RST 
	PIOD->PIO_CODR = PIO_PD1;
	
	PIOD->PIO_SODR = PIO_PD1;
	
	// Combine the high and low bytes of the encoder data to one variable
	
	encoderdata = (encoderdataMSB<<8) | encoderdataLSB;
	
	//Set !OE high
	PIOD->PIO_SODR = PIO_PD0;
	
	return encoderdata;
}
