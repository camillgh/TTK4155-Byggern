#ifdef MOTOR_H
#define MOTOR_H

void motor_init();
void motor_control(uint16_t encoderdata, uint8_t position_x, CAN_MESSAGE *message, pidData_t *pid);
uint16_t motor_read_encoder(void);

#endif