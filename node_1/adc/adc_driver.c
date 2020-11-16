#include "config.h"

#include <avr/io.h>
#include <time.h>
#include <util/delay.h>


/**
 * \brief Initializes adc
 *
 *
 * \param void
 * \retval 0
 */

int adc_init(void){
	
	// Enable external memory
	MCUCR |= (1 << SRE);
	SFIOR |= (1 << XMM2);
		
	return 0;
}


/**
 * \brief Make clock signal for ADC
 *
 *
 * \param void
 * \retval void
 */

void adc_clock_signal(void){
	
	// Clock signal on PB0	
	DDRB |= (1<< PB0);

	// Set CTC mode	
	TCCR0 |= (1<< WGM01);
	TCCR0 &= ~(1<< WGM00);
	TCCR0 |= (1<<COM00);
	TCCR0 |= (1<<CS00);

	// Set compare value for waveform
	OCR0 = 10;

}


/**
 * \brief Write command for adc
 *
 *
 * \param void
 * \retval void
 */

void adc_write(uint8_t data, uint16_t addr)
{
	// Pointer with starting at the adress for adc
	volatile char *ext_ram = (char *) 0x1400;
	
	ext_ram[addr] = data;
}

/**
 * \brief Read command for adc
 *
 *
 * \param channel adc channel
 * \retval data data from adc
 */

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

