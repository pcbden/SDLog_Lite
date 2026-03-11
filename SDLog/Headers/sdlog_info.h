#pragma once
#define INFO_PARAM_MAX_LEN 32
typedef enum {
  DEBUG_MODE_NONE,
  DEBUG_MODE_UART1,
  DEBUG_MODE_UART2,
}debug_mode_t;
typedef struct {
  char sensor_temperature[INFO_PARAM_MAX_LEN];
  char provider[INFO_PARAM_MAX_LEN];
  char imei[INFO_PARAM_MAX_LEN];
  char sig_quality_dbm[INFO_PARAM_MAX_LEN];
  char bat_level_p[INFO_PARAM_MAX_LEN];
  char ccid[INFO_PARAM_MAX_LEN];
  char cnum[INFO_PARAM_MAX_LEN];

  char upnum[INFO_PARAM_MAX_LEN];
  
  char sensor_sensor_type[INFO_PARAM_MAX_LEN];
  char sensor_seth_mm[INFO_PARAM_MAX_LEN];
  char sensor_cor_sm[INFO_PARAM_MAX_LEN];
  
  char apn_con_type[INFO_PARAM_MAX_LEN];
  char apn_name[INFO_PARAM_MAX_LEN];
  char apn_user_name[INFO_PARAM_MAX_LEN];
  char apn_password[INFO_PARAM_MAX_LEN];
  char apn_phone_num[INFO_PARAM_MAX_LEN];
  char apn_rate[INFO_PARAM_MAX_LEN];
  
  char daq_min_distance_mm[INFO_PARAM_MAX_LEN];
  char daq_send_period_s[INFO_PARAM_MAX_LEN];
  char daq_min_measure_count[INFO_PARAM_MAX_LEN];
  char daq_measure_period_s[INFO_PARAM_MAX_LEN];

  char mqtt_ip[INFO_PARAM_MAX_LEN];
  char mqtt_port[INFO_PARAM_MAX_LEN];
  char mqtt_user_name[INFO_PARAM_MAX_LEN];
  char mqtt_password[INFO_PARAM_MAX_LEN];
  char mqtt_qos[INFO_PARAM_MAX_LEN];
  char mqtt_clean_session[INFO_PARAM_MAX_LEN];
  char mqtt_keep_alive[INFO_PARAM_MAX_LEN];
  char mqtt_timeout[INFO_PARAM_MAX_LEN];
  char mqtt_topics1[INFO_PARAM_MAX_LEN];
  char mqtt_topics2[INFO_PARAM_MAX_LEN];

  char ftp_ip[INFO_PARAM_MAX_LEN];
  char ftp_port[INFO_PARAM_MAX_LEN];
  char ftp_username[INFO_PARAM_MAX_LEN];
  char ftp_password[INFO_PARAM_MAX_LEN];
  char ftp_interval[INFO_PARAM_MAX_LEN];
  char ftp_topics1[INFO_PARAM_MAX_LEN];
  char ftp_topics2[INFO_PARAM_MAX_LEN];

  char name1[INFO_PARAM_MAX_LEN];

  char name2[INFO_PARAM_MAX_LEN];

  char name3[INFO_PARAM_MAX_LEN];
}sdlog_info_t;
extern sdlog_info_t info;
extern debug_mode_t debug_mode;
