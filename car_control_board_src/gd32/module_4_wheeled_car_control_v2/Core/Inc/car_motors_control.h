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

/* structure for keeping controlling pins, ports, timer stuff */
typedef struct {
	uint16_t pin_dir_0;
	GPIO_TypeDef *pin_dir_0_port;
	uint16_t pin_dir_1;
	GPIO_TypeDef *pin_dir_1_port;
	TIM_HandleTypeDef *tim;
	uint32_t tim_ch;
} motor_pins_s;

#endif /* INC_CAR_MOTORS_CONTROL_H_ */
