#pragma once
#include "modem_api.h"
#include "pwr_manager.h"
typedef enum {
  APP_STATE_START,
  APP_STATE_MODEM_INIT,
  BOOT_APP_STATE_MODEM_INIT,
  APP_STATE_SLEEP,
  BOOT_APP_STATE_CONFIG,
  APP_STATE_CONNECT,
  BOOT_APP_STATE_CONNECT,
  BOOT_APP_STAT_NTP,
  APP_STATE_CONNECT_MQTT,
}app_state_t;
extern app_state_t state;
void application_run(void);
void application_init(void);
