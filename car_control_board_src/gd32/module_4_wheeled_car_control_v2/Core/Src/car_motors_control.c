/*
 * car_motors_control.c
 *
 *  Created on: Aug 19, 2022
 *      Author: AEra
 */
#include "car_motors_control.h"

/* timers for controlling the motors using PWM mode */
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

/* limitation of PWM signal */
#define PWM_MAX (htim2.Init.Period * 0.40)

/* motors structures */
motor_pins_s motor_1, motor_2, motor_3, motor_4;

/**
* @brief Initialization of the motor
* @retval None
*/
static void init_motor(motor_pins_s *p_motor, uint16_t dir_0_pin, GPIO_TypeDef *dir_0_prt, uint16_t dir_1_pin, GPIO_TypeDef *dir_1_prt, TIM_HandleTypeDef *p_tim, uint32_t t_channel) {
	p_motor->pin_dir_0 = dir_0_pin;
	p_motor->pin_dir_0_port = dir_0_prt;
	p_motor->pin_dir_1 = dir_1_pin;
	p_motor->pin_dir_1_port = dir_1_prt;
	p_motor->tim = p_tim;
	p_motor->tim_ch = t_channel;

	HAL_GPIO_WritePin(p_motor->pin_dir_1_port, p_motor->pin_dir_1, 0);
	HAL_GPIO_WritePin(p_motor->pin_dir_0_port, p_motor->pin_dir_0, 0);

	__HAL_TIM_SET_COMPARE(p_motor->tim, p_motor->tim_ch, 0);
	HAL_TIM_PWM_Start(p_motor->tim, p_motor->tim_ch);
}

/**
* @brief Initialization of the all motors
* @retval None
*/
#define BROWN_TANK
//#define GREEN_TANK
void init_motors(void) {
#if defined (BROWN_TANK)
	init_motor(&motor_2, DIG_AIN_1_Pin, DIG_AIN_1_GPIO_Port, DIG_AIN_2_Pin, DIG_AIN_2_GPIO_Port, &htim2, TIM_CHANNEL_3);
	init_motor(&motor_1, DIG_BIN_1_Pin, DIG_BIN_1_GPIO_Port, DIG_BIN_2_Pin, DIG_BIN_2_GPIO_Port, &htim2, TIM_CHANNEL_4);
//	init_motor(&motor_3, DIG_AIN_3_Pin, DIG_AIN_3_GPIO_Port, DIG_AIN_4_Pin, DIG_AIN_4_GPIO_Port, &htim3, TIM_CHANNEL_3);
//	init_motor(&motor_4, DIG_BIN_3_Pin, DIG_BIN_3_GPIO_Port, DIG_BIN_4_Pin, DIG_BIN_4_GPIO_Port, &htim3, TIM_CHANNEL_4);
	init_motor(&motor_3, DIG_AIN_4_Pin, DIG_AIN_4_GPIO_Port, DIG_AIN_3_Pin, DIG_AIN_3_GPIO_Port, &htim3, TIM_CHANNEL_3);
	init_motor(&motor_4, DIG_BIN_4_Pin, DIG_BIN_4_GPIO_Port, DIG_BIN_3_Pin, DIG_BIN_3_GPIO_Port, &htim3, TIM_CHANNEL_4);
#elif defined (GREEN_TANK)
	init_motor(&motor_4, DIG_AIN_2_Pin, DIG_AIN_2_GPIO_Port, DIG_AIN_1_Pin, DIG_AIN_1_GPIO_Port, &htim2, TIM_CHANNEL_3);
	init_motor(&motor_2, DIG_BIN_1_Pin, DIG_BIN_1_GPIO_Port, DIG_BIN_2_Pin, DIG_BIN_2_GPIO_Port, &htim2, TIM_CHANNEL_4);
	init_motor(&motor_3, DIG_AIN_4_Pin, DIG_AIN_4_GPIO_Port, DIG_AIN_3_Pin, DIG_AIN_3_GPIO_Port, &htim3, TIM_CHANNEL_3);
	init_motor(&motor_1, DIG_BIN_3_Pin, DIG_BIN_3_GPIO_Port, DIG_BIN_4_Pin, DIG_BIN_4_GPIO_Port, &htim3, TIM_CHANNEL_4);
#endif
}

/**
* @brief Setting direction and pwm for one of the motors 
* @param mt: pointer to motor structure
* @param dr: motor direction - either 0 or 1
* @param pulse: PWM value - from 0 to PWM_MAX
* @retval None
*/
static void set_motor_dir_pwm(motor_pins_s *mt, uint8_t dr, uint16_t pulse) {
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

/**
* @brief Interracting with certain motor
* @param motor_num: number of the ceratin motor - from 1 to 4
* @param dir: direction for the motor: either 0 or 1
* @param pwm: output pwm value: from 0 to PWM_MAX
* @retval None
*/
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

/**
* @brief Stopping the motor
* @param motor_num: number of the ceratin motor - from 1 to 4
* @retval None
*/
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

/**
* @brief Stopping all the motors
* @retval None
*/
void stop_all_motors(void) {
	set_motor_dir_pwm(&motor_1, 2, 0);
	set_motor_dir_pwm(&motor_2, 2, 0);
	set_motor_dir_pwm(&motor_3, 2, 0);
	set_motor_dir_pwm(&motor_4, 2, 0);
}
