#ifndef UART_DRIVER_H
#define UART_DRIVER_H

void USART_init(unsigned int ubrr);
void USART_transmit(unsigned char c);
int USART_receive(void);

#endif