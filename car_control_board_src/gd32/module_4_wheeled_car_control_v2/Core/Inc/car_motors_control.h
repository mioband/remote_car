/*
 * car_motors_control.h
 *
 *  Created on: Aug 19, 2022
 *      Author: admin
 */
#include <stdint.h>
#include "main.h"

#ifndef INC_CAR_MOTORS_CONTROL_H_
#define INC_CAR_MOTORS_CONTROL_H_


void init_motors(void);
void move_motor(uint8_t motor_num, uint8_t dir, uint16_t pwm);
void stop_motor(uint8_t motor_num);
void stop_all_motors(void);


#endif /* INC_CAR_MOTORS_CONTROL_H_ */
