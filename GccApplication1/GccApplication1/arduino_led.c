#include <avr/io.h>
#include <avr/interrupt.h>
#include <time.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/pgmspace.h>

void led_init(void){
	// Activate PIO in PMC
	
	
	// Enable register PIO
	PIOA->PIO_PER = 0x1u << 1;
	
	// Set PIO as output
	PIOA->PIO_OER = 0x1u << 1;
	
}