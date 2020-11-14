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

//! Last process value, used to find derivative of process value.
int16_t lastProcessValue = 0;
//! The Proportional tuning constant, multiplied with SCALING_FACTOR
const int16_t P_Factor = 1;
//! The Integral tuning constant, multiplied with SCALING_FACTOR
int16_t I_Factor = 1;
//! The Derivative tuning constant, multiplied with SCALING_FACTOR
int16_t D_Factor = 0;
//! Maximum allowed error, avoid overflow
int16_t maxError =  MAX_INT / (1 + 1);
//! Maximum allowed sumerror, avoid overflow
int32_t maxSumError = MAX_I_TERM / (1 + 1);

/*
void pid_Init(int16_t p_factor, int16_t i_factor, int16_t d_factor)
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
*/

/*! \brief PID control algorithm.
 *
 *  Calculates output from referancePos, process value and PID status.
 *
 *  \param referancePos  Desired value.
 *  \param encoderData  Measured value.
 *  \param pid_st  PID status struct.
 */


uint32_t sumError = 0;


int16_t pid_Controller(int16_t referancePos, uint16_t encoderData) //, int32_t sumError)
{
	int16_t P_Factor = 1;
	int16_t I_Factor = 1;

	int16_t error, p_term, d_term;
	int32_t i_term, ret, temp;
		
	//Adjust the encoderData to 
	encoderData = (encoderData/17500.0)*255;
	
	//Out of bounds

	if (encoderData < 0){
		encoderData = 0;
	}
	else if (encoderData > 255){
		encoderData = 255;
	}
	//printf("EncoderData %d\n\r", encoderData);
	//Calculate error
	error = referancePos - encoderData;
	printf("Errorrr %d\n\r", error);
	printf("encoder %d\n\r", encoderData);
	//Integral term
	sumError = sumError + error;
	printf("sumerror %d\n\r", sumError);

	if (sumError = 20000){
		sumError = 0;
	}
	
	i_term =  I_Factor*sumError;
	
	//Proportional term
	p_term = P_Factor*error;
	

	ret = p_term + i_term; //+ d_term
	
	//printf("p_term %d\n\r", p_term);
	
	printf("\n\r");
	
	if (ret > 1300){
		ret = 1300;
	} else if (ret < 0){
		ret = 0;
	}
	
	
	//Set direction
	if (error > 0) {
		PIOD->PIO_CODR = PIO_PD10;
		dac_write((int16_t)ret);
	} else {
		PIOD->PIO_SODR = PIO_PD10;
		dac_write((int16_t)ret);
	}
	
	
	lastProcessValue = encoderData;
	
	
	//return ((int16_t)ret);
}

/*! \brief Resets the integrator.
 *
 *  Calling this function will reset the integrator in the PID regulator.
 */
/*
void pid_Reset_Integrator(pidData_t *pid_st)
{
	 sumError = 0;
}
*/