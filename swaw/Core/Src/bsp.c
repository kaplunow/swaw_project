//#include <cstdio>

#include "bsp.h"
#include "stm32f1xx_hal.h"
#include "gpio.h"
#include "adc.h"
#include "tim.h"
#include "main.h"
#include "ssd1306.h"
#include <stdio.h>

extern TIM_HandleTypeDef htim1;
extern ADC_HandleTypeDef hadc1;

void SystemClock_Config(void);

int tim_status;
int radius_status;
volatile float radius;

void init(){
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
	MX_TIM1_Init();
	MX_ADC1_Init();
	HAL_ADC_Start(&hadc1);
	HAL_TIM_Base_Start_IT(&htim1);
	ssd1306_Init();
	radius = 32;
	radius_status = 0;
}

void HelloWorld() {
	HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
	HAL_Delay(1000);
}

int tim_get_status() {
	return tim_status;
}

float get_radius(){
	return radius;
}

void clear_radius_status(){
	radius_status = 0;
}

int get_radius_status(){
	return radius_status;
}

void tim_clear_status() {
	tim_status = 0;
}

int read_hall() {
	int temp = HAL_ADC_GetValue(&hadc1);
	temp = temp - 4096.0*(HALL_SENSOR_OFFSET/HALL_SENSOR_VCC);
	if(temp < 0){
		temp = -temp;
	}
	return temp;
}

int detection_moment(int hall, int prev_hall){
	if(hall > DETECTION_TRESHOLD && prev_hall < DETECTION_TRESHOLD) {
		return 1;
	}else{
		return 0;
	}
}

int detection_able_reset(int hall, int able_to_detect){
	if(hall < DETECTION_RESET_TRESHOLD){
		return 1;
	}
	else if (hall > DETECTION_TRESHOLD) {
		return 0;
	}
	else{
		return able_to_detect;
	}
}

float calculate_velocity(int periods, float radius){
	float velocity = 2.0 * 3.14 * 3.6 * (radius/100.0) /(periods * HALL_SENSOR_PERIOD/1000);
	return velocity;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if(GPIO_Pin == BUTTON_PLUS_Pin){
        HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
        if(0 == radius_status){
				radius++;
				radius_status = 1;
         }

    }
    else if(GPIO_Pin == BUTTON_MINUS_Pin){
        HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
        if(0 == radius_status){
        	radius--;
        	radius_status = 1;
        }

    }
    //char str[20];
//   	 sprintf(str,"%.1f cm",radius);
//   	 ssd1306_SetCursor(2,21);
//   	 ssd1306_WriteString(str, Font_11x18, White);
//   	 ssd1306_UpdateScreen();
    //printf("radius = %.1f cm \n", radius);
}
 void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) {
    HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
    tim_status = 1;
}

 void display (float velocity){
	 char str[20];
	 ssd1306_Fill(Black);
	 ssd1306_SetCursor(2,0);
	 sprintf(str,"%.2f km/h",velocity);
	 ssd1306_WriteString(str, Font_11x18, White);
	 ssd1306_SetCursor(2,21);
	 sprintf(str,"%.0f cm",get_radius());
	 ssd1306_WriteString(str, Font_11x18, White);
	 ssd1306_UpdateScreen();
 }

// ssize_t _write(int file, const void *ptr, size_t len) {
//  (void) file;  /* Not used, avoid warning */
//  SEGGER_RTT_Write(0, ptr, len);
//  return len;
//}
