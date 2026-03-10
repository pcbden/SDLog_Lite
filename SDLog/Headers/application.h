#pragma once
#include "modem_api.h"
#include "pwr_manager.h"
typedef enum {
  APP_STATE_START,
  APP_STATE_MODEM_INIT,
  APP_STATE_SLEEP,
  APP_STATE_CONNECT,
}app_state_t;
extern app_state_t state;
void application_run(void);
void application_init(void);
