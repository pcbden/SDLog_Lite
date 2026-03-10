#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "commands.h"
typedef enum {
  MODEM_INIT_AT_CHECK,
  MODEM_INIT_AT_ERROR,
  MODEM_INIT_SIM_CHECK,
  MODEM_INIT_SIM_ERROR,
  MODEM_INIT_REG_CHECK,
  MODEM_INIT_REG_ERROR,
  MODEM_INIT_COLLECT_INFO,
  MODEM_INIT_END,
}modem_init_t;
bool modem_init(void);
