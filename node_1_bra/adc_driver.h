
#ifndef SRAM_H
#define SRAM_H

void adc_clock_signal(void);
void adc_write(uint8_t data, uint16_t addr);
uint8_t adc_read(uint16_t adrr);
int adc_init(void);

#endif