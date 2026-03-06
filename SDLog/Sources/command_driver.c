#include "command_driver.h"
#include "uart_driver.h"
#include <string.h>

uint8_t urc_data[1024];
bool urc_flag;
bool response_flag;
command_result_t command_execute(command_t command){
  uint32_t start = HAL_GetTick();
  command_result_t res = COMMAND_RESULT_ERROR;
  if(command.type == COMMAND_TYPE_SINGLE){
    uart_send_str(UART_MODEM,command.at_string);
    res = COMMAND_RESULT_TIMEOUT;
    while((HAL_GetTick() - start) < command.timeout_ms){
      if(uart_modem_rx_flag){
        uart_modem_rx_flag = false;
        command_result_process();
        uart_start_receive(UART_MODEM);
        if(response_flag){
          response_flag = false;
          if(strstr((char*)uart_modem_rx_buffer,command.response_string) != NULL){
            res = COMMAND_RESULT_OK;
            break;
          }
          else {
            res = COMMAND_RESULT_ERROR;
            break;
          }
        }
      }
    }
  }
  return res;
}
void command_result_process(void){
  if(strstr((char*)uart_modem_rx_buffer,"+URC") != NULL){
    memcpy(urc_data,uart_modem_rx_buffer,uart_modem_rx_size);
    urc_flag = true;
  }
  else{
    response_flag  = true;
  }
}
