#include "modem_api.h"
#include "commands.h"


modem_init_t modem_init(void){
  if(command_execute(AT) != COMMAND_RESULT_OK){
    return MODEM_INIT_UNKNOWN;
  }
  if(command_execute(AT_CPIN) != COMMAND_RESULT_OK){
    return MODEM_INIT_NOSIM;
  }
  if(command_execute(AT_CREG_CHECK) == COMMAND_RESULT_OK){
    if(command_execute(AT_CREG) != COMMAND_RESULT_OK){
      return MODEM_INIT_NOPROVIDER;
    }
  }
  command_execute(AT_COPS);
  command_execute(AT_GSN);
  command_execute(AT_CSQ);
  command_execute(AT_CBC);
  command_execute(AT_CCID);
  command_execute(AT_CNUM);
  return MODEM_INIT_OK;
}
bool modem_internet_connect(void){
  if(command_execute(AT_CGATT_CHECK) != COMMAND_RESULT_OK){
    if(command_execute(AT_CGATT) != COMMAND_RESULT_OK){
      return false;
    }
  }
  command_execute(AT_SAPBR_CONTYPE);
  command_execute(AT_SAPBR_APN);
  command_execute(AT_SAPBR_USER);
  command_execute(AT_SAPBR_PWD);
  command_execute(AT_SAPBR_PHONENUM);
  command_execute(AT_SAPBR_RATE);
  if(command_execute(AT_SAPBR_CHECKIP) == COMMAND_RESULT_OK){
    if(command_execute(AT_SAPBR_OPEN) != COMMAND_RESULT_OK){
      return false;
    }
  }
  if(command_execute(AT_SAPBR_CHECKIP) == COMMAND_RESULT_OK){
    return false; 
  }
  return true;
}
void modem_ntp_update(void){
  command_execute(AT_CNTP_SERVER1);
  if(command_execute(AT_CNTP) != COMMAND_RESULT_OK){
    command_execute(AT_CNTP_SERVER2);
    command_execute(AT_CNTP);
  }
}
