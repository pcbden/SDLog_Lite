#pragma once
#include "modbus_master.h"
#include "sdlog_info.h"

static const modbus_command_t SENSOR_TEMPERATURE = {
  .modbus_description = "Temperature_degress ",
  .modbus_command = {0x01,0x03,0x00,0x00,0x00,0x01},
  .modbus_command_len = 6,
  .type = MODBUS_TYPE_HEX,
  .data_type = MODBUS_DATA_UNSIGNED,
  .data_size = MODBUS_DATA_SIZE_16,
  .data_byte_order = MODBUS_DATA_BIG_ENDIAN_ABCD,
  .store_pointer = info.sensor_temperature,
  .modbus_result = "-1",
  .timeout_ms = 1000,
  .post_delay_ms = 100,
};
