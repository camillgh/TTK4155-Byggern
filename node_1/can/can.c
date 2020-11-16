#include "mcp2515.h"
#include "mcp2515_driver.h"
#include "SPI_com_driver.h"
#include "can.h"
#include "config.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <time.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/pgmspace.h>

uint8_t can_flag = 0;

/**
 * \brief Can initialization
 *
 *
 * \param void
 * \retval void
 */

void can_init(){

	// Initialize mcp
	mcp2515_driver_init();
	
	uint8_t value;
	
	// Disable global interrupt
	cli();
	
	// Set pullup resistor on PINE0
	PORTE |= (1<<PE0);
	
	// Interrupt on rising edge PE0
	EMCUCR |= (1<<ISC2);

	// Enable interrupt on PE0
	GICR |= (1<<INT2);
	
	// Enable interrupt on receive buffer
	mcp2515_bit_modify(MCP_CANINTE, 0xFF, 0x3);
	
	// Set interrupt flag on receive buffer to zero
	mcp2515_bit_modify(MCP_CANINTF, 0xFF, 0x00);
	
	// Set PE0 as input for interrupt
	DDRE &= ~(1<<PE0);
	
	//Enable global interrupts
	sei();
	
}

/**
 * \brief Send command for can
 *
 *
 * \param *message message to send
 * \retval void
 */

void can_send(can_message *message){

	if (can_transmission_completed()){
		
		// Id
		mcp2515_write(message->id >> 3, MCP_TXB1SIDH);
		mcp2515_write(message->id << 5, MCP_TXB1SIDL);
		
		// Data length
		mcp2515_write(message->length, MCP_TXB1DLC);
		
		// Data
		for (int i = 0; i < message->length; i++){
			mcp2515_write(message->data[i], MCP_TXB1D0  + i);
			
		}

	}

	// Request to send command
	mcp2515_request_to_send(MCP_RTS_TX1);
	
}

/**
 * \brief Receive command for can
 *
 *
 * \param *message message to receive
 * \retval void
 */

void can_receive(can_message *message){
	
	// If buffer has received a message, then proceed
	if (can_flag){
		
		// Message id
		message->id = (mcp2515_read(MCP_RXB0SIDH << 3)) | (mcp2515_read(MCP_RXB0SIDL) >> 5);
		
		// Message length
		message->length = 0x0F & (mcp2515_read(MCP_RXB0DLC));

		// Message data
		for (int i = 0; i < message->length; i++){
			message->data[i] = mcp2515_read(MCP_RXB0D0  + i);
			
		}
		
		// Message done reading, set can flag to zero
		can_flag = 0;
		
	}
	else{

		// Message not received
		message->id = -1;
		
	}

	// Reset interrupt
	mcp2515_bit_modify(MCP_CANINTF, 0xff, 0);
}

/**
 * \brief Checks if transmission is complete 
 *
 *
 * \param void
 * \retval Success(0) or failure(1)
 */

uint8_t can_transmission_completed(){
	
	// Checks if TX buffer has a pending transmission, if no then return 1
	if (test_bit(mcp2515_read(MCP_TXB0CTRL), 3)){
		return 0;
	}
	else{
		return 1;
	}
}

/**
 * \brief Runs if can interrupt is triggered
 *
 *
 * \param void
 * \retval void
 */

uint8_t can_interrupt(){

	// If CAN interrupt service is activated, then clear interrupt flag and set can flag
	// such that we can read message
	mcp2515_bit_modify(MCP_CANINTF, 0x01, 0);
	can_flag = 1;
}

/**
 * \brief Can interrupt routine
 *
 *
 * \param void
 * \retval void
 */




// Interrupt service for CAN
ISR(INT2_vect){
	_delay_ms(10);
	
	can_interrupt();
}