#include "mcp2515_driver.h"
#include "mcp2515.h"
#include "SPI_com_driver.h"

#include <avr/io.h>
#include <time.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/pgmspace.h>

/**
 * \brief Select can controller
 *
 *
 * \param void
 * \retval void
 */


// Select CAN controller
void slave_select(){
	PORTB &= ~(1<<PB4);
}

/**
 * \brief Deselect CAN controller
 *
 *
 * \param void
 * \retval void
 */


// Deselect can controller
void slave_deselect(){
	PORTB |= (1<<PB4);
}

/**
 * \brief CAN initializiation
 *
 *
 * \param void
 * \retval Sucess(1) or Failure(0)
 */


uint8_t mcp2515_driver_init(){
	uint8_t value;
	
	// Initialize spi
	spi_init();
	
	// Send reset command
	mcp2515_reset();

	// Turn mask filters off, receive any messages
	mcp2515_write(MCP_RXB0CTRL,0x60);
	mcp2515_write(MCP_RXB1CTRL,0x70);
	
	// Set can bus timing 
	mcp2515_write(0x01, MCP_CNF3);
	mcp2515_write(0xb5, MCP_CNF2);
	mcp2515_write(0x43, MCP_CNF1);  //CAN BR NODE 2 0x290561
	
	// Configuration mode test
	value = mcp2515_read(MCP_CANSTAT);
	
	if ((value & MODE_MASK) != MODE_CONFIG){
		printf("MCP2515 is NOT in configuration mode after reset!\n\r");
		return 1;
	}
	
	
	// Set normal mode
	mcp2515_write(MODE_NORMAL, MCP_CANCTRL);
	
	return 0;
}

/**
 * \brief Read command for mcp2515
 *
 *
 * \param address
 * \retval result
 */


uint8_t mcp2515_read(uint8_t address){
	
	uint8_t result;
	
	// Select CAN
	slave_select();
	
	// Send read command
	spi_send(MCP_READ);

	// Send address
	spi_send(address);

	// Read data
	result = spi_receive();
	
	// Deselect can controller
	slave_deselect();
	
	return result;
	
}

/**
 * \brief Write command for mcp2515
 *
 *
 * \param data data to be send, 
 * \param address address that is written to
 * \retval void
 */

void mcp2515_write(uint8_t data, uint8_t address){
	
	// Selevt CAN
	slave_select();
	
	// MCP write command
	spi_send(MCP_WRITE);
	
	// Sending address
	spi_send(address);
	
	// Sending data
	spi_send(data);
	
	// Deselect CAN
	slave_deselect();
	
}

/**
 * \brief Request to send command for mcp2515
 *
 *
 * \param command Request to send command for mailbox
 * \retval void
 */

void mcp2515_request_to_send(char command){
	
	// Request to send commands:
	// MCP_RTS_TX0
	// MCP_RTS_TX1
	// MCP_RTS_TX2
	// MCP_RTS_TX3
	
	// Select CAN
	slave_select();
	
	// Send request to send command
	spi_send(command);
	
	// Deselect CAN
	slave_deselect();
	
}

/**
 * \brief Read status (modes) command mcp2515, 
 *
 *
 * \param void
 * \retval result status result
 */


uint8_t mcp2515_read_status(void){
	
	uint8_t result;
	
	// Select CAN
	slave_select();
	
	// Send read status command
	spi_send(MCP_READ_STATUS);

	// Read status
	result = spi_receive();
	
	// Deselect CAN
	slave_deselect();
	
	return result;
	
}

/**
 * \brief Bit modify command for mcp2515, modify bit at address
 *
 *
 * \param address bit address to be modified
 * \param mask bit mask
 * \param data bit to be modified
 * \retval result
 */

void mcp2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data){
	
	// Select CAN
	slave_select();
	
	// Send bit modify command
	spi_send(MCP_BITMOD);
	
	// Address we want to modify
	spi_send(address);
	
	// Bit mask
	spi_send(mask);
	
	// Modifying data
	spi_send(data);
	
	// Deselct CAN
	slave_deselect();
	
}

/**
 * \brief Reset command for mcp2515
 *
 *
 * \param void
 * \retval void
 */

void mcp2515_reset(){
	
	// Select CAN
	slave_select();
	
	// Send reset command
	spi_send(MCP_RESET);
	
	// Deselect can controller
	slave_deselect();
	
}