/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_Pin GPIO_PIN_13
#define LED_GPIO_Port GPIOC
#define LEDRED_Pin GPIO_PIN_1
#define LEDRED_GPIO_Port GPIOA
#define SATR_1_OUT_Pin GPIO_PIN_4
#define SATR_1_OUT_GPIO_Port GPIOA
#define SATR_2_OUT_Pin GPIO_PIN_5
#define SATR_2_OUT_GPIO_Port GPIOA
#define SATR_3_OUT_Pin GPIO_PIN_6
#define SATR_3_OUT_GPIO_Port GPIOA
#define SATR_4_OUT_Pin GPIO_PIN_7
#define SATR_4_OUT_GPIO_Port GPIOA
#define SOTON_1_EX_Pin GPIO_PIN_0
#define SOTON_1_EX_GPIO_Port GPIOB
#define SOTON_1_EX_EXTI_IRQn EXTI0_IRQn
#define SOTON_2_EX_Pin GPIO_PIN_1
#define SOTON_2_EX_GPIO_Port GPIOB
#define SOTON_2_EX_EXTI_IRQn EXTI1_IRQn
#define SOTON_3_EX_Pin GPIO_PIN_12
#define SOTON_3_EX_GPIO_Port GPIOB
#define SOTON_3_EX_EXTI_IRQn EXTI15_10_IRQn
#define SOTON_4_EX_Pin GPIO_PIN_13
#define SOTON_4_EX_GPIO_Port GPIOB
#define SOTON_4_EX_EXTI_IRQn EXTI15_10_IRQn
#define KEY_RIGHT_EX_Pin GPIO_PIN_14
#define KEY_RIGHT_EX_GPIO_Port GPIOB
#define KEY_RIGHT_EX_EXTI_IRQn EXTI15_10_IRQn
#define KEY_LEFT_EX_Pin GPIO_PIN_15
#define KEY_LEFT_EX_GPIO_Port GPIOB
#define KEY_LEFT_EX_EXTI_IRQn EXTI15_10_IRQn
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
