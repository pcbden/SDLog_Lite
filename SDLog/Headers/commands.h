#pragma once
#include "command_driver.h"
#include "sdlog_info.h"

static const command_t AT = {
  .at_string = "AT\r\n",
  .response_string = "OK\r\n",
  .type = COMMAND_TYPE_REPEATED,
  .timeout_ms = 1000,
  .count = 10,
};
