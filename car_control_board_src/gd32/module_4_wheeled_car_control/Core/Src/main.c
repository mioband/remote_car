/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "car_motors_control.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define TEST_DIR 1
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */
uint8_t test_buf[2];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM3_Init(void);
static void MX_USART3_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void encoders_reading(GPIO_TypeDef *prt_1, uint16_t pin_1, GPIO_TypeDef *prt_2, uint16_t pin_2) {
	if (HAL_GPIO_ReadPin(prt_1, pin_1)) {
		HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, 1);
	} else {
		HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, 0);
	}

	if (HAL_GPIO_ReadPin(prt_2, pin_2)) {
		HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, 1);
	} else {
		HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, 0);
	}
}


void test_motor(uint8_t dc_num, uint32_t testing_time,  uint8_t test_direction) {
	switch (dc_num) {
		case 1:
		case 2:
		case 3:
		case 4:
			move_motor(dc_num, test_direction, 100);
			break;
		default:
			stop_all_motors();
			break;
	}

	if (testing_time < HAL_MAX_DELAY) testing_time += (uint32_t)(uwTickFreq);
	uint32_t tickstart = HAL_GetTick();

	while ((HAL_GetTick() - tickstart) < testing_time) {
		switch (dc_num) {
			case 1:
				encoders_reading(ENC_1_GPIO_Port, ENC_1_Pin, ENC_2_GPIO_Port, ENC_2_Pin);
				break;
			case 2:
				encoders_reading(ENC_3_GPIO_Port, ENC_3_Pin, ENC_4_GPIO_Port, ENC_4_Pin);
				break;
			case 3:
				encoders_reading(ENC_5_GPIO_Port, ENC_5_Pin, ENC_6_GPIO_Port, ENC_6_Pin);
				break;
			case 4:
				encoders_reading(ENC_7_GPIO_Port, ENC_7_Pin, ENC_8_GPIO_Port, ENC_8_Pin);
				break;
		}
	}
}


void test_motors_and_encoders(void) {
	test_motor(1, 5000, 0);
	stop_motor(1);
	HAL_Delay(500);
	test_motor(1, 5000, 1);
	stop_motor(1);
	HAL_Delay(500);

	test_motor(2, 5000, 0);
	stop_motor(2);
	HAL_Delay(500);
	test_motor(2, 5000, 1);
	stop_motor(2);
	HAL_Delay(500);

	test_motor(3, 5000, 0);
	stop_motor(3);
	HAL_Delay(500);
	test_motor(3, 5000, 1);
	stop_motor(3);
	HAL_Delay(500);

	test_motor(4, 5000, 0);
	stop_motor(4);
	HAL_Delay(500);
	test_motor(4, 5000, 1);
	stop_motor(4);
	HAL_Delay(500);
}


void d_out_test(void) {
	HAL_GPIO_WritePin(DIG_OUT_1_GPIO_Port, DIG_OUT_1_Pin, 1);
	HAL_GPIO_WritePin(DIG_OUT_2_GPIO_Port, DIG_OUT_2_Pin, 0);
	HAL_GPIO_WritePin(DIG_OUT_3_GPIO_Port, DIG_OUT_3_Pin, 0);
	HAL_GPIO_WritePin(DIG_OUT_4_GPIO_Port, DIG_OUT_4_Pin, 0);
	HAL_GPIO_WritePin(DIG_OUT_5_GPIO_Port, DIG_OUT_5_Pin, 0);
	HAL_Delay(5000);
	HAL_GPIO_WritePin(DIG_OUT_1_GPIO_Port, DIG_OUT_1_Pin, 0);
	HAL_GPIO_WritePin(DIG_OUT_2_GPIO_Port, DIG_OUT_2_Pin, 1);
	HAL_GPIO_WritePin(DIG_OUT_3_GPIO_Port, DIG_OUT_3_Pin, 0);
	HAL_GPIO_WritePin(DIG_OUT_4_GPIO_Port, DIG_OUT_4_Pin, 0);
	HAL_GPIO_WritePin(DIG_OUT_5_GPIO_Port, DIG_OUT_5_Pin, 0);
	HAL_Delay(5000);
	HAL_GPIO_WritePin(DIG_OUT_1_GPIO_Port, DIG_OUT_1_Pin, 0);
	HAL_GPIO_WritePin(DIG_OUT_2_GPIO_Port, DIG_OUT_2_Pin, 0);
	HAL_GPIO_WritePin(DIG_OUT_3_GPIO_Port, DIG_OUT_3_Pin, 1);
	HAL_GPIO_WritePin(DIG_OUT_4_GPIO_Port, DIG_OUT_4_Pin, 0);
	HAL_GPIO_WritePin(DIG_OUT_5_GPIO_Port, DIG_OUT_5_Pin, 0);
	HAL_Delay(5000);
	HAL_GPIO_WritePin(DIG_OUT_1_GPIO_Port, DIG_OUT_1_Pin, 0);
	HAL_GPIO_WritePin(DIG_OUT_2_GPIO_Port, DIG_OUT_2_Pin, 0);
	HAL_GPIO_WritePin(DIG_OUT_3_GPIO_Port, DIG_OUT_3_Pin, 0);
	HAL_GPIO_WritePin(DIG_OUT_4_GPIO_Port, DIG_OUT_4_Pin, 1);
	HAL_GPIO_WritePin(DIG_OUT_5_GPIO_Port, DIG_OUT_5_Pin, 0);
	HAL_Delay(5000);
	HAL_GPIO_WritePin(DIG_OUT_1_GPIO_Port, DIG_OUT_1_Pin, 0);
	HAL_GPIO_WritePin(DIG_OUT_2_GPIO_Port, DIG_OUT_2_Pin, 0);
	HAL_GPIO_WritePin(DIG_OUT_3_GPIO_Port, DIG_OUT_3_Pin, 0);
	HAL_GPIO_WritePin(DIG_OUT_4_GPIO_Port, DIG_OUT_4_Pin, 0);
	HAL_GPIO_WritePin(DIG_OUT_5_GPIO_Port, DIG_OUT_5_Pin, 1);
	HAL_Delay(5000);
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if (test_buf[0] == 'L') {
		switch (test_buf[1]) {
			case '0':
				HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, 1);
				HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, 0);
				break;
			case '1':
				HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, 0);
				HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, 1);
				break;
		}
	}

	HAL_UART_Receive_IT(&huart3, (uint8_t *) test_buf, sizeof(test_buf));
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
  init_motors();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
//  move_motor(1, 1, 900);
  HAL_UART_Receive_IT(&huart3, (uint8_t *) test_buf, sizeof(test_buf));
  while (1) {

//	  test_motors_and_encoders();
//	  d_out_test();
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 999;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 7;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 999;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, DIG_BIN_4_Pin|DIG_BIN_3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, DIG_AIN_2_Pin|DIG_AIN_1_Pin|DIG_BIN_1_Pin|DIG_BIN_2_Pin
                          |DIG_AIN_4_Pin|DIG_AIN_3_Pin|LED_2_Pin|LED_1_Pin
                          |DIG_OUT_5_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, DIG_OUT_4_Pin|DIG_OUT_3_Pin|DIG_OUT_2_Pin|DIG_OUT_1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : DIG_BIN_4_Pin DIG_BIN_3_Pin */
  GPIO_InitStruct.Pin = DIG_BIN_4_Pin|DIG_BIN_3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : DIG_AIN_2_Pin DIG_AIN_1_Pin DIG_BIN_1_Pin DIG_BIN_2_Pin
                           DIG_AIN_4_Pin DIG_AIN_3_Pin LED_2_Pin LED_1_Pin
                           DIG_OUT_5_Pin */
  GPIO_InitStruct.Pin = DIG_AIN_2_Pin|DIG_AIN_1_Pin|DIG_BIN_1_Pin|DIG_BIN_2_Pin
                          |DIG_AIN_4_Pin|DIG_AIN_3_Pin|LED_2_Pin|LED_1_Pin
                          |DIG_OUT_5_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : DIG_OUT_4_Pin DIG_OUT_3_Pin DIG_OUT_2_Pin DIG_OUT_1_Pin */
  GPIO_InitStruct.Pin = DIG_OUT_4_Pin|DIG_OUT_3_Pin|DIG_OUT_2_Pin|DIG_OUT_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : ENC_8_Pin ENC_7_Pin ENC_6_Pin */
  GPIO_InitStruct.Pin = ENC_8_Pin|ENC_7_Pin|ENC_6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : ENC_5_Pin ENC_4_Pin ENC_3_Pin ENC_2_Pin
                           ENC_1_Pin */
  GPIO_InitStruct.Pin = ENC_5_Pin|ENC_4_Pin|ENC_3_Pin|ENC_2_Pin
                          |ENC_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

