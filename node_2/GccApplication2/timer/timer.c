#include "sam.h"

volatile uint32_t period = 0;


/**
 * \brief Initializes the ms delay
 *
 *
 * \param void
 * \retval void
 */

void systick_init_ms(void){
	
	// Set the reload register with reload value corresponding to 1ms = 10500
	SysTick->LOAD = (10500 & SysTick_LOAD_RELOAD_Msk)-1;
	
	// Clear register
	SysTick->VAL = 0;
	
	// Sets CLKSOURCE, TICKINT (enables SysTick exception request) and ENABLE (enables the counter)
	SysTick->CTRL |= (0b0 << SysTick_CTRL_CLKSOURCE_Pos) & SysTick_CTRL_CLKSOURCE_Msk | (0b1 << SysTick_CTRL_TICKINT_Pos) & (SysTick_CTRL_TICKINT_Msk) | (0b1 << SysTick_CTRL_ENABLE_Pos) & SysTick_CTRL_ENABLE_Msk; 
	
}



/**
 * \brief Initializes the us delay
 *
 *
 * \param void
 * \retval void
 */

void systick_init_us(void){
	
	// Set the reload register with reload value corresponding to 1 us = 11
	SysTick->LOAD = (11 & SysTick_LOAD_RELOAD_Msk)-1;
	
	// Clear register
	SysTick->VAL = 0;
	
	// Sets CLKSOURCE, TICKINT (enables SysTick exception request) and ENABLE (enables the counter)	
	SysTick->CTRL |= (0b0 << SysTick_CTRL_CLKSOURCE_Pos) & SysTick_CTRL_CLKSOURCE_Msk | (0b1 << SysTick_CTRL_TICKINT_Pos) & (SysTick_CTRL_TICKINT_Msk) | (0b1 << SysTick_CTRL_ENABLE_Pos) & SysTick_CTRL_ENABLE_Msk;
	
}



/**
 * \brief Runs a ms delay
 *
 *
 * \param ms Number of milliseconds
 * \retval void
 */

void systick_delay_ms(int ms){
	
	period = ms;
	systick_init_ms();
	
	// Traps the system in a delay as long as period != 0
	while(period){
		__asm__("nop");
	}


	
}



/**
 * \brief Runs a us delay
 *
 *
 * \param ms Number of microseconds
 * \retval void
 */

void systick_delay_us(int us){
	
	period = us;
	systick_init_us();
	
	// Traps the system in a delay as long as period != 0
	while(period){
		__asm__("nop");
	}
}


/**
 * \brief Handles a SysTick exception
 *
 *
 * \param void
 * \retval void
 */

void SysTick_Handler(void){
	
	if (period == 0)
	{
		// Disables the counter
		
		SysTick->CTRL = 0;
		SysTick->VAL = 0;
		
	} else {
		
		// Decrements the counter
		period--;
		
	}		
}