#include "application.h"
#include "stm32l1xx_hal.h"
#include "uart_driver.h"
#include "usbd_cdc_if.h"
#include "sdlog_info.h"
#include "file_manager.h"

sdlog_info_t info;
debug_mode_t debug_mode = DEBUG_MODE_NONE;
app_state_t state = APP_STATE_START;
void application_run(void){
  while(1){
    switch (state) {
      case APP_STATE_START:
        CDC_Transmit_FS((uint8_t*)"Reset\n",6);
        pwr_enable(PWR_BUZZER);
        HAL_Delay(100);
        pwr_disable(PWR_BUZZER);
        state = APP_STATE_MODEM_INIT;
        break;
      case APP_STATE_MODEM_INIT:
        pwr_enable(PWR_MODEM);
        if(modem_init()){
          state = APP_STATE_CONNECT;
        }
        else {
          state = APP_STATE_SLEEP;
        }
        break;
      case APP_STATE_CONNECT:
        config_read();
        //pwr_disable(PWR_MODEM);
        while (1)
          ;
        break;
      case APP_STATE_SLEEP:
        //pwr_disable(PWR_MODEM);
        while (1)
          ;
        break;
    }
  }
}
void application_init(void){
  uart_init(UART_MODEM,UART_BAUD_9600,UART_WORDLEN_8,UART_PAR_NONE,UART_STOP_1);
  pwr_buzzer_init(PWR_BUZZER);
}
