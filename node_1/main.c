/*
 * TTK4155 Byggern prosjekt.c
 *
 * Created: 27.08.2020 08:45:11
 * Author : thomhagl
 */ 

#include <avr/io.h>
#include <time.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include "UART_driver.h"
#include "config.h"
#include "SRAM.h"
#include "adc_driver.h"



void main(void){
	USART_init(MYUBRR);
	SRAM_init();
	//SRAM_test();
	adc_clock_signal();
	while(1){
		printf(adc_read(0));
	}
}