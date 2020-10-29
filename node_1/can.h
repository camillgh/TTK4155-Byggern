#include <avr/io.h>

#ifndef CAN_H
#define CAN_H

typedef struct{
	uint16_t id;
	char length;
	char data[8];
	
} can_message;

void can_init();
void can_send(can_message *message);
void can_receive(can_message *message); 
uint8_t can_transmission_completed();
 
 
#endif
