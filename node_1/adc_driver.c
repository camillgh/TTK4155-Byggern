#include "config.h"

#include <avr/io.h>
#include <time.h>
#include <util/delay.h>

//volatile char *adc = (char *) 0x1400;


int adc_init(void){
	MCUCR |= (1 << SRE);
	SFIOR |= (1 << XMM2);
	
	DDRE &= ~(1<<PINE0);
	
	//*adc = 1;
	//*adc = 2;
	//*adc = 3;
	//*adc = 4;
	
	return 0;
}



void adc_clock_signal(void){
	
	DDRB |= (1<< PB0);
	
	TCCR0 |= (1<< WGM01);
	//TCCR0 = 0X11;
	TCCR0 &= ~(1<< WGM00);
	
	TCCR0 |= (1<<COM00);
	//TCCR0 |= (1<<COM01);
	
	TCCR0 |= (1<<CS00);
	//TCCR0 |= (1<<CS01);
	//TCCR0 |= (1<<CS02);

	
	OCR0 = 10;
	
	
	//DDRD &= ~(1 << DDD2);
	//PORTD |= (1<< PD4);
}

void adc_write(uint8_t data, uint16_t addr)
{
	volatile char *ext_ram = (char *) 0x1400;
	ext_ram[addr] = data;
}

uint8_t adc_read(uint8_t channel){
	volatile char *adc = (char *) 0x1400;
	uint8_t data;
	
	adc[0] = 0b10000000 | channel;

	_delay_us(100);
	
	data = adc[0];
	
	return data;
}

//uint8_t adc_read(uint16_t adrr){
//	volatile char *ext_ram = (char *) 0x1400;
//	uint8_t ret_val = ext_ram[adrr];
//	return ret_val;
//}

