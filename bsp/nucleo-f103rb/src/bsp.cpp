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
        HAL_Delay(500);
    }

} // namespace swaw::bsp

extern "C" void SysTick_Handler(void) {
    HAL_IncTick();
}

extern "C" size_t _write(int file, const void *ptr, size_t len) {
  (void) file;  /* Not used, avoid warning */
  SEGGER_RTT_Write(0, ptr, len);
  return len;
} 
