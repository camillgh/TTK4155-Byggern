#include <avr/io.h>
#include "time.h"

/**
 * \brief Test program to output a square signal 
 *
 *
 * \param void
 * \retval void
 */

// Test program to output a square signal on PA0 
void test_program(void){

	while (1)
	{

		DDRA = 00000001;
		_delay_ms(1000);

		PORTA |= (1<< PA0);

		_delay_ms(1000);

		PORTA &= ~(1<< PA0);


	}
}