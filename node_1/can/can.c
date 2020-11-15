#include <avr/io.h>
#include <avr/interrupt.h>
#include <time.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/pgmspace.h>

#include "../can/mcp2515.h"
#include "../can/mcp2515_driver.h"
#include "../can/SPI_com_driver.h"
#include "../can/can.h"
#include "../config.h"

uint8_t can_flag = 0;

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
	
	mcp2515_bit_modify(MCP_CANINTE, 0xFF, 0x3);
	mcp2515_bit_modify(MCP_CANINTF, 0xFF, 0x00);
	
	DDRE &= ~(1<<PE0);
	
	//Enable global interrupts
	sei();

	value = mcp2515_read(MCP_CANSTAT);
	if ((value & MODE_MASK) != MODE_LOOPBACK){
		printf("MCP2515 is NOT set to LOOPBACK!\n\r");
		return 1;
	}
	
	//SREG |= 1<<7;
	//MCUCR &= ~(1<<ISC01 | 1<< ISC00);
	
}
void can_send(can_message *message){

	if (can_transmission_completed()){
		//printf("canstat3: %x \n \r", mcp2515_read(MCP_CANSTAT));
		// Id
		mcp2515_write(message->id >> 3, MCP_TXB1SIDH);
		mcp2515_write(message->id << 5, MCP_TXB1SIDL);
			
		// Data length
		mcp2515_write(message->length, MCP_TXB1DLC);
		//printf("canstat4: %x \n \r", mcp2515_read(MCP_CANSTAT));
		// Data
		for (int i = 0; i < message->length; i++){
			mcp2515_write(message->data[i], MCP_TXB1D0  + i);
			//printf("Send DATA0_%d: %d Wanted: %d \n \r",i,mcp2515_read(MCP_TXB1D0  + i), message->data[i]);
			//printf("TXB: %x \n \ r", MCP_TXB0D0 + i);
			//printf("canstat6: %x \n \r", mcp2515_read(MCP_CANSTAT));
		}

	}
	mcp2515_request_to_send(MCP_RTS_TX1);			
	//printf("canstat5: %x \n \r", mcp2515_read(MCP_CANSTAT));
}

void can_receive(can_message *message){
	
	if (can_flag){
		printf("Eg er inni can interupt, her va da koseleg \n\r\n\r");
		// Message id
		message->id = (mcp2515_read(MCP_RXB0SIDH << 3)) | (mcp2515_read(MCP_RXB0SIDL) >> 5);
		
		// Message length
		message->length = 0x0F & (mcp2515_read(MCP_RXB0DLC));
		//printf("--------- MESSAGE LENGTH!! : %d ------------ \n \r",message->length);

		// Message data
		for (int i = 0; i < message->length; i++){
			message->data[i] = mcp2515_read(MCP_RXB0D0  + i);
			//printf("DATA0_%d: %d \n \r",i, mcp2515_read(MCP_RXB0D0  + i));
			//printf("DATA1_%d: %d \n \r",i,mcp2515_read(MCP_RXB1D0  + i));
		}
		/*
		// Message id
		message.id = (mcp2515_read(MCP_RXB1SIDH << 3)) | (mcp2515_read(MCP_RXB1SIDL) >> 5);
		
		// Message length
		message.length = 0x0F & (mcp2515_read(MCP_RXB1DLC));
		
		// Message data
		for (int i = 0; i < 8; i++){
			message.data[i] = mcp2515_read(MCP_RXB1D0 + i);
			printf("DATA1: %c \n \r",message.data[i]);
		}
		*/
		can_flag = 0;
	}
	else{
		message->id = -1;
		
	}
	mcp2515_bit_modify(MCP_CANINTF, 0xff, 0);
}

uint8_t can_transmission_completed(){
	if (test_bit(mcp2515_read(MCP_TXB0CTRL), 3)){
		return 0;
	}
	else{
		return 1;
	}
}

uint8_t can_interrupt(){
	mcp2515_bit_modify(MCP_CANINTF, 0x01, 0);
	can_flag = 1;
}

ISR(INT2_vect){
	_delay_ms(10);
	
	can_interrupt();
	
}