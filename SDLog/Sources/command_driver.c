#include "command_driver.h"
#include "uart_driver.h"
#include <string.h>
#include "usbd_cdc_if.h"
#include "pwr_manager.h"
#include "sdlog_info.h"

uint8_t urc_buffer[1024];
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
        command_result_process(command);
        res = (response_flag == true) ? COMMAND_RESULT_OK : COMMAND_RESULT_ERROR;
        response_flag = false;
        uart_start_receive(UART_MODEM);
        break;
      }
    }
    uart_start_receive(UART_MODEM);
  }
  if(command.type == COMMAND_TYPE_SINGLE_UNTIL){
    uart_send_str(UART_MODEM,command.at_string);
    res = COMMAND_RESULT_TIMEOUT;
    while((HAL_GetTick() - start) < command.timeout_ms){
      if(uart_modem_rx_flag){
        uart_modem_rx_flag = false;
        command_result_process(command);
        if(response_flag){
          res = (response_flag == true) ? COMMAND_RESULT_OK : COMMAND_RESULT_ERROR;
          response_flag = false;
          uart_start_receive(UART_MODEM);
          break;
        }
        ///////////////////////
        if(urc_flag){
          CDC_Transmit_FS(urc_buffer,uart_modem_rx_size);
          urc_flag = false;
        }
        ///////////////////////
        uart_start_receive(UART_MODEM);
      }
    }
    uart_start_receive(UART_MODEM);
  }
  if(command.type == COMMAND_TYPE_STORE){
    uart_send_str(UART_MODEM,command.at_string);
    res = COMMAND_RESULT_TIMEOUT;
    while((HAL_GetTick() - start) < command.timeout_ms){
      if(uart_modem_rx_flag){
        uart_modem_rx_flag = false;
        command_result_process(command);
        if(response_flag){
          response_flag = false;
          if(command_extract((char*)uart_modem_rx_buffer,command.prefix,command.suffix,command.store,command.pass,INFO_PARAM_MAX_LEN)){
            res = COMMAND_RESULT_OK;
            break;
          }
        }
        uart_start_receive(UART_MODEM);
      }
    }
    uart_start_receive(UART_MODEM);
  }
  if(command.type == COMMAND_TYPE_REPEATED){
    int i = 0;
    command_t new_command = command;
    new_command.type = COMMAND_TYPE_SINGLE;
    res = COMMAND_RESULT_TIMEOUT;
    while(i < new_command.count){
      if(command_execute(new_command) == COMMAND_RESULT_OK){
        res = COMMAND_RESULT_OK;
        break;
      }
      i ++;
    }
  }
  HAL_Delay(command.post_delay_ms);
  return res;
}
bool command_extract(char* buf, const char* prefix, const char* suffix, char* store, int pass, int max){
  const char* start_str = strstr(buf, prefix);
  while(pass > 0){
    if(start_str == NULL) return false;
    buf += (start_str - buf) + strlen(prefix);
    start_str = strstr(buf, prefix);
    pass--;
  }
  if(start_str == NULL) return false;
  start_str += strlen(prefix);
  const char* finish = (*suffix == '\0') ? start_str + strlen(start_str) : strstr(start_str, suffix);
  if(finish == NULL) return false;
  int len = finish - start_str;
  if(len > max - 1) return false;
  memcpy(store, start_str, len);
  store[len] = '\0';
  return true;
}
void command_result_process(command_t command){
  if(strstr((char*)uart_modem_rx_buffer,command.response_string) != NULL){
    response_flag  = true;
  }
  else{
    memcpy(urc_buffer,uart_modem_rx_buffer,uart_modem_rx_size);
    urc_flag  = true;
    __NOP();
  }
}
