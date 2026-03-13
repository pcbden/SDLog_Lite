#include "application.h"
#include "stm32l1xx_hal.h"
#include "uart_driver.h"
#include "usbd_cdc_if.h"
#include "sdlog_info.h"
#include "file_manager.h"
#include "usbd_cdc_if.h"
#include "sensor_reader.h"
extern USBD_HandleTypeDef hUsbDeviceFS;
sdlog_info_t info;
debug_mode_t debug_mode = DEBUG_MODE_NONE;
app_state_t state = APP_STATE_START;
void application_run(void){
  while(1){
    switch (state) {
      case APP_STATE_START:
        pwr_enable(PWR_BUZZER);
        HAL_Delay(100);
        pwr_disable(PWR_BUZZER);
        state = BOOT_APP_STATE_MODEM_INIT;
        if(hUsbDeviceFS.dev_state > USBD_STATE_DEFAULT){
          while(1){
            if(sensor_read_usb_flag){
              sensor_read_usb_flag = false;
              debug_mode = DEBUG_MODE_NONE;
              sensor_read_all(SENSOR_TEST_ON);
              debug_mode = DEBUG_MODE_UART2;
            }
          }
        }
        break;
      case BOOT_APP_STATE_MODEM_INIT:
        pwr_enable(PWR_MODEM);
        if(modem_init() == MODEM_INIT_OK){
          state = BOOT_APP_STATE_CONFIG;
        }
        else {
          state = APP_STATE_SLEEP;
        }
        break;
      case BOOT_APP_STATE_CONFIG:
        if(config_read() == true){
          state = BOOT_APP_STATE_CONNECT;
        }
        else{
          state = APP_STATE_SLEEP;
        }
        break;
      case BOOT_APP_STATE_CONNECT:
        if(modem_internet_connect() == true){
          state = BOOT_APP_STAT_NTP;
        }
        else{
          state = APP_STATE_SLEEP;
        }
        break;
      case BOOT_APP_STAT_NTP:
        modem_ntp_update();
        while(1)
          ;
        pwr_disable(PWR_MODEM);
        while(1)
          ;
        break;
      case APP_STATE_SLEEP:
        pwr_disable(PWR_MODEM);
        while (1)
          ;
        break;
    }
  }
}
void application_init(void){
  uart_init(UART_MODEM,UART_BAUD_9600,UART_WORDLEN_8,UART_PAR_NONE,UART_STOP_1);
  uart_init(UART_SENSOR,UART_BAUD_9600,UART_WORDLEN_8,UART_PAR_NONE,UART_STOP_1);
  pwr_buzzer_init(PWR_BUZZER);
}
