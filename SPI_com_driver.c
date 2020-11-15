 #include "SPI_com_driver.h"
 #include "mcp2515.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <time.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/pgmspace.h>

void spi_init(void){
	
	// Set MOSI, SCK and SS as output
	DDRB |= (1<<PB5)|(1<<PB7)|(1<<PB4);
	
	// Set MISO as input
	DDRB &= ~(1<<PB6);
	
	// Enable SPI, Master, set clock rate fck/16 
	SPCR |= (1<<SPE)|(1<<MSTR)|(1<<SPR0);
	
}

void spi_send(char cData){
	
	// Start transmission 
	SPDR = cData;
	
	// Wait for the transmission to complete 
	while (!(SPSR & (1<<SPIF))){
		;}
}

char spi_receive(void)
{
	// Send dummy byte
	spi_send(0);
	
	// Wait for reception complete
	while (!(SPSR & (1<<SPIF))){
		;
	}
	
	// Return data register 
	return SPDR;
}

