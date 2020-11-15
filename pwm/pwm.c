#include "sam.h"



void pwm_timercounter_init(void){
	
	// Enable clock on port C
	PMC->PMC_PCER0 |= (1 << ID_PIOC);
	
	// Enable clock
	PMC->PMC_PCER1 |= (1 << ID_PWM-32);
	
	// Disable input Pin44, used by PWM
	PIOC->PIO_PDR |= PIO_PDR_P19;
	
	// Set peripheral C on Pin44
	PIOC->PIO_ABSR |= PIO_ABSR_P19;
	
	// Activate CLKA, set MCK/2
	PWM->PWM_CLK |= PWM_CLK_DIVA(1) | PWM_CLK_PREA(6);
	
	// Select CLKA
	PWM->PWM_CH_NUM[5].PWM_CMR |= (PWM_CMR_CPRE_CLKA);
	
	// Set period, 20 ms 
	PWM->PWM_CH_NUM[5].PWM_CPRD = 1640*16;
	
	// Set start duty cycle, 1.5ms (7.5% pulse width)
	PWM->PWM_CH_NUM[5].PWM_CDTY = 24272; //CPRD - CPRD*7.5%
	
	// Enable channel
	PWM->PWM_ENA |= (PWM_ENA_CHID5);

}

void pwm_update_dutycycle(int32_t position){
	
	uint32_t dutycycle = 0;

	// Max and min value to put in CDTYUPD registor for duty cycle to be in range 0.9-2.1 [ms]
	int32_t max_duty = 23490; //CPRD - CPRD * 2.1/20
	int32_t min_duty = 25055; //CPRD - CPRD * 0.9/20
	
	// Used in a linear model on the form y=ax+b to scale the duty cycle in range 0.9-2.1ms when using the joystick
	int32_t diff = min_duty-max_duty;
	
	// Limit on the joystick signal
	if (position > 255) {
		position = 255;
	}
	if (position < 0) {
		position = 0;
	}

	// Calculate value for dutycycle
	dutycycle = (position/255.0)*diff + max_duty;
	
	// Limit on duty cycle
	if (dutycycle < max_duty){
		dutycycle = max_duty;
	}
	
	if (dutycycle > min_duty){
		dutycycle = min_duty;
	}
	
	// Set new duty cycle
	PWM->PWM_CH_NUM[5].PWM_CDTYUPD = dutycycle;
	
}