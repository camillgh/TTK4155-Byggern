/*
 * pid.h
 *
 * Created: 15.11.2020 09:52:23
 *  Author: ivartg
 */ 

#include "stdint.h"
#include "sam.h"

#ifndef PID_H_
#define PID_H_

#define DEC_INT12 4095
#define SCALING_FACTOR 255

#define JOY_MAX 255 
#define ENC_MAX 8500

static int32_t joy_ref = 0;
static int16_t last_error;
static int32_t sum_error;
int32_t max_sum_error;


void pid_init(void);
void pid_ref(uint8_t joy_pos);
int32_t pid_controller(int16_t enc_pos);
void pid_update(void);
void pid_timercounter_init();


#endif /* PID_H_ */