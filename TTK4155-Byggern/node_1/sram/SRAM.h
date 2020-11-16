/*
 * IncFile1.h
 *
 * Created: 03.09.2020 18:46:00
 *  Author: thomhagl
 */ 

#ifndef SRAM_H
#define SRAM_H

void SRAM_init(void);
void SRAM_test(void);
void SRAM_write(uint8_t data, uint16_t addr);
uint8_t SRAM_read(uint16_t adrr);

#endif