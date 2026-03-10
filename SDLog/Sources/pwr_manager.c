#include "pwr_manager.h"
#include "gpio_driver.h"
#include "stm32l1xx_hal.h"
void pwr_buzzer_init(pwr_component_t component){
  HAL_TIM_PWM_Start(BUZZER_TIMER_HANDLE_Pointer,BUZZER_TIMER_CHANNEL);
}
bool pwr_enable(pwr_component_t component){
  if(component == PWR_MODEM){
    if(gpio_get(MODEM_STATUS_Port,MODEM_STATUS_Pin) == GPIO_STATE_HIGH){
      return true;
    }
    uint32_t start = HAL_GetTick();
    gpio_set(MODEM_PWRS_Port,MODEM_PWRS_Pin,GPIO_STATE_HIGH);
    while(gpio_get(MODEM_STATUS_Port,MODEM_STATUS_Pin) != GPIO_STATE_HIGH){
      if((HAL_GetTick() - start) > MODEM_PWRS_TIMEOUT_MS){
        gpio_set(MODEM_PWRS_Port,MODEM_PWRS_Pin,GPIO_STATE_LOW);
        return false;
      }
    }
    gpio_set(MODEM_PWRS_Port,MODEM_PWRS_Pin,GPIO_STATE_LOW);
    return true;
  }
  if(component == PWR_BOOST){
    gpio_set(BOOST_PWR_ON_Port,BOOST_PWR_ON_Pin,GPIO_STATE_HIGH);
    HAL_Delay(100);
    gpio_set(BOOST_PWR_ENABLE_Port,BOOST_PWR_ENABLE_Pin,GPIO_STATE_HIGH);
    HAL_Delay(100);
    return true;
  }
  if(component == PWR_LED1_BLUE){
    gpio_set(LED1_BLUE_Port,LED1_BLUE_Pin,GPIO_STATE_LOW);
    return true;
  }
  if(component == PWR_LED1_GREEN){
    gpio_set(LED1_GREEN_Port,LED1_GREEN_Pin,GPIO_STATE_LOW);
    return true;
  }
  if(component == PWR_LED1_RED){
    gpio_set(LED1_RED_Port,LED1_RED_Pin,GPIO_STATE_LOW);
    return true;
  }
  if(component == PWR_LED2_BLUE){
    gpio_set(LED2_BLUE_Port,LED2_BLUE_Pin,GPIO_STATE_LOW);
    return true;
  }
  if(component == PWR_LED2_RED){
    gpio_set(LED2_RED_Port,LED2_RED_Pin,GPIO_STATE_LOW);
    return true;
  }
  if(component == PWR_BUZZER){
    __HAL_TIM_SET_COMPARE(BUZZER_TIMER_HANDLE_Pointer,BUZZER_TIMER_CHANNEL,BUZZER_TIMER_COMPARE);
    return true;
  }
  return false;
}
bool pwr_disable(pwr_component_t component){
  if(component == PWR_MODEM){
    if(gpio_get(MODEM_STATUS_Port,MODEM_STATUS_Pin) == GPIO_STATE_LOW){
      return true;
    }
    uint32_t start = HAL_GetTick();
    gpio_set(MODEM_PWRS_Port,MODEM_PWRS_Pin,GPIO_STATE_HIGH);
    while(gpio_get(MODEM_STATUS_Port,MODEM_STATUS_Pin) != GPIO_STATE_LOW){
      if((HAL_GetTick() - start) > MODEM_PWRS_TIMEOUT_MS){
        gpio_set(MODEM_PWRS_Port,MODEM_PWRS_Pin,GPIO_STATE_LOW);
        return false;
      }
    }
    gpio_set(MODEM_PWRS_Port,MODEM_PWRS_Pin,GPIO_STATE_LOW);
    return true;
  }
  if(component == PWR_BOOST){
    gpio_set(BOOST_PWR_ENABLE_Port,BOOST_PWR_ENABLE_Pin,GPIO_STATE_LOW);
    HAL_Delay(100);
    gpio_set(BOOST_PWR_ON_Port,BOOST_PWR_ON_Pin,GPIO_STATE_LOW);
    HAL_Delay(100);
    return true;
  }
  if(component == PWR_LED1_BLUE){
    gpio_set(LED1_BLUE_Port,LED1_BLUE_Pin,GPIO_STATE_HIGH);
    return true;
  }
  if(component == PWR_LED1_GREEN){
    gpio_set(LED1_GREEN_Port,LED1_GREEN_Pin,GPIO_STATE_HIGH);
    return true;
  }
  if(component == PWR_LED1_RED){
    gpio_set(LED1_RED_Port,LED1_RED_Pin,GPIO_STATE_HIGH);
    return true;
  }
  if(component == PWR_LED2_BLUE){
    gpio_set(LED2_BLUE_Port,LED2_BLUE_Pin,GPIO_STATE_HIGH);
    return true;
  }
  if(component == PWR_LED2_RED){
    gpio_set(LED2_RED_Port,LED2_RED_Pin,GPIO_STATE_HIGH);
    return true;
  }
  if(component == PWR_BUZZER){
    __HAL_TIM_SET_COMPARE(BUZZER_TIMER_HANDLE_Pointer,BUZZER_TIMER_CHANNEL,0);
    return true;
  }
  return false;
}
bool pwr_is_enabled(pwr_component_t component){
  if(component == PWR_MODEM){
    return gpio_get(MODEM_STATUS_Port,MODEM_STATUS_Pin) == GPIO_STATE_HIGH;
  }
  if(component == PWR_BOOST){
    return gpio_get(BOOST_PWR_ON_Port,BOOST_PWR_ON_Pin) == GPIO_STATE_HIGH &&
      gpio_get(BOOST_PWR_ENABLE_Port,BOOST_PWR_ENABLE_Pin) == GPIO_STATE_HIGH;
  }
  if(component == PWR_LED1_BLUE){
    return gpio_get(LED1_BLUE_Port,LED1_BLUE_Pin) == GPIO_STATE_LOW;
  }
  if(component == PWR_LED1_GREEN){
    return gpio_get(LED1_GREEN_Port,LED1_GREEN_Pin) == GPIO_STATE_LOW;
  }
  if(component == PWR_LED1_RED){
    return gpio_get(LED1_RED_Port,LED1_RED_Pin) == GPIO_STATE_LOW;
  }
  if(component == PWR_LED2_BLUE){
    return gpio_get(LED2_BLUE_Port,LED2_BLUE_Pin) == GPIO_STATE_LOW;
  }
  if(component == PWR_LED2_RED){
    return gpio_get(LED2_RED_Port,LED2_RED_Pin) == GPIO_STATE_LOW;
  }
  return false;
}
