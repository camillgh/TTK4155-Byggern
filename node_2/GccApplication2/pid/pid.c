/*
 * pid.c
 *
 * Created: 09.11.2020 11:13:05
 *  Author: thomhagl
 */ 

/*! \file *********************************************************************
 *
 * \brief General PID implementation for AVR.
 *
 * Discrete PID controller implementation. Set up by giving P/I/D terms
 * to Init_PID(), and uses a struct PID_DATA to store internal values.
 *
 *
 *****************************************************************************/

#include "pid.h"
#include "stdint.h"
#include "sam.h"

/*! \brief Initialization of PID controller parameters.
 *
 *  Initialize the variables used by the PID algorithm.
 *
 *  \param p_factor  Proportional term.
 *  \param i_factor  Integral term.
 *  \param d_factor  Derivate term.
 *  \param pid  Struct with PID status.
 */
void pid_Init(int16_t p_factor, int16_t i_factor, int16_t d_factor, struct PID_DATA *pid)
{
	// Start values for PID controller
	pid->sumError         = 0;
	pid->lastProcessValue = 0;
	// Tuning constants for PID loop
	pid->P_Factor = p_factor;
	pid->I_Factor = i_factor;
	//pid->D_Factor = d_factor;
	// Limits to avoid overflow
	pid->maxError    = MAX_INT / (pid->P_Factor + 1);
	pid->maxSumError = MAX_I_TERM / (pid->I_Factor + 1);
}

/*! \brief PID control algorithm.
 *
 *  Calculates output from referancePos, process value and PID status.
 *
 *  \param referancePos  Desired value.
 *  \param encoderData  Measured value.
 *  \param pid_st  PID status struct.
 */
int16_t pid_Controller(int16_t referancePos, int16_t encoderData, struct PID_DATA *pid_st)
{
	int16_t errors, p_term, d_term;
	int32_t i_term, ret, temp;
	
	encoderData = (encoderData/18000.0)*255;

	if (encoderData < 0){
		encoderData = 0;
	}
	else if (encoderData > 255){
			encoderData = 255;
	}
	printf("%d\n\r", encoderData);
	errors = referancePos - encoderData;

	// Calculate Pterm and limit error overflow
	if (errors > pid_st->maxError) {
		p_term = MAX_INT;
	} else if (errors < -pid_st->maxError) {
		p_term = -MAX_INT;
	} else {
		p_term = pid_st->P_Factor * errors;
	}

	// Calculate Iterm and limit integral runaway
	temp = pid_st->sumError + errors;
	if (temp > pid_st->maxSumError) {
		i_term           = MAX_I_TERM;
		pid_st->sumError = pid_st->maxSumError;
	} else if (temp < -pid_st->maxSumError) {
		i_term           = -MAX_I_TERM;
		pid_st->sumError = -pid_st->maxSumError;
	} else {
		pid_st->sumError = temp;
		i_term           = pid_st->I_Factor * pid_st->sumError;
	}

	// Calculate Dterm
	//d_term = pid_st->D_Factor * (pid_st->lastProcessValue - encoderData);

	pid_st->lastProcessValue = encoderData;

	ret = (p_term + i_term + d_term) / SCALING_FACTOR;
	if (ret > MAX_INT) {
		ret = MAX_INT;
	} else if (ret < -MAX_INT) {
		ret = -MAX_INT;
	}

	return ((int16_t)ret);
}

/*! \brief Resets the integrator.
 *
 *  Calling this function will reset the integrator in the PID regulator.
 */
void pid_Reset_Integrator(pidData_t *pid_st)
{
	pid_st->sumError = 0;
}
