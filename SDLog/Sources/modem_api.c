#include "modem_api.h"


bool modem_init(void){
  modem_init_t state = MODEM_INIT_AT_CHECK;
  bool res = false;
  while(state != MODEM_INIT_END){
    switch (state) {
      case MODEM_INIT_AT_CHECK:
        state = (command_execute(AT) == COMMAND_RESULT_OK) ? MODEM_INIT_SIM_CHECK : MODEM_INIT_AT_ERROR;
        break;
      case MODEM_INIT_SIM_CHECK:
        state = (command_execute(AT_CPIN) == COMMAND_RESULT_OK) ? MODEM_INIT_REG_CHECK : MODEM_INIT_SIM_ERROR;
        break;
      case MODEM_INIT_REG_CHECK:
        if(command_execute(AT_CREG_CHECK) == COMMAND_RESULT_OK){
          state = (command_execute(AT_CREG) == COMMAND_RESULT_OK) ? MODEM_INIT_COLLECT_INFO : MODEM_INIT_END;
        }
        else{
          state = MODEM_INIT_COLLECT_INFO;
        }
        break;
      case MODEM_INIT_COLLECT_INFO:
        if(command_execute(AT_COPS) != COMMAND_RESULT_OK){
          //error log
        }
        if(command_execute(AT_GSN) != COMMAND_RESULT_OK){
          //error log
        }
        if(command_execute(AT_CSQ) != COMMAND_RESULT_OK){
          //error log
        }
        if(command_execute(AT_CBC) != COMMAND_RESULT_OK){
          //error log
        }
        if(command_execute(AT_CCID) != COMMAND_RESULT_OK){
          //error log
        }
        if(command_execute(AT_CNUM) != COMMAND_RESULT_OK){
          state = MODEM_INIT_REG_ERROR;
        }
        state = MODEM_INIT_END;


      case MODEM_INIT_AT_ERROR:
        state = MODEM_INIT_END;
        res = false;
        break;
      case MODEM_INIT_SIM_ERROR:
        state = MODEM_INIT_END;
        res = false;
        break;
      case MODEM_INIT_REG_ERROR:
        state = MODEM_INIT_END;
        res = false;
        break;
      case MODEM_INIT_END:
        res = false;
        break;
    }
  }
  res = true;
  return res;
}
