/*
 * pid2.h
 *
 * Created: 15.11.2020 09:52:23
 *  Author: ivartg
 */ 

#include "stdint.h"
#include "sam.h"

#ifndef PID2_H_
#define PID2_H_
#define INT12_MAX 4095
#define SCALING_FACTOR 255
#define SETPOINT_MAX 255 //MAX_JOY

#define ENCODER_MAX 8500
#define ENCODER_SAFEZONE 0

static int32_t ref=0;
static int16_t last_error;
static int32_t sum_error;
int32_t max_sum_error;


void pid2_init(void);
void pid2_ref(uint8_t joy_pos);
int32_t pid2_controller(int16_t measurement);
void pid2_update_controller(void);

#endif /* PID2_H_ */