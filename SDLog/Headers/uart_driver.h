#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "usart.h"

#define UART_BUFFER_SIZE 1024

#define UART_MODEM_MAX_RX_SIZE 800
#define UART_SENSOR_MAX_RX_SIZE 256
#define UART_AUX_MAX_RX_SIZE 256

#define UART_TRANSMIT_TIMEOUT_MS 100
#define UART_RS485_ASSERT_MS 0
#define UART_RS485_DEASSERT_MS 10

typedef enum {
  UART_BAUD_9600,
  UART_BAUD_19200,
  UART_BAUD_38400,
  UART_BAUD_57600,
  UART_BAUD_115200,
}uart_baud_t;

typedef enum {
  UART_WORDLEN_8,
  UART_WORDLEN_9,
}uart_worldlen_t;

typedef enum {
  UART_PAR_NONE,
  UART_PAR_EVEN,
  UART_PAR_ODD,
}uart_parity_t;

typedef enum {
  UART_STOP_1,
  UART_STOP_2,
}uart_stopbits_t;

typedef enum {
  UART_MODEM,
  UART_SENSOR,
  UART_AUX,
}uart_port_t;

extern uint8_t uart_modem_rx_buffer[UART_BUFFER_SIZE + 1];
extern uint8_t uart_sensor_rx_buffer[UART_BUFFER_SIZE + 1];
extern uint8_t uart_aux_rx_buffer[UART_BUFFER_SIZE + 1];

extern bool uart_modem_rx_flag; 
extern bool uart_sensor_rx_flag; 
extern bool uart_aux_rx_flag; 

extern uint16_t uart_modem_rx_size;
extern uint16_t uart_sensor_rx_size;
extern uint16_t uart_aux_rx_size;

void uart_init(uart_port_t uart, uart_baud_t baud, uart_worldlen_t wordlen, uart_parity_t parity, uart_stopbits_t stopbits);
void uart_send_str(uart_port_t uart, const char* str);
void uart_send_raw(uart_port_t uart, const uint8_t* data, uint16_t len);
void uart_start_receive(uart_port_t uart);
