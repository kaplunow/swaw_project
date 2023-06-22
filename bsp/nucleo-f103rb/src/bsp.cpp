#include <SEGGER_RTT.h>
#include <cstdio>

#include "bsp.hpp"
#include "stm32f1xx_hal.h"
#include "gpio.h"
#include "adc.h"
#include "tim.h"
#include "main.h"

extern TIM_HandleTypeDef htim1;
extern ADC_HandleTypeDef hadc1;

extern "C" void SystemClock_Config(void);

int tim_status;
volatile float radius;
namespace swaw::bsp {

    void init() noexcept {
        HAL_Init();
        SystemClock_Config();
        MX_GPIO_Init();
        MX_TIM1_Init();
        MX_ADC1_Init();
        HAL_ADC_Start(&hadc1);
        HAL_TIM_Base_Start_IT(&htim1);
        radius = 32;
    }

    void HelloWorld() noexcept {
        HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
        HAL_Delay(1000);
    }

    int tim_get_status() {
        return tim_status;
    }

    float get_radius(){
        return radius;
    }
    
    void tim_clear_status() {
        tim_status = 0;
    }

    int read_hall() {
        int temp = HAL_ADC_GetValue(&hadc1);
        temp = abs(temp - 4096.0*(HALL_SENSOR_OFFSET/HALL_SENSOR_VCC));
        return temp;
    }

    bool detection_moment(int hall, int prev_hall){
        if(hall > DETECTION_TRESHOLD && prev_hall < DETECTION_TRESHOLD) {
            return true;
        }else{
            return false;
        }
    }

    bool detection_able_reset(int hall, bool able_to_detect){
        if(hall < DETECTION_RESET_TRESHOLD){
            return true;
        }
        else if (hall > DETECTION_TRESHOLD) {
            return false;
        }
        else{
            return able_to_detect;
        }
    }

    float calculate_velocity(int periods, float radius){
        float velocity = 2.0 * 3.14 * 3.6 * (radius/100.0) /(periods * HALL_SENSOR_PERIOD/1000);
        return velocity;
    }

} // namespace swaw::bsp


extern "C" void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if(GPIO_Pin == B1_Pin){
        HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
        radius++;
    }
    else if(GPIO_Pin == Button_on_board_Pin){
        HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
        radius--;
    }
    printf("radius = %.1f cm \n", radius);
}

extern "C" void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) {
    HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
    tim_status = 1;
}

extern "C" _ssize_t _write(int file, const void *ptr, size_t len) {
  (void) file;  /* Not used, avoid warning */        
  SEGGER_RTT_Write(0, ptr, len);
  return len;
} 
