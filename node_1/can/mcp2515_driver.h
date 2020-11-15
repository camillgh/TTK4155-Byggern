#include <avr/io.h>

#ifndef MCP2515_DRIVER_H
#define MCP2515_DRIVER_H

void slave_select();

void slave_deselect();

uint8_t mcp2515_driver_init();

uint8_t mcp2515_read(uint8_t address);

void mcp2515_write(uint8_t data, uint8_t address);

void mcp2515_request_to_send(char command);

uint8_t mcp2515_read_status(void);

void mcp2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data);

void mcp2515_reset();

#endif