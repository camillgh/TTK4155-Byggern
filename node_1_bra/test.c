/*
 * TTK4155 Byggern prosjekt.c
 *
 * Created: 27.08.2020 08:45:11
 * Author : thomhagl
 */ 

#define F_CPU 4915200UL
#include <avr/io.h>
#include <time.h>
#include <util/delay.h>
#include <stdio.h>



int main(void)
{
    /* Replace with your application code */
    	
	while (1) 
    {
			
		DDRA = 00000001;	
		_delay_ms(1000);
		
		PORTA |= (1<< PA0);

		_delay_ms(1000);

		PORTA &= ~(1<< PA0);
	

    }
}


