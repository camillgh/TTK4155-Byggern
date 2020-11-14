/*
 * pid.h
 *
 * Created: 09.11.2020 11:13:25
 *  Author: thomhagl
 */ 


#ifndef PID_H_
#define PID_H_



#include "stdint.h"

#define SCALING_FACTOR 128


//! Summation of errors, used for integrate calculations

/*! \brief PID Status
 *
 * Setpoints and data used by the PID control algorithm
 

/*
 *
 * Needed to avoid sign/overflow problems
 */
// Maximum value of variables
#define MAX_INT INT8_MAX
#define MAX_LONG INT32_MAX
#define MAX_I_TERM (MAX_LONG / 2)

// Boolean values
#define FALSE 0
void    pid_Init(int16_t p_factor, int16_t i_factor, int16_t d_factor);
int16_t pid_Controller(int16_t referancePos, uint16_t encoderData); //, int32_t sumError);
//void    pid_Reset_Integrator(pidData_t *pid_st);



#endif /* PID_H_ */