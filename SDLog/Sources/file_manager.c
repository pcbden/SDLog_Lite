#include "file_manager.h"
#include "at_commands.h"
#include "at_command_driver.h"
#include "uart_driver.h"
#include <string.h>

uint8_t file_buffer[UART_BUFFER_SIZE + 1];
bool config_read(void){
  char temp_array[256] = {[0 ... 255] = 0};
  if(command_execute(AT_FSDRIVE) == COMMAND_RESULT_OK){
    if(command_execute(AT_FSREAD) == COMMAND_RESULT_OK){
      memcpy(file_buffer,uart_modem_rx_buffer,uart_modem_rx_size);
      command_extract((char*)file_buffer,"UPNUM=","#",info.upnum,0,32);
      if(command_extract((char*)file_buffer,"SENSOR=","#",temp_array,0,32)){
        command_extract(temp_array,NULL,",",info.sensor_sensor_type,0,32);
        command_extract(temp_array,",",",",info.sensor_seth_mm,0,32);
        command_extract(temp_array,",",NULL,info.sensor_cor_sm,1,32);
      }
      if(command_extract((char*)file_buffer,"DAQ=","#",temp_array,0,256)){
        command_extract(temp_array,NULL,",",info.daq_min_distance_mm,0,32);
        command_extract(temp_array,",",",",info.daq_send_period_s,0,32);
        command_extract(temp_array,",",",",info.daq_min_measure_count,1,32);
        command_extract(temp_array,",",NULL,info.daq_measure_period_s,2,32);
      }
      if(command_extract((char*)file_buffer,"APN=","#",temp_array,0,256)){
        command_extract(temp_array,NULL,",",info.apn_con_type,0,32);
        command_extract(temp_array,",",",",info.apn_name,0,32);
        command_extract(temp_array,",",",",info.apn_user_name,1,32);
        command_extract(temp_array,",",",",info.apn_password,2,32);
        command_extract(temp_array,",",",",info.apn_phone_num,3,32);
        command_extract(temp_array,",",NULL,info.apn_rate,4,32);
      }
      if(command_extract((char*)file_buffer,"MQTT=","#",temp_array,0,256)){
        command_extract(temp_array,NULL,",",info.mqtt_ip,0,32);
        command_extract(temp_array,",",",",info.mqtt_port,0,32);
        command_extract(temp_array,",",",",info.mqtt_user_name,1,32);
        command_extract(temp_array,",",",",info.mqtt_password,2,32);
        command_extract(temp_array,",",",",info.mqtt_qos,3,32);
        command_extract(temp_array,",",",",info.mqtt_clean_session,4,32);
        command_extract(temp_array,",",",",info.mqtt_keep_alive,5,32);
        command_extract(temp_array,",",",",info.mqtt_timeout,6,32);
        command_extract(temp_array,",",",",info.mqtt_topics1,7,32);
        command_extract(temp_array,",",NULL,info.mqtt_topics2,8,32);
      }
      if(command_extract((char*)file_buffer,"FTP=","#",temp_array,0,256)){
        command_extract(temp_array,NULL,",",info.ftp_ip,0,32);
        command_extract(temp_array,",",",",info.ftp_port,0,32);
        command_extract(temp_array,",",",",info.ftp_username,1,32);
        command_extract(temp_array,",",",",info.ftp_password,2,32);
        command_extract(temp_array,",",",",info.ftp_interval,3,32);
        command_extract(temp_array,",",",",info.ftp_topics1,4,32);
        command_extract(temp_array,",",NULL,info.ftp_topics2,5,32);
      }
      command_extract((char*)file_buffer,"NAME1=","#",info.name1,0,32);
      command_extract((char*)file_buffer,"NAME2=","#",info.name2,0,32);
      command_extract((char*)file_buffer,"NAME3=","#",info.name3,0,32);
      return true;
    }
  }
  return false;
}
