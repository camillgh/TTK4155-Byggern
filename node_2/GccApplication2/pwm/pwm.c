#include "sam.h"



void pwm_timercounter_init(void){
	
	// Enable clock on port C
	PMC->PMC_PCER0 |= (1 << ID_PIOC);
	
	// Enable clock
	PMC->PMC_PCER1 |= (1 << ID_PWM-32);
	
	// Disable input P44, used by PWM
	PIOC->PIO_PDR |= PIO_PDR_P19;
	
	// Set peripheral C on P44
	PIOC->PIO_ABSR |= PIO_ABSR_P19;
	
	// Select CLKA, MCK/2
	PWM->PWM_CLK |= PWM_CLK_DIVA(1) | PWM_CLK_PREA(6);
	
	
	PWM->PWM_CH_NUM[5].PWM_CMR |= (PWM_CMR_CPRE_CLKA);
	
	// Set period, 20 ms 
	PWM->PWM_CH_NUM[5].PWM_CPRD = 16*1640;
	
	// Set start duty cycle, 1.5ms
	PWM->PWM_CH_NUM[5].PWM_CDTY = 1312;
	
	// Enable channel
	PWM->PWM_ENA |= (PWM_ENA_CHID5);

}

void pwm_update_dutycycle(int32_t position){
	
	uint32_t dutycycle = 0;
	int32_t max_duty = 2755;
	int32_t min_duty = 1181;
	
	int32_t diff = max_duty - min_duty;
	
	
	if (position > 255) {
		position = 255;
	}
	if (position < 0) {
		position = 0;
	}

	
	dutycycle = (position/255.0)*diff + min_duty;

	if (dutycycle > max_duty){
		dutycycle = max_duty;
	}
	
	if (dutycycle < min_duty){
		dutycycle = min_duty;
	}
	
	PWM->PWM_CH_NUM[5].PWM_CDTYUPD = dutycycle;
	
	//printf("%d\n\r", dutycycle);
}