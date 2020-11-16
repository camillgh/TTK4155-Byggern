#include <stdio.h>
#include <avr/io.h>
#include "UART_driver.h"
#define test_bit(reg, bit) (reg & (1 << bit))
#define loop_until_bit_is_set(reg, bit) while( !test_bit(reg, bit))
#define set_bit(reg, bit) (reg |= (1<< bit))

void USART_init(unsigned int ubrr){
	
	/* Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;			
	
	// Enable RX0 and TX0
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);

	// Connect printf to putty
	fdevopen(USART_transmit, USART_receive);

}

void USART_transmit(unsigned char data){

	// While transmit buffer not empty, then wait
	while(!(UCSR0A & (1<<UDRE0)));

	// Put data in buffer
	UDR0 = data;
}

int USART_receive(void){
	
	// Wait for data 
	while(!(UCSR0A & (1<<RXC0)));

	// Return received data
	return UDR0;
}
