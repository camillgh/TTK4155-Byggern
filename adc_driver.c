#include "config.h"
#include <avr/io.h>
#include <time.h>
#include <util/delay.h>


int adc_init(void){

	// Enable external memory
	MCUCR |= (1 << SRE);
	SFIOR |= (1 << XMM2);
	
	// Set interrupt on PINE0
	DDRE &= ~(1<<PINE0);
	
	return 0;
}


// Clock signal for adc
void adc_clock_signal(void){
	
	// Clock signal on PB0
	DDRB |= (1<< PB0);
	
	// Set CTC mode
	TCCR0 |= (1<< WGM01);
	TCCR0 &= ~(1<< WGM00);
	
	// Clear OC0 on Compare match
	TCCR0 |= (1<<COM00);
	TCCR0 |= (1<<CS00);

	// Set compare value for clock waveform
	OCR0 = 10;

}

void adc_write(uint8_t data, uint16_t addr)
{
	// Pointer starting at the adress for adc
	volatile char *ext_ram = (char *) 0x1400;

	// Write data
	ext_ram[addr] = data;
}

uint8_t adc_read(uint8_t channel){

	// Pointer starting at the adress for adc
	volatile char *adc = (char *) 0x1400;
	
	uint8_t data;
	
	// Select channel
	adc[0] = 0b10000000 | channel;

	_delay_us(100);
	
	// Get data from channel
	data = adc[0];
	
	return data;
}

