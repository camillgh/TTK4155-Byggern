#include "sam.h"

void systick_init_ms(void){
	
	// Set interrupt
	SysTick->CTRL = (SysTick_CTRL_TICKINT_Msk);
	
	// Clear register
	SysTick->VAL = (0<<SysTick_VAL_CURRENT_Pos);
	
}

void systick_delay_ms(uint16_t ms){
	
	// Clear register
	SysTick->VAL = (0<<SysTick_VAL_CURRENT_Pos);
	
	// Set the reload register
	SysTick->LOAD = ms*(84000UL-1UL);
	
	// Start counter
	SysTick->CTRL = (SysTick_CTRL_ENABLE_Msk);
	
}

void SysTick_Handler(void){
	SysTick->CTRL = (0<<SysTick_CTRL_ENABLE_Pos);
	SysTick->VAL = (0<<SysTick_VAL_CURRENT_Pos);
}