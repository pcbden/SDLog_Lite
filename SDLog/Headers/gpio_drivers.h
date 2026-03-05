#pragma once
#include <stdint.h>
#include "gpio_config.h"
typedef enum{
  GPIO_STATE_LOW,
  GPIO_STATE_HIGH,
} gpio_state_t;

void gpio_set(GPIO_TypeDef* port, uint16_t pin, gpio_state_t state);
gpio_state_t gpio_get(GPIO_TypeDef* port, uint16_t pin);
