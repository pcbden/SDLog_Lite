#include "sensor_reader.h"
#include "modbus_master.h"
#include "modbus_commands.h"
#include <stdio.h>
#include <string.h>
#include "stm32l1xx_hal.h"
#include "usbd_cdc_if.h"

bool reorder_bytes(modbus_data_byte_order_t byte_order, modbus_data_size_t size, uint8_t* bytes, int len, uint8_t* result){
  if(size == MODBUS_DATA_SIZE_16){
    if(len == 2){
      switch (byte_order) {
        case MODBUS_DATA_BIG_ENDIAN_ABCD:
          result[0] = bytes[0];
          result[1] = bytes[1];
          break;
        case MODBUS_DATA_LITTLE_ENDIAN_DCAB:
          result[0] = bytes[1];
          result[1] = bytes[0];
          break;
        case MODBUS_DATA_BIG_ENDIAN_BYTE_SWAP_CDAB:
          break;
        case MODBUS_DATA_LITTLE_ENDIAN_BYTE_SWAP_BADC:
          break;
      }
    }
    else{
      return false;
    }
  }
  if(size == MODBUS_DATA_SIZE_32){
    if(len == 4){
      switch (byte_order) {
        case MODBUS_DATA_BIG_ENDIAN_ABCD:
          result[0] = bytes[0];
          result[1] = bytes[1];
          result[2] = bytes[2];
          result[3] = bytes[3];
          break;
        case MODBUS_DATA_LITTLE_ENDIAN_DCAB:
          result[0] = bytes[3];
          result[1] = bytes[2];
          result[2] = bytes[1];
          result[3] = bytes[0];
          break;
        case MODBUS_DATA_BIG_ENDIAN_BYTE_SWAP_CDAB:
          result[0] = bytes[2];
          result[1] = bytes[3];
          result[2] = bytes[0];
          result[3] = bytes[1];
          break;
        case MODBUS_DATA_LITTLE_ENDIAN_BYTE_SWAP_BADC:
          result[0] = bytes[1];
          result[1] = bytes[0];
          result[2] = bytes[3];
          result[3] = bytes[2];
          break;
      }
    }
    else{
      return false;
    }
  }
  if(size == MODBUS_DATA_SIZE_64){
    if(len == 8){
      switch (byte_order) {
        case MODBUS_DATA_BIG_ENDIAN_ABCD:
          result[0] = bytes[0];
          result[1] = bytes[1];
          result[2] = bytes[2];
          result[3] = bytes[3];
          result[4] = bytes[4];
          result[5] = bytes[5];
          result[6] = bytes[6];
          result[7] = bytes[7];
          break;
        case MODBUS_DATA_LITTLE_ENDIAN_DCAB:
          result[0] = bytes[7];
          result[1] = bytes[6];
          result[2] = bytes[5];
          result[3] = bytes[4];
          result[4] = bytes[3];
          result[5] = bytes[2];
          result[6] = bytes[1];
          result[7] = bytes[0];
          break;
        case MODBUS_DATA_BIG_ENDIAN_BYTE_SWAP_CDAB:
          break;
        case MODBUS_DATA_LITTLE_ENDIAN_BYTE_SWAP_BADC:
          break;
      }
    }
    else{
      return false;
    }

  }
  return true;
}
bool format_data(uint8_t* data,modbus_data_size_t size, modbus_data_type_t type, int presion, uint8_t* result){
  int16_t int16;
  uint16_t uint16;
  int32_t int32;
  uint32_t uint32;
  int64_t int64;
  uint64_t uint64;
  float f;
  double d;
  if(size == MODBUS_DATA_SIZE_16){
    switch (type) {
      case MODBUS_DATA_SIGNED:
        int16 = (data[0] << 8) | data[1];
        snprintf((char*)result,INFO_PARAM_MAX_LEN,"%hd",int16);
        break;
      case MODBUS_DATA_UNSIGNED:
        uint16 = (data[0] << 8) | data[1];
        snprintf((char*)result,INFO_PARAM_MAX_LEN,"%hu",uint16);
        break;
      case MODBUS_DATA_FLOAT:
        return false;
        break;
      case MODBUS_DATA_DOUBLE:
        return false;
        break;
    }
  }
  if(size == MODBUS_DATA_SIZE_32){
    switch (type){
      case MODBUS_DATA_SIGNED:
        int32 = ((uint32_t)data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];
        snprintf((char*)result,INFO_PARAM_MAX_LEN,"%ld",int32);
        break;
      case MODBUS_DATA_UNSIGNED:
        uint32 = ((uint32_t)data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];
        snprintf((char*)result,INFO_PARAM_MAX_LEN,"%lu",uint32);
        break;
      case MODBUS_DATA_FLOAT:
        memcpy(&f,data,4);
        snprintf((char*)result,INFO_PARAM_MAX_LEN,"%.*f",presion,f);
        break;
      case MODBUS_DATA_DOUBLE:
        return false;
        break;
    }
  }
  if(size == MODBUS_DATA_SIZE_64){
    switch (type) {
      case MODBUS_DATA_SIGNED:
        int64 = ((uint64_t)data[0] << 56) | ((uint64_t)data[1] << 48) | ((uint64_t)data[2] << 40) | ((uint64_t)data[3] << 32) | 
          ((uint64_t)data[4] << 24) | (data[5] << 16) | (data[6] << 8) | data[7];
        snprintf((char*)result,INFO_PARAM_MAX_LEN,"%lld",int64);
        break;
      case MODBUS_DATA_UNSIGNED:
        uint64 = ((uint64_t)data[0] << 56) | ((uint64_t)data[1] << 48) | ((uint64_t)data[2] << 40) | ((uint64_t)data[3] << 32) | 
          ((uint64_t)data[4] << 24) | (data[5] << 16) | (data[6] << 8) | data[7];
        snprintf((char*)result,INFO_PARAM_MAX_LEN,"%llu",uint64);
        break;
      case MODBUS_DATA_DOUBLE:
        memcpy(&d,data,8);
        snprintf((char*)result,INFO_PARAM_MAX_LEN,"%.*f",presion,d);
        break;
      case MODBUS_DATA_FLOAT:
        return false;
        break;
    }
  }
  return true;
}
bool sensor_read(modbus_command_t command, sensor_test_t type){
  uint8_t temp_array[128];
  bool res = false;
  memcpy(command.store_pointer,command.modbus_result,INFO_PARAM_MAX_LEN);
  if(modbus_execute(command) == MODBUS_RESULT_OK){
    if(command.modbus_data[1] == 0x03){
      if(reorder_bytes(command.data_byte_order,command.data_size,&command.modbus_data[3],command.modbus_data[2],temp_array)){
        if(format_data(temp_array,command.data_size,command.data_type,command.presion,command.modbus_result)){
          memcpy(command.store_pointer,command.modbus_result,INFO_PARAM_MAX_LEN);
          res = true;
        }
      }
    }
  }
  else {
    //log here
  }
  if(type == SENSOR_TEST_ON){
    strncpy((char*)temp_array,command.modbus_description,INFO_PARAM_MAX_LEN);
    strncat((char*)temp_array,command.store_pointer,strlen(command.store_pointer));
    HAL_Delay(100);
    CDC_Transmit_FS(temp_array,strlen((char*)temp_array));
  }
  return res;
}
void sensor_read_all(sensor_test_t type){
  sensor_read(SENSOR_TEMPERATURE,type);
}
