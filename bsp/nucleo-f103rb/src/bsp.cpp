#include <SEGGER_RTT.h>

#include "bsp.hpp"
#include "stm32f1xx_hal.h"
#include "gpio.h"
#include "adc.h"
#include "tim.h"

extern TIM_HandleTypeDef htim1;
extern ADC_HandleTypeDef hadc1;

extern "C" void SystemClock_Config(void);


namespace swaw::bsp {


    void init() noexcept {
        HAL_Init();
        SystemClock_Config();
        MX_GPIO_Init();
        MX_TIM1_Init();
        MX_ADC1_Init();
        HAL_ADC_Start(&hadc1);
        HAL_TIM_Base_Start_IT(&htim1);
    }

    void HelloWorld() noexcept {
        HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
        HAL_Delay(1000);
    }

} // namespace swaw::bsp


extern "C" void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if(GPIO_Pin == B1_Pin)
        HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
}

extern "C" void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) {
    HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
}

extern "C" _ssize_t _write(int file, const void *ptr, size_t len) {
  (void) file;  /* Not used, avoid warning */        
  SEGGER_RTT_Write(0, ptr, len);
  return len;
} 
