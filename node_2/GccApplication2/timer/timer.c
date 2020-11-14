#include "sam.h"

volatile uint32_t period = 0;

void systick_init_ms(void){
	
	// Set the reload register
	SysTick->LOAD = (10500 & SysTick_LOAD_RELOAD_Msk)-1;
	
	// Clear register
	SysTick->VAL = 0;
	
	// interrupt
	//NVIC_SetPriority(SysTick_IRQn, IRQ)
	
	SysTick->CTRL |= (0b0 << SysTick_CTRL_CLKSOURCE_Pos) & SysTick_CTRL_CLKSOURCE_Msk | (0b1 << SysTick_CTRL_TICKINT_Pos) & (SysTick_CTRL_TICKINT_Msk) | (0b1 << SysTick_CTRL_ENABLE_Pos) & SysTick_CTRL_ENABLE_Msk; 
	
}

void systick_init_us(void){
	
	// Set the reload register
	SysTick->LOAD = (11 & SysTick_LOAD_RELOAD_Msk)-1;
	
	// Clear register
	SysTick->VAL = 0;
	
	// interrupt
	//NVIC_SetPriority(SysTick_IRQn, IRQ)
	
	SysTick->CTRL |= (0b0 << SysTick_CTRL_CLKSOURCE_Pos) & SysTick_CTRL_CLKSOURCE_Msk | (0b1 << SysTick_CTRL_TICKINT_Pos) & (SysTick_CTRL_TICKINT_Msk) | (0b1 << SysTick_CTRL_ENABLE_Pos) & SysTick_CTRL_ENABLE_Msk;
	
}

void systick_delay_ms(int ms){
	period = ms;
	systick_init_ms();
	while(period){
		__asm__("nop");
	}


	
}

void systick_delay_us(int us){
	period = us;
	systick_init_us();
	while(period){
		__asm__("nop");
	}
}


void pid_timercounter_init(void){
	
	// Interrupt enable
	PWM->PWM_IER1 = PWM_IER1_CHID3;
	
	// Enable clock on port C
	//PMC->PMC_PCER0 |= (1 << ID_PIOC);
	
	// Enable clock
	PMC->PMC_PCER1 |= (1 << ID_PWM-32);
	
	
	// Select CLKA, MCK/2
	PWM->PWM_CLK |= PWM_CLK_DIVA(1) | PWM_CLK_PREA(6);
	
	
	PWM->PWM_CH_NUM[3].PWM_CMR |= (PWM_CMR_CPRE_CLKA);
	
	// Set period, 20 ms
	PWM->PWM_CH_NUM[3].PWM_CPRD = 1640*16;
	
	// Set start duty cycle, 1.5ms (7.5% pulse width)

	PWM->PWM_CH_NUM[3].PWM_CDTY = 24272; //CPRD - CPRD*7.5%
	
	// Enable channel
	PWM->PWM_ENA |= (PWM_ENA_CHID3);
	
	

}


void SysTick_Handler(void){
	//SysTick->CTRL = (0<<SysTick_CTRL_ENABLE_Pos);
	//SysTick->VAL = (0<<SysTick_VAL_CURRENT_Pos);
	
	if (period == 0)
	{
		// Disable counter
		SysTick->CTRL = 0;
		SysTick->VAL = 0;
	}else{
		period--;
	}		
}