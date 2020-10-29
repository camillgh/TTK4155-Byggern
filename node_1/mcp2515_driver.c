#include "mcp2515_driver.h"
#include "mcp2515.h"
#include "SPI_com_driver.h"

#include <avr/io.h>
#include <time.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/pgmspace.h>

// Select can controller
void slave_select(){
	PORTB &= ~(1<<PB4);
}


// Deselect can controller
void slave_deselect(){
	PORTB |= (1<<PB4);
}


uint8_t mcp2515_driver_init(){
	uint8_t value;
	
	// Initialize spi
	spi_init();
	
	// Send reset command
	mcp2515_reset();
	mcp2515_write(0x60,0x60);
	mcp2515_write(0x60,0x70);
	// Self test
	
	//mcp2515_bit_modify(MCP_CANCTRL,MODE_MASK,MODE_LOOPBACK);
	value = mcp2515_read(MCP_CANSTAT);
	//printf("val: %x \n \r", value);
	mcp2515_write(0x01, MCP_CNF3);
	mcp2515_write(0xb5, MCP_CNF2);
	mcp2515_write(0x43, MCP_CNF1);  //CAN BR NODE 2 0x290561
	if ((value & MODE_MASK) != MODE_CONFIG){
		printf("MCP2515 is NOT in configuration mode after reset!\n\r");
		return 1;
	}
	_delay_ms(1000);
	//printf("Canstat after reset: %d",  value);
	mcp2515_write(MODE_NORMAL, MCP_CANCTRL); 
	//_delay_ms();  
	value = mcp2515_read(MCP_CANSTAT);
	printf("%d \n\r", value);
	if ((value & MODE_MASK) != MODE_LOOPBACK){
		printf("MCP2515 is NOT set to LOOPBACK!\n\r");
		return 1;
	}
	
	
	
	return 0;
}

uint8_t mcp2515_read(uint8_t address){
	
	uint8_t result;
	
	slave_select();
	
	spi_send(MCP_READ);
	spi_send(address);
	result = spi_receive();
	
	slave_deselect();
	
	return result;
	
}


void mcp2515_write(uint8_t data, uint8_t address){
	
	slave_select();
	
	// MCP write command
	spi_send(MCP_WRITE);
	
	// Sending address
	spi_send(address);
	
	// Sending data
	spi_send(data);
	
	slave_deselect();
	
}

void mcp2515_request_to_send(char command){
	
	// MCP_RST_TX0
	// MCP_RST_TX1
	// MCP_RST_TX2
	// MCP_RST_TX3
	
	slave_select();
	
	spi_send(command);
	
	slave_deselect();
	
}


uint8_t mcp2515_read_status(void){
	
	uint8_t result;
	
	slave_select();
	
	spi_send(MCP_READ_STATUS);
	result = spi_receive();
	
	slave_deselect();
	
	return result;
	
}

void mcp2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data){
	
	slave_select();
	
	// Send bit modify command
	spi_send(MCP_BITMOD);
	
	// Address we want to modify
	spi_send(address);
	
	// Bit mask
	spi_send(mask);
	
	// Modifying data
	spi_send(data);
	
	slave_deselect();
	
}

void mcp2515_reset(){
	
	// Select can controller
	slave_select();
	
	// Send reset command
	spi_send(MCP_RESET);
	
	// Deselect can controller
	slave_deselect();
	
}