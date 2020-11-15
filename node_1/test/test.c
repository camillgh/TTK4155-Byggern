#include <avr/io.h>

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