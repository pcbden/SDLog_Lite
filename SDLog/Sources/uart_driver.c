#include <string.h>
#include "uart_driver.h"
#include "gpio_driver.h"
#include "sdlog_info.h"
#include "usbd_cdc_if.h"

extern void Error_Handler(void);
uint8_t uart_modem_rx_buffer[UART_BUFFER_SIZE + 1];
uint8_t uart_sensor_rx_buffer[UART_BUFFER_SIZE + 1];
uint8_t uart_aux_rx_buffer[UART_BUFFER_SIZE + 1];

bool uart_modem_rx_flag; 
bool uart_sensor_rx_flag; 
bool uart_aux_rx_flag; 

uint16_t uart_modem_rx_size;
uint16_t uart_sensor_rx_size;
uint16_t uart_aux_rx_size;

void uart_init(uart_port_t uart, uart_baud_t baud, uart_worldlen_t wordlen, uart_parity_t parity, uart_stopbits_t stopbits){
  uint32_t my_baud = 9600;
  uint32_t my_wordlen = UART_WORDLENGTH_8B;
  uint32_t my_parity = UART_PARITY_NONE;
  uint32_t my_stopbits = UART_STOPBITS_1;
  switch (baud) {
    case UART_BAUD_9600:
      my_baud = 9600;
      break;

    case UART_BAUD_19200:
      my_baud = 19200;
      break;

    case UART_BAUD_38400:
      my_baud = 38400;
      break;

    case UART_BAUD_57600:
      my_baud = 57600;
      break;

    case UART_BAUD_115200:
      my_baud = 115200;
      break;
  }
  switch (wordlen) {
    case UART_WORDLEN_8:
      my_wordlen = UART_WORDLENGTH_8B;
      break;
  
    case UART_WORDLEN_9:
      my_wordlen = UART_WORDLENGTH_9B;
      break;
  }
  switch (parity) {
    case UART_PAR_EVEN:
      my_parity = UART_PARITY_EVEN;
      break;

    case UART_PAR_ODD:
      my_parity = UART_PARITY_ODD;
      break;

    case UART_PAR_NONE:
      my_parity = UART_PARITY_NONE;
      break;
  }
  switch (stopbits) {
    case UART_STOP_1:
      my_stopbits = UART_STOPBITS_1;
      break;
  
    case UART_STOP_2:
      my_stopbits = UART_STOPBITS_2;
      break;
  }

  if(uart == UART_MODEM){
    huart1.Init.BaudRate = my_baud;
    huart1.Init.WordLength = my_wordlen;
    huart1.Init.Parity = my_parity;
    huart1.Init.StopBits = my_stopbits;
    if(HAL_UART_Init(&huart1) != HAL_OK){
      Error_Handler();
    }
  }
  if(uart == UART_SENSOR){
    huart2.Init.BaudRate = my_baud;
    huart2.Init.WordLength = my_wordlen;
    huart2.Init.Parity = my_parity;
    huart2.Init.StopBits = my_stopbits;
    if(HAL_UART_Init(&huart2) != HAL_OK){
      Error_Handler();
    }
  }
  if(uart == UART_AUX){
    huart3.Init.BaudRate = my_baud;
    huart3.Init.WordLength = my_wordlen;
    huart3.Init.Parity = my_parity;
    huart3.Init.StopBits = my_stopbits;
    if(HAL_UART_Init(&huart3) != HAL_OK){
      Error_Handler();
    }
  }
  uart_start_receive(uart);
}
void uart_send_str(uart_port_t uart, const char* str){
  uint16_t len = strlen(str);
  volatile HAL_StatusTypeDef res = HAL_ERROR;
  UNUSED(res);
  if(uart == UART_MODEM){
    res = HAL_UART_Transmit(&huart1,(uint8_t*)str,len,UART_TRANSMIT_TIMEOUT_MS);
    __NOP();
  }
  if(uart == UART_SENSOR){
    gpio_set(UART_RS485_RE_Port,UART_RS485_RE_Pin,GPIO_STATE_HIGH);
    HAL_Delay(UART_RS485_ASSERT_MS);
    HAL_UART_Transmit(&huart2,(uint8_t*)str,len,UART_TRANSMIT_TIMEOUT_MS);
    HAL_Delay(UART_RS485_DEASSERT_MS);
    gpio_set(UART_RS485_RE_Port,UART_RS485_RE_Pin,GPIO_STATE_LOW);
  }
  if(uart == UART_AUX){
    res = HAL_UART_Transmit(&huart3,(uint8_t*)str,len,UART_TRANSMIT_TIMEOUT_MS);
    __NOP();
  }
}
void uart_send_raw(uart_port_t uart, const uint8_t* data, uint16_t len){
  if(uart == UART_MODEM){
    HAL_UART_Transmit(&huart1,data,len,UART_TRANSMIT_TIMEOUT_MS);
  }
  if(uart == UART_SENSOR){
    gpio_set(UART_RS485_RE_Port,UART_RS485_RE_Pin,GPIO_STATE_HIGH);
    HAL_Delay(UART_RS485_ASSERT_MS);
    HAL_UART_Transmit(&huart2,data,len,UART_TRANSMIT_TIMEOUT_MS);
    HAL_Delay(UART_RS485_DEASSERT_MS);
    gpio_set(UART_RS485_RE_Port,UART_RS485_RE_Pin,GPIO_STATE_LOW);
  }
  if(uart == UART_AUX){
    HAL_UART_Transmit(&huart3,data,len,UART_TRANSMIT_TIMEOUT_MS);
  }
}
void uart_start_receive(uart_port_t uart){
  if(uart == UART_MODEM){
    HAL_UARTEx_ReceiveToIdle_DMA(&huart1,uart_modem_rx_buffer,UART_BUFFER_SIZE);
  }
  if(uart == UART_SENSOR){
    HAL_UARTEx_ReceiveToIdle_DMA(&huart2,uart_sensor_rx_buffer,UART_BUFFER_SIZE);
  }
  if(uart == UART_AUX){
    HAL_UARTEx_ReceiveToIdle_DMA(&huart3,uart_aux_rx_buffer,UART_BUFFER_SIZE);
  }
}
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size){
  __NOP();
  if(huart->Instance == USART1){
    if(debug_mode == DEBUG_MODE_NONE){
      if(Size < UART_MODEM_MAX_RX_SIZE){
        uart_modem_rx_size = Size;
        uart_modem_rx_flag = true;
        uart_modem_rx_buffer[Size] = '\0';
      }
    }
    if(debug_mode == DEBUG_MODE_UART1){
      CDC_Transmit_FS(uart_modem_rx_buffer,Size);
      uart_start_receive(UART_MODEM);
    }
  }
  if(huart->Instance == USART2){
    if(Size < UART_SENSOR_MAX_RX_SIZE){
      uart_sensor_rx_size = Size;
      uart_sensor_rx_flag = true;
      uart_sensor_rx_buffer[Size] = '\0';
    }
  }
  if(huart->Instance == USART3){
    if(Size < UART_AUX_MAX_RX_SIZE){
      uart_aux_rx_size = Size;
      uart_aux_rx_flag = true;
      uart_aux_rx_buffer[Size] = '\0';
    }
  }
}
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart){
  HAL_UART_AbortReceive(huart);
  if(huart->Instance == USART1){
    uart_start_receive(UART_MODEM);
  }
  if(huart->Instance == USART2){
    uart_start_receive(UART_SENSOR);
  }
  if(huart->Instance == USART3){
    uart_start_receive(UART_AUX);
  }
}
