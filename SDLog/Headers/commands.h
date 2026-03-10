#pragma once
#include "command_driver.h"
#include "sdlog_info.h"

static const command_t AT = {
  .at_string = "ATE1\r\n",
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
static const command_t AT_CGATT_CHECK = {
  .at_string = "AT+CGATT?\r\n",
  .response_string = "+CGATT: 1",
  .type = COMMAND_TYPE_REPEATED,
  .timeout_ms = 1000,
  .post_delay_ms = 1000,
  .count = 75,
};
static const command_t AT_CGATT = {
  .at_string = "AT+CGATT=1\r\n",
  .response_string = "OK",
  .type = COMMAND_TYPE_SINGLE_UNTIL,
  .timeout_ms = 75000,
};
static const command_t AT_SAPBR_CONTYPE = {
  .at_string = "AT+SAPBR=3,1,\"CONTYPE\",\"%s\"\r\n%s%s%s",
  .response_string = "OK",
  .type = COMMAND_TYPE_BUILD,
  .p = {info.apn_con_type,"","",""},
  .timeout_ms = 1000,
};
static const command_t AT_SAPBR_APN = {
  .at_string = "AT+SAPBR=3,1,\"APN\",\"%s\"\r\n%s%s%s",
  .response_string = "OK",
  .type = COMMAND_TYPE_BUILD,
  .p = {info.apn_name,"","",""},
  .timeout_ms = 1000,
};
static const command_t AT_SAPBR_USER = {
  .at_string = "AT+SAPBR=3,1,\"USER\",\"%s\"\r\n%s%s%s",
  .response_string = "OK",
  .type = COMMAND_TYPE_BUILD,
  .p = {info.apn_user_name,"","",""},
  .timeout_ms = 1000,
};
static const command_t AT_SAPBR_PWD = {
  .at_string = "AT+SAPBR=3,1,\"PWD\",\"%s\"\r\n%s%s%s",
  .response_string = "OK",
  .type = COMMAND_TYPE_BUILD,
  .p = {info.apn_password,"","",""},
  .timeout_ms = 1000,
};
static const command_t AT_SAPBR_PHONENUM = {
  .at_string = "AT+SAPBR=3,1,\"PHONENUM\",\"%s\"\r\n%s%s%s",
  .response_string = "OK",
  .type = COMMAND_TYPE_BUILD,
  .p = {info.apn_phone_num,"","",""},
  .timeout_ms = 1000,
};
static const command_t AT_SAPBR_RATE = {
  .at_string = "AT+SAPBR=3,1,\"RATE\",\"%s\"\r\n%s%s%s",
  .response_string = "OK",
  .type = COMMAND_TYPE_BUILD,
  .p = {info.apn_rate,"","",""},
  .timeout_ms = 1000,
};
static const command_t AT_SAPBR_OPEN = {
  .at_string = "AT+SAPBR=1,1\r\n",
  .response_string = "OK",
  .type = COMMAND_TYPE_SINGLE_UNTIL,
  .timeout_ms = 85000,
  .post_delay_ms = 1000,
};
static const command_t AT_SAPBR_CHECKIP = {
  .at_string = "AT+SAPBR=2,1\r\n",
  .response_string = "0.0.0.0",
  .type = COMMAND_TYPE_SINGLE,
  .timeout_ms = 1000,
};
static const command_t AT_CNTP_SERVER1 = {
  .at_string = "AT+CNTP=\"pool.ntp.org\",0\r\n",
  .response_string = "OK",
  .type = COMMAND_TYPE_SINGLE,
  .timeout_ms = 1000,
};
static const command_t AT_CNTP_SERVER2 = {
  .at_string = "AT+CNTP=\"time.google.com\",0\r\n",
  .response_string = "OK",
  .type = COMMAND_TYPE_SINGLE,
  .timeout_ms = 1000,
};
static const command_t AT_CNTP = {
  .at_string = "AT+CNTP\r\n",
  .response_string = "+CNTP: 1",
  .type = COMMAND_TYPE_SINGLE_UNTIL,
  .timeout_ms = 10000,
};
