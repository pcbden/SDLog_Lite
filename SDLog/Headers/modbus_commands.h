#pragma once
#include "modbus_master.h"
#include "sdlog_info.h"

static modbus_command_t __attribute__((unused)) SENSOR_ALL = {
  .modbus_description = "Update ALL ",
  .modbus_command = {0x01,0x03,0x00,0x00,0x00,0x06},
  .modbus_command_len = 6,
  .type = MODBUS_TYPE_HEX,
  .timeout_ms = 4000,
  .post_delay_ms = 100,
};
static modbus_command_t __attribute__((unused)) SENSOR_CONDUCT = {
  .modbus_description = "Conductivity Value (uS/sm) ",
  .modbus_command = {0x01,0x03,0x00,0x00,0x00,0x01},
  .modbus_command_len = 6,
  .type = MODBUS_TYPE_HEX,
  .data_type = MODBUS_DATA_UNSIGNED,
  .data_size = MODBUS_DATA_SIZE_16,
  .data_byte_order = MODBUS_DATA_BIG_ENDIAN_ABCD,
  .store_pointer = info.conductivity_value,
  .divide_power_of_10th = info.conductivity_divide,
  .modbus_result = "-1",
  .timeout_ms = 4000,
  .post_delay_ms = 100,
};
static modbus_command_t __attribute__((unused)) SENSOR_CONDUCT_DIV = {
  .modbus_description = "Conductivity DIV ",
  .modbus_command = {0x01,0x03,0x00,0x01,0x00,0x01},
  .modbus_command_len = 6,
  .type = MODBUS_TYPE_HEX,
  .data_type = MODBUS_DATA_UNSIGNED,
  .data_size = MODBUS_DATA_SIZE_16,
  .data_byte_order = MODBUS_DATA_BIG_ENDIAN_ABCD,
  .store_pointer = info.conductivity_divide,
  .modbus_result = "-1",
  .timeout_ms = 4000,
  .post_delay_ms = 100,
};
static modbus_command_t __attribute__((unused)) SENSOR_TEMP = {
  .modbus_description = "Temperature Value (°C) ",
  .modbus_command = {0x01,0x03,0x00,0x02,0x00,0x01},
  .modbus_command_len = 6,
  .type = MODBUS_TYPE_HEX,
  .data_type = MODBUS_DATA_UNSIGNED,
  .data_size = MODBUS_DATA_SIZE_16,
  .data_byte_order = MODBUS_DATA_BIG_ENDIAN_ABCD,
  .store_pointer = info.temperature_value,
  .divide_power_of_10th = info.temperature_divide,
  .modbus_result = "-1",
  .timeout_ms = 4000,
  .post_delay_ms = 100,
};
static modbus_command_t __attribute__((unused)) SENSOR_TEMP_DIV = {
  .modbus_description = "Temperature DIV ",
  .modbus_command = {0x01,0x03,0x00,0x03,0x00,0x01},
  .modbus_command_len = 6,
  .type = MODBUS_TYPE_HEX,
  .data_type = MODBUS_DATA_UNSIGNED,
  .data_size = MODBUS_DATA_SIZE_16,
  .data_byte_order = MODBUS_DATA_BIG_ENDIAN_ABCD,
  .store_pointer = info.temperature_divide,
  .modbus_result = "-1",
  .timeout_ms = 4000,
  .post_delay_ms = 100,
};
static modbus_command_t __attribute__((unused)) SENSOR_LEVEL = {
  .modbus_description = "Level Value (mm) ",
  .modbus_command = {0x01,0x03,0x00,0x04,0x00,0x01},
  .modbus_command_len = 6,
  .type = MODBUS_TYPE_HEX,
  .data_type = MODBUS_DATA_UNSIGNED,
  .data_size = MODBUS_DATA_SIZE_16,
  .data_byte_order = MODBUS_DATA_BIG_ENDIAN_ABCD,
  .store_pointer = info.level_value,
  .divide_power_of_10th = info.level_divide,
  .modbus_result = "-1",
  .timeout_ms = 4000,
  .post_delay_ms = 100,
};
static modbus_command_t __attribute__((unused)) SENSOR_LEVEL_DIV = {
  .modbus_description = "Level DIV ",
  .modbus_command = {0x01,0x03,0x00,0x05,0x00,0x01},
  .modbus_command_len = 6,
  .type = MODBUS_TYPE_HEX,
  .data_type = MODBUS_DATA_UNSIGNED,
  .data_size = MODBUS_DATA_SIZE_16,
  .data_byte_order = MODBUS_DATA_BIG_ENDIAN_ABCD,
  .store_pointer = info.level_value,
  .modbus_result = "-1",
  .timeout_ms = 4000,
  .post_delay_ms = 100,
};
