#include "gpio_drivers.h"
//Button callback. will fire on both rising and falling edge
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
  if(GPIO_Pin == BUTTON_AND_BOOT_Pin){
    __NOP();
  }
}
void gpio_set(GPIO_TypeDef* port, uint16_t pin, gpio_state_t state){
  GPIO_PinState hal_pin_state = (state == GPIO_STATE_HIGH) ? GPIO_PIN_SET : GPIO_PIN_RESET;
  HAL_GPIO_WritePin(port,pin,hal_pin_state);
}
gpio_state_t gpio_get(GPIO_TypeDef* port, uint16_t pin){
  return HAL_GPIO_ReadPin(port,pin) == GPIO_PIN_SET ? GPIO_STATE_HIGH : GPIO_STATE_LOW;
}
