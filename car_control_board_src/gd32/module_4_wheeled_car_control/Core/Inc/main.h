/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define DIG_BIN_4_Pin GPIO_PIN_13
#define DIG_BIN_4_GPIO_Port GPIOC
#define DIG_BIN_3_Pin GPIO_PIN_14
#define DIG_BIN_3_GPIO_Port GPIOC
#define DIG_AIN_2_Pin GPIO_PIN_0
#define DIG_AIN_2_GPIO_Port GPIOA
#define DIG_AIN_1_Pin GPIO_PIN_1
#define DIG_AIN_1_GPIO_Port GPIOA
#define DIG_BIN_1_Pin GPIO_PIN_4
#define DIG_BIN_1_GPIO_Port GPIOA
#define DIG_BIN_2_Pin GPIO_PIN_5
#define DIG_BIN_2_GPIO_Port GPIOA
#define DIG_AIN_4_Pin GPIO_PIN_6
#define DIG_AIN_4_GPIO_Port GPIOA
#define DIG_AIN_3_Pin GPIO_PIN_7
#define DIG_AIN_3_GPIO_Port GPIOA
#define DIG_OUT_4_Pin GPIO_PIN_12
#define DIG_OUT_4_GPIO_Port GPIOB
#define DIG_OUT_3_Pin GPIO_PIN_13
#define DIG_OUT_3_GPIO_Port GPIOB
#define DIG_OUT_2_Pin GPIO_PIN_14
#define DIG_OUT_2_GPIO_Port GPIOB
#define DIG_OUT_1_Pin GPIO_PIN_15
#define DIG_OUT_1_GPIO_Port GPIOB
#define ENC_8_Pin GPIO_PIN_8
#define ENC_8_GPIO_Port GPIOA
#define ENC_7_Pin GPIO_PIN_9
#define ENC_7_GPIO_Port GPIOA
#define LED_2_Pin GPIO_PIN_10
#define LED_2_GPIO_Port GPIOA
#define LED_1_Pin GPIO_PIN_11
#define LED_1_GPIO_Port GPIOA
#define DIG_OUT_5_Pin GPIO_PIN_12
#define DIG_OUT_5_GPIO_Port GPIOA
#define ENC_6_Pin GPIO_PIN_15
#define ENC_6_GPIO_Port GPIOA
#define ENC_5_Pin GPIO_PIN_3
#define ENC_5_GPIO_Port GPIOB
#define ENC_4_Pin GPIO_PIN_4
#define ENC_4_GPIO_Port GPIOB
#define ENC_3_Pin GPIO_PIN_5
#define ENC_3_GPIO_Port GPIOB
#define ENC_2_Pin GPIO_PIN_6
#define ENC_2_GPIO_Port GPIOB
#define ENC_1_Pin GPIO_PIN_7
#define ENC_1_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
