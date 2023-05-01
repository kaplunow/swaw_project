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


} // namespace swaw::bsp

extern "C" void SysTick_Handler(void) {
    HAL_IncTick();
}

extern "C" _ssize_t _write(int file, const void *ptr, size_t len) {
  (void) file;  /* Not used, avoid warning */
  SEGGER_RTT_Write(0, ptr, len);
  return len;
}
