#pragma once
#include <stdint.h>
typedef enum{
  MODBUS_TYPE_ASCII,
  MODBUS_TYPE_HEX,
}modbus_type_t;

typedef enum {
  MODBUS_RESULT_OK,
  MODBUS_RESULT_TIMEOUT,
  MODBUS_RESULT_CRC_ERROR,
}modbus_result_t;

typedef enum {
  MODBUS_DATA_SIGNED,
  MODBUS_DATA_UNSIGNED,
  MODBUS_DATA_FLOAT,
  MODBUS_DATA_DOUBLE,
}modbus_data_type_t;

typedef enum {
  MODBUS_DATA_SIZE_16,
  MODBUS_DATA_SIZE_32,
  MODBUS_DATA_SIZE_64,
}modbus_data_size_t;

typedef enum {
  MODBUS_DATA_BIG_ENDIAN_ABCD,
  MODBUS_DATA_LITTLE_ENDIAN_DCAB,
  MODBUS_DATA_BIG_ENDIAN_BYTE_SWAP_CDAB,
  MODBUS_DATA_LITTLE_ENDIAN_BYTE_SWAP_BADC,
}modbus_data_byte_order_t;

typedef struct {
  const char* modbus_description;
  const char* modbus_string;
  uint8_t modbus_command[16];
  uint8_t modbus_data[16];
  modbus_type_t type;
  uint16_t modbus_command_len;
  modbus_data_type_t data_type;
  modbus_data_size_t data_size;
  modbus_data_byte_order_t data_byte_order;
  int presion;
  char* store_pointer;
  char* divide_power_of_10th;
  uint8_t modbus_result[32];
  uint32_t timeout_ms;
  uint32_t post_delay_ms;
}modbus_command_t;

modbus_result_t modbus_execute(modbus_command_t* command);
uint16_t crc16(uint8_t* buffer, uint16_t len);

