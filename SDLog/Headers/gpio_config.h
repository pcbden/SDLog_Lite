#pragma once

#include <stdint.h>
#include "stm32l1xx_hal.h"
#include "tim.h"

//pwrs pin of the modem. (On or Off pin)
//(MODEM ON)Set High until MODEM_STATUS_Pin goes high, then set low
//(MODEM OFF)Set High until MODEM_STATUS_Pin goes low, then set low
#define MODEM_PWRS_Pin GPIO_PIN_10
#define MODEM_PWRS_Port GPIOC

#define MODEM_STATUS_Pin GPIO_PIN_1
#define MODEM_STATUS_Port GPIOB

#define BUTTON_AND_BOOT_Pin GPIO_PIN_13
#define BUTTON_AND_BOOT_Port GPIOC

#define BOOST_PWR_ON_Pin GPIO_PIN_4
#define BOOST_PWR_ON_Port GPIOA

#define BOOST_PWR_ENABLE_Pin GPIO_PIN_8
#define BOOST_PWR_ENABLE_Port GPIOC

#define LED1_BLUE_Pin GPIO_PIN_0
#define LED1_BLUE_Port GPIOC

#define LED1_GREEN_Pin GPIO_PIN_1
#define LED1_GREEN_Port GPIOC

#define LED1_RED_Pin GPIO_PIN_2
#define LED1_RED_Port GPIOC

#define LED2_BLUE_Pin GPIO_PIN_3
#define LED2_BLUE_Port GPIOC

#define LED2_RED_Pin GPIO_PIN_4
#define LED2_RED_Port GPIOC

#define BUZZER_TIMER_HANDLE_Pointer &htim9
#define BUZZER_TIMER_CHANNEL TIM_CHANNEL_1

#define UART_RS485_RE_Pin GPIO_PIN_1
#define UART_RS485_RE_Port GPIOA
