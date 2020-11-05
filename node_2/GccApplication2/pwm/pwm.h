/*
 * pwm.h
 *
 * Created: 05.11.2020 12:34:42
 *  Author: thomhagl
 */ 


#ifndef PWM_H_
#define PWM_H_

void pwm_timercounter_init(void);
void pwm_update_dutycycle(int32_t position);

#endif /* PWM_H_ */