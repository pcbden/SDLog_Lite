#include "modbus_master.h"
#include "uart_driver.h"
#include <string.h>

uint16_t crc16(uint8_t* buffer, uint16_t len){
  uint16_t crc = 0xFFFF;
  while(len--){
    crc ^= *buffer++;
    for(int i = 0; i < 8; i++){
      if(crc & 0x0001){
        crc = (crc >> 1) ^ 0xA001;
      }
      else{
        crc >>= 1;
      }
    }
  }
  return crc;
}
modbus_result_t modbus_execute(modbus_command_t* command){
  uint32_t start = HAL_GetTick();
  uint16_t my_crc;
  modbus_result_t res = MODBUS_RESULT_TIMEOUT;
  if(command->type == MODBUS_TYPE_HEX){
    my_crc = crc16(command->modbus_command,command->modbus_command_len);
    command->modbus_command[command->modbus_command_len] = (uint8_t)my_crc;
    command->modbus_command[command->modbus_command_len + 1] = (uint8_t)(my_crc >> 8);
    uart_send_raw(UART_SENSOR,command->modbus_command,command->modbus_command_len + 2);
    while((HAL_GetTick() - start) < command->timeout_ms){
      if(uart_sensor_rx_flag){
        uart_sensor_rx_flag = false;
        my_crc = (uart_sensor_rx_buffer[uart_sensor_rx_size - 1] << 8) + uart_sensor_rx_buffer[uart_sensor_rx_size-2];
        if(my_crc == crc16(uart_sensor_rx_buffer,uart_sensor_rx_size - 2)){
          memcpy(command->modbus_data,uart_sensor_rx_buffer,uart_sensor_rx_size);
          res =  MODBUS_RESULT_OK;
        }
        else{
          res = MODBUS_RESULT_CRC_ERROR;
        }
        uart_start_receive(UART_SENSOR);
        break;
      }
    }
    uart_start_receive(UART_SENSOR);
  }
  return res;
}
