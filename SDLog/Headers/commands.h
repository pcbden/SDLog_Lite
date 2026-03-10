#pragma once
#include "command_driver.h"
#include "sdlog_info.h"

static const command_t AT = {
  .at_string = "ATE0\r\n",
  .response_string = "OK\r\n",
  .type = COMMAND_TYPE_REPEATED,
  .timeout_ms = 1000,
  .count = 10,
};
static const command_t AT_CPIN = {
  .at_string = "AT+CPIN?\r\n",
  .response_string = "+CPIN: READY",
  .type = COMMAND_TYPE_SINGLE_UNTIL,
  .timeout_ms = 5000,
};
static const command_t AT_CREG = {
  .at_string = "AT+CREG=1\r\n",
  .response_string = "+CREG:",
  .type = COMMAND_TYPE_SINGLE_UNTIL,
  .timeout_ms = 60000,
};
static const command_t AT_CREG_CHECK = {
  .at_string = "AT+CREG?\r\n",
  .response_string = ",2",
  .type = COMMAND_TYPE_SINGLE,
  .timeout_ms = 1000,
};
static const command_t AT_COPS = {
  .at_string = "AT+COPS?\r\n",
  .response_string = "+COPS:",
  .type = COMMAND_TYPE_STORE,
  .timeout_ms = 1000,
  .prefix = ",\"",
  .suffix = "\"",
  .store = info.provider,
  .pass = 0,
};
static const command_t AT_GSN = {
  .at_string = "AT+GSN\r\n",
  .response_string = "OK",
  .type = COMMAND_TYPE_STORE,
  .timeout_ms = 1000,
  .prefix = "\r\n",
  .suffix = "\r\n",
  .store = info.imei,
  .pass = 0,
};
static const command_t AT_CSQ = {
  .at_string = "AT+CSQ\r\n",
  .response_string = "OK",
  .type = COMMAND_TYPE_STORE,
  .timeout_ms = 1000,
  .prefix = "CSQ: ",
  .suffix = ",",
  .store = info.sig_quality_dbm,
  .pass = 0,
};
static const command_t AT_CBC = {
  .at_string = "AT+CBC\r\n",
  .response_string = "OK",
  .type = COMMAND_TYPE_STORE,
  .timeout_ms = 1000,
  .prefix = ",",
  .suffix = ",",
  .store = info.bat_level_p,
  .pass = 0,
};
static const command_t AT_CCID = {
  .at_string = "AT+CCID\r\n",
  .response_string = "OK",
  .type = COMMAND_TYPE_STORE,
  .timeout_ms = 1000,
  .prefix = "\r\n",
  .suffix = "\r\n",
  .store = info.ccid,
  .pass = 0,
};
static const command_t AT_CNUM = {
  .at_string = "AT+CNUM\r\n",
  .response_string = "OK",
  .type = COMMAND_TYPE_STORE,
  .timeout_ms = 100,
  .prefix = ",\"",
  .suffix = "\"",
  .store = info.cnum,
  .pass = 0,
};
static const command_t AT_FSDRIVE = {
  .at_string = "AT+FSDRIVE=0\r\n",
  .response_string = "+FSDRIVE: C",
  .type = COMMAND_TYPE_SINGLE,
  .timeout_ms = 1000,
};
static const command_t AT_FSREAD = {
  .at_string = "AT+FSREAD=C:\\USER\\BtReceived\\config.txt,0,1024,0\r\n",
  .response_string = "OK",
  .type = COMMAND_TYPE_SINGLE,
  .timeout_ms = 1000,
};
