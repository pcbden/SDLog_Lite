#pragma once
#include "modbus_master.h"
#include "sdlog_info.h"

static modbus_command_t __attribute__((unused)) SENSOR_CONDUCT = {
  .modbus_description = "Conductivity Value ",
  .modbus_command = {0x01,0x03,0x00,0x00,0x00,0x01},
  .modbus_command_len = 6,
  .type = MODBUS_TYPE_HEX,
  .data_type = MODBUS_DATA_UNSIGNED,
  .data_size = MODBUS_DATA_SIZE_16,
  .data_byte_order = MODBUS_DATA_BIG_ENDIAN_ABCD,
  .store_pointer = info.conductivity_value,
  .modbus_result = "-1",
  .timeout_ms = 1000,
  .post_delay_ms = 1000,
};
static modbus_command_t __attribute__((unused)) SENSOR_CONDUCT_DIV = {
  .modbus_description = "Conductivity Value2",
  .modbus_command = {0x01,0x03,0x00,0x01,0x00,0x01},
  .modbus_command_len = 6,
  .type = MODBUS_TYPE_HEX,
  .data_type = MODBUS_DATA_UNSIGNED,
  .data_size = MODBUS_DATA_SIZE_16,
  .data_byte_order = MODBUS_DATA_BIG_ENDIAN_ABCD,
  .store_pointer = info.conductivity_divide,
  .modbus_result = "-1",
  .timeout_ms = 1000,
  .post_delay_ms = 1000,
};
