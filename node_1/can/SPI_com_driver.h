#include <avr/io.h>
#ifndef SPI_COM_DRIVER_H
#define SPI_COM_DRIVER_H

void spi_init(void);
void spi_send(char cData);
char spi_receive(void);

#endif