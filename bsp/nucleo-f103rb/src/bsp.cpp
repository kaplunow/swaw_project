#include <SEGGER_RTT.h>

#include "bsp.hpp"
#include "gpio.h"
#include "stm32f1xx_hal.h"

extern "C" void SystemClock_Config(void);



namespace swaw::bsp {


    void init() noexcept {
        HAL_Init();
        SystemClock_Config();
        MX_GPIO_Init();
    }

    void HelloWorld() noexcept {
        HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
        HAL_Delay(1000);
    }

    // void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    //     if(GPIO_Pin == B1_Pin)
    //         HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
    // }

} // namespace swaw::bsp

extern "C" void SysTick_Handler(void) {
    HAL_IncTick();
}

extern "C" _ssize_t _write(int file, const void *ptr, size_t len) {
  (void) file;  /* Not used, avoid warning */        
  SEGGER_RTT_Write(0, ptr, len);
  return len;
} 
