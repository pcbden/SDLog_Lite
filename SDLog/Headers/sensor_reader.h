#pragma once
#include "modbus_commands.h"
#include <stdbool.h>
typedef enum{
  SENSOR_TEST_ON,
  SENSOR_TEST_OFF,
}sensor_test_t;
extern bool sensor_read_usb_flag;
void sensor_read_all(sensor_test_t type);
