#include "sam.h"



/**
 * \brief Initializes the PWM signal for the servo angle
 *
 *
 * \param void
 * \retval void
 */

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

	//Select pre-scaler CLKA	
	PWM->PWM_CH_NUM[5].PWM_CMR |= (PWM_CMR_CPRE_CLKA);
	
	// Set period, 20 ms 
	PWM->PWM_CH_NUM[5].PWM_CPRD = 1640*16;
	
	// Set start duty cycle, 1.5ms (7.5% pulse width)
	PWM->PWM_CH_NUM[5].PWM_CDTY = 24272; //CPRD - CPRD*7.5%
	
	// Enable channel 5
	PWM->PWM_ENA |= (PWM_ENA_CHID5);

}


/**
 * \brief Updates the duty cycle of the PWM signal for the servo angle
 *
 *
 * \param position Joystick position 
 * \retval void
 */

void pwm_update_dutycycle(int32_t position){
	
	uint32_t dutycycle = 0;
	int32_t max_duty = 23490; //CPRD - CPRD * 2.1/20
	int32_t min_duty = 25055; //CPRD - CPRD * 0.9/20
	
	int32_t diff = min_duty-max_duty;
	
	// Limits joystick position range	
	if (position > 255) {
		position = 255;
	}
	if (position < 0) {
		position = 0;
	}

	// Calculates the new duty cycle	
	dutycycle = (position/255.0)*diff + max_duty;

	// Limits the new duty cycle
	if (dutycycle < max_duty){
		dutycycle = max_duty;
	}
	
	if (dutycycle > min_duty){
		dutycycle = min_duty;
	}
	
	// Updates duty cycle
	PWM->PWM_CH_NUM[5].PWM_CDTYUPD = dutycycle;
}