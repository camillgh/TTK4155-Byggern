#ifdef TIMER_H
#define TIMER_H

void systick_init(void);
void systick_delay_ms(uint16_t ms);
void SysTick_Handler(void);

#endif