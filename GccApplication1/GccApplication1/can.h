#include <avr/io.h>

#ifndef CAN_H
#define CAN_H

typedef struct{
	unsigned int id;
	uint8_t length;
	uint8_t data[8];
	
} can_message;

void can_init();
void can_send(can_message *message);
void can_receive(can_message *message); 
uint8_t can_transmission_completed();
 
 
#endif
