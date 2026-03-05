#pragma once 

#include <stdint.h>
#include "stdbool.h"

#define MODEM_PWRS_TIMEOUT_MS 1500
#define BUZZER_TIMER_COMPARE 10

typedef enum {
  PWR_MODEM,
  PWR_BOOST,
  PWR_LED1_BLUE,
  PWR_LED1_GREEN,
  PWR_LED1_RED,
  PWR_LED2_BLUE,
  PWR_LED2_RED,
  PWR_BUZZER,
} pwr_component_t;

bool pwr_enable(pwr_component_t component);
bool pwr_disable(pwr_component_t component);
bool pwr_is_enabled(pwr_component_t component);
