#pragma once
#include <stdbool.h>

typedef enum {
  MODEM_INIT_OK,
  MODEM_INIT_NOSIM,
  MODEM_INIT_NOPROVIDER,
  MODEM_INIT_UNKNOWN,
}modem_init_t;
modem_init_t modem_init(void);
bool modem_internet_connect(void);
void modem_ntp_update(void);
