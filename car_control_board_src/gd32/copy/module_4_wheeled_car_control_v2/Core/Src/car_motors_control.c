/*
 * car_motors_control.c
 *
 *  Created on: Aug 19, 2022
 *      Author: AEra
 */
#include "car_motors_control.h"


extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;


#define PWM_MAX (htim2.Init.Period * 0.40)


typedef struct {
	uint16_t pin_dir_0;
	GPIO_TypeDef *pin_dir_0_port;
	uint16_t pin_dir_1;
	GPIO_TypeDef *pin_dir_1_port;
	TIM_HandleTypeDef *tim;
	uint32_t tim_ch;
} motor_pins;


motor_pins motor_1, motor_2, motor_3, motor_4;


static void init_motor_1(void) {
	motor_1.pin_dir_0 = DIG_AIN_1_Pin;
	motor_1.pin_dir_0_port = DIG_AIN_1_GPIO_Port;
	motor_1.pin_dir_1 = DIG_AIN_2_Pin;
	motor_1.pin_dir_1_port = DIG_AIN_2_GPIO_Port;
	motor_1.tim = &htim2;
	motor_1.tim_ch = TIM_CHANNEL_3;

	HAL_GPIO_WritePin(motor_1.pin_dir_0_port, motor_1.pin_dir_0, 0);
	HAL_GPIO_WritePin(motor_1.pin_dir_1_port, motor_1.pin_dir_1, 0);

	__HAL_TIM_SET_COMPARE(motor_1.tim, motor_1.tim_ch, 0);
	HAL_TIM_PWM_Start(motor_1.tim, motor_1.tim_ch);
}


static void init_motor_2(void) {
	motor_2.pin_dir_0 = DIG_BIN_1_Pin;
	motor_2.pin_dir_0_port = DIG_BIN_1_GPIO_Port;
	motor_2.pin_dir_1 = DIG_BIN_2_Pin;
	motor_2.pin_dir_1_port = DIG_BIN_2_GPIO_Port;
	motor_2.tim = &htim2;
	motor_2.tim_ch = TIM_CHANNEL_4;

	HAL_GPIO_WritePin(motor_2.pin_dir_0_port, motor_2.pin_dir_0, 0);
	HAL_GPIO_WritePin(motor_2.pin_dir_1_port, motor_2.pin_dir_1, 0);

	__HAL_TIM_SET_COMPARE(motor_2.tim, motor_2.tim_ch, 0);
	HAL_TIM_PWM_Start(motor_2.tim, motor_2.tim_ch);
}


static void init_motor_3(void) {
//	motor_3.pin_dir_0 = DIG_AIN_3_Pin;
//	motor_3.pin_dir_0_port = DIG_AIN_3_GPIO_Port;
//	motor_3.pin_dir_1 = DIG_AIN_4_Pin;
//	motor_3.pin_dir_1_port = DIG_AIN_4_GPIO_Port;
	motor_3.pin_dir_1 = DIG_AIN_3_Pin;
	motor_3.pin_dir_1_port = DIG_AIN_3_GPIO_Port;
	motor_3.pin_dir_0 = DIG_AIN_4_Pin;
	motor_3.pin_dir_0_port = DIG_AIN_4_GPIO_Port;
	motor_3.tim = &htim3;
	motor_3.tim_ch = TIM_CHANNEL_3;

	HAL_GPIO_WritePin(motor_3.pin_dir_0_port, motor_3.pin_dir_0, 0);
	HAL_GPIO_WritePin(motor_3.pin_dir_1_port, motor_3.pin_dir_1, 0);

	__HAL_TIM_SET_COMPARE(motor_3.tim, motor_3.tim_ch, 0);
	HAL_TIM_PWM_Start(motor_3.tim, motor_3.tim_ch);
}


static void init_motor_4(void) {
//	motor_4.pin_dir_0 = DIG_BIN_3_Pin;
//	motor_4.pin_dir_0_port = DIG_BIN_3_GPIO_Port;
//	motor_4.pin_dir_1 = DIG_BIN_4_Pin;
//	motor_4.pin_dir_1_port = DIG_BIN_4_GPIO_Port;
	motor_4.pin_dir_1 = DIG_BIN_3_Pin;
	motor_4.pin_dir_1_port = DIG_BIN_3_GPIO_Port;
	motor_4.pin_dir_0 = DIG_BIN_4_Pin;
	motor_4.pin_dir_0_port = DIG_BIN_4_GPIO_Port;
	motor_4.tim = &htim3;
	motor_4.tim_ch = TIM_CHANNEL_4;

	HAL_GPIO_WritePin(motor_4.pin_dir_0_port, motor_4.pin_dir_0, 0);
	HAL_GPIO_WritePin(motor_4.pin_dir_1_port, motor_4.pin_dir_1, 0);

	__HAL_TIM_SET_COMPARE(motor_4.tim, motor_4.tim_ch, 0);
	HAL_TIM_PWM_Start(motor_4.tim, motor_4.tim_ch);
}


void init_motors(void) {
	init_motor_1();
	init_motor_2();
	init_motor_3();
	init_motor_4();
}


static void set_motor_dir_pwm(motor_pins *mt, uint8_t dr, uint16_t pulse) {
	switch (dr) {
		case 0:
			HAL_GPIO_WritePin(mt->pin_dir_1_port, mt->pin_dir_1, 0);
			HAL_GPIO_WritePin(mt->pin_dir_0_port, mt->pin_dir_0, 1);
			break;
		case 1:
			HAL_GPIO_WritePin(mt->pin_dir_0_port, mt->pin_dir_0, 0);
			HAL_GPIO_WritePin(mt->pin_dir_1_port, mt->pin_dir_1, 1);
			break;
		default:
			HAL_GPIO_WritePin(mt->pin_dir_0_port, mt->pin_dir_0, 0);
			HAL_GPIO_WritePin(mt->pin_dir_1_port, mt->pin_dir_1, 0);
			break;
	}

	if (pulse > PWM_MAX) pulse = PWM_MAX;
	__HAL_TIM_SET_COMPARE(mt->tim, mt->tim_ch, pulse);
}


void move_motor(uint8_t motor_num, uint8_t dir, uint16_t pwm) {
	switch (motor_num) {
		case 1:
			set_motor_dir_pwm(&motor_1, dir, pwm);
			break;
		case 2:
			set_motor_dir_pwm(&motor_2, dir, pwm);
			break;
		case 3:
			set_motor_dir_pwm(&motor_3, dir, pwm);
			break;
		case 4:
			set_motor_dir_pwm(&motor_4, dir, pwm);
			break;
	}
}


void stop_motor(uint8_t motor_num) {
	switch (motor_num) {
		case 1:
			set_motor_dir_pwm(&motor_1, 2, 0);
			break;
		case 2:
			set_motor_dir_pwm(&motor_2, 2, 0);
			break;
		case 3:
			set_motor_dir_pwm(&motor_3, 2, 0);
			break;
		case 4:
			set_motor_dir_pwm(&motor_4, 2, 0);
			break;
	}
}


void stop_all_motors(void) {
	set_motor_dir_pwm(&motor_1, 2, 0);
	set_motor_dir_pwm(&motor_2, 2, 0);
	set_motor_dir_pwm(&motor_3, 2, 0);
	set_motor_dir_pwm(&motor_4, 2, 0);
}
