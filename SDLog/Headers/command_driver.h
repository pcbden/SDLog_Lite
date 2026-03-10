#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef enum {
  COMMAND_TYPE_SINGLE,
  COMMAND_TYPE_STORE,
  COMMAND_TYPE_SINGLE_UNTIL,
  COMMAND_TYPE_REPEATED,
  COMMAND_TYPE_STORED,
}command_type_t;

typedef enum {
  COMMAND_RESULT_OK,
  COMMAND_RESULT_ERROR,
  COMMAND_RESULT_TIMEOUT,
}command_result_t;

typedef struct {
  const char* at_string;
  const char* response_string;
  command_type_t type;
  uint16_t timeout_ms;
  uint16_t post_delay_ms;
  uint16_t count;
  const char* prefix;
  const char* suffix;
  char* store;
  int pass;
}command_t;

extern uint8_t urc_data[1024];
extern bool urc_flag;
extern bool response_flag;
command_result_t command_execute(command_t command);
void command_result_process(command_t command);
command_result_t command_execute(command_t command);
bool command_extract(char* buf, const char* prefix, const char* suffix, char* store, int pass, int max);
