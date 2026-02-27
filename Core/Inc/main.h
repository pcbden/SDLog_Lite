/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "stm32l1xx_hal.h"

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
#define BUTTON_Pin GPIO_PIN_13
#define BUTTON_GPIO_Port GPIOC
#define L1_B_Pin GPIO_PIN_0
#define L1_B_GPIO_Port GPIOC
#define L1_G_Pin GPIO_PIN_1
#define L1_G_GPIO_Port GPIOC
#define L1_R_Pin GPIO_PIN_2
#define L1_R_GPIO_Port GPIOC
#define L2_B_Pin GPIO_PIN_3
#define L2_B_GPIO_Port GPIOC
#define RE_Pin GPIO_PIN_1
#define RE_GPIO_Port GPIOA
#define ON_5V_Pin GPIO_PIN_4
#define ON_5V_GPIO_Port GPIOA
#define L2_R_Pin GPIO_PIN_4
#define L2_R_GPIO_Port GPIOC
#define STATUS_Pin GPIO_PIN_1
#define STATUS_GPIO_Port GPIOB
#define EN_5V_Pin GPIO_PIN_9
#define EN_5V_GPIO_Port GPIOC
#define PWRS_Pin GPIO_PIN_10
#define PWRS_GPIO_Port GPIOC

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
