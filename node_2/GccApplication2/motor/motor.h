#ifdef MOTOR_H
#define MOTOR_H

uint16_t encoderdata;


void motor_init();
uint16_t motor_read_encoder(void);

#endif