/*
 * led.c
 *
 *  Created on: Feb 1, 2026
 *      Author: LHH1021
 */


#include "led.h"
#include <stdio.h>
#include <stdbool.h>

#define RGB_PWM_MAX 256

#define RGB_UPDATE_R(newColor) __HAL_TIM_SET_COMPARE(RGB_TIMER, RGB_CHANNEL_R, (newColor))
#define RGB_UPDATE_G(newColor) __HAL_TIM_SET_COMPARE(RGB_TIMER, RGB_CHANNEL_G, (newColor))
#define RGB_UPDATE_B(newColor) __HAL_TIM_SET_COMPARE(RGB_TIMER, RGB_CHANNEL_B, (newColor))

#define SysLed_ON() HAL_GPIO_WritePin(SysLed_GPIO_Port, SysLed_Pin, GPIO_PIN_RESET)
#define SysLed_OFF() HAL_GPIO_WritePin(SysLed_GPIO_Port, SysLed_Pin, GPIO_PIN_SET)

#define RGB_LED_ON(COLOR_VALUE)        \
  do                                   \
  {                                    \
    uint32_t newColor = (COLOR_VALUE); \
    RGB_UPDATE_B((uint8_t)(newColor)); \
    newColor = newColor >> 8;          \
    RGB_UPDATE_G((uint8_t)(newColor)); \
    newColor = newColor >> 8;          \
    RGB_UPDATE_R((uint8_t)(newColor)); \
  } while (0)

// 定义颜色，为了避免 CCR 为0，不能进入OC中断，CCR最小值为1
#define RGB_COLOR_PURPO 0x8B008B
#define RGB_COLOR_BLACK 0x010101
#define RGB_COLOR_RED 0xF00101
#define RGB_COLOR_BLUE 0x0101F0

void led_rgb_Init(void)
{
  RGB_LED_ON(RGB_COLOR_BLACK);
  HAL_TIM_PWM_Start_IT(RGB_TIMER, RGB_CHANNEL_R); // LED_R
  HAL_TIM_PWM_Start_IT(RGB_TIMER, RGB_CHANNEL_G); // LED_G
  HAL_TIM_PWM_Start_IT(RGB_TIMER, RGB_CHANNEL_B); // LED_B
  HAL_TIM_Base_Start_IT(RGB_TIMER);
  HAL_TIM_Base_Start_IT(&htim6); // 启动RGB 动态更新，更新周期 10ms
}

//中断周期 10ms
void led_rgb_update(void)
{
  static uint16_t color_r = 1;
  static uint16_t color_g = 1;
  static uint16_t color_b = 1;

//  RGB_UPDATE_R(color_r++);
//  if (color_r == RGB_PWM_MAX)
//  {
//    color_r = 1;
//    RGB_UPDATE_G(color_g++);
//    if (color_g == RGB_PWM_MAX)
//    {
//      color_g = 1;
//      RGB_UPDATE_B(color_b++);
//      if (color_b == RGB_PWM_MAX)
//      {
//        color_b = 1;
//      }
//    }
//  }
	//Another Showing
	RGB_UPDATE_B(color_b++);
  if (color_b == RGB_PWM_MAX)
  {
    color_b = 1;
    RGB_UPDATE_R(color_r++);
    if (color_r == RGB_PWM_MAX)
    {
      color_r = 1;
      RGB_UPDATE_G(color_g++);
      if (color_g == RGB_PWM_MAX)
      {
        color_g = 1;
      }
    }
  }
}

//中断周期 10ms
void led_flash_control(void)
{
  static uint8_t step = 0;
  static uint16_t timeout = 0;
  static uint8_t flashTimes = 0;
  static uint32_t oldColor = 0;

  switch (step)
  {
  case 0: // 已点亮炫彩灯和状态灯
    // 记录之前的颜色
    oldColor = 0;
    oldColor =  (__HAL_TIM_GET_COMPARE(RGB_TIMER, RGB_CHANNEL_R) << 16) \
              | (__HAL_TIM_GET_COMPARE(RGB_TIMER, RGB_CHANNEL_G) << 8) \
              | __HAL_TIM_GET_COMPARE(RGB_TIMER, RGB_CHANNEL_B);

    step = 1;
  case 1:
	 SysLed_ON();
    RGB_LED_ON(RGB_COLOR_RED);
    timeout = 12;
    step = 2;
    break;
  case 2: // 等待点亮时间
    timeout--;
    if (timeout == 0)
    {
      SysLed_OFF();
      RGB_LED_ON(RGB_COLOR_BLUE);
      timeout = 30;
      step = 3;
    }
    break;
  case 3: // 等待熄灭时间
    timeout--;
    if (timeout == 0)
    {
      flashTimes++;
      if (flashTimes == 2)
      {
        flashTimes = 0;
        // 设置回之前的颜色
        RGB_LED_ON(oldColor);
        HAL_TIM_Base_Stop_IT(RGB_FLASH_FLUSH_TIMER);
        HAL_TIM_Base_Start_IT(RGB_NOMAL_FLUSH_TIMER); // 重启RGB 动态更新
        step = 0;
      }
      else
      {
        step = 1;
      }
    }
    break;
  default:
    step = flashTimes = oldColor = timeout = 0;
    break;
  }
}

void led_flash_begin(void)
{
  HAL_TIM_Base_Stop_IT(RGB_NOMAL_FLUSH_TIMER);  // 停止RGB 动态更新
  HAL_TIM_Base_Start_IT(RGB_FLASH_FLUSH_TIMER); // 开始闪烁控制
}

#if 0
void led_rgb_test(void)
{
  uint16_t color;
//	HAL_TIM_Base_Stop_IT(&htim7);
  printf("Test R\n");
	RGB_LED_ON(RGB_COLOR_BLACK);
	HAL_Delay(500);
  for (color = 0; color < RGB_PWM_MAX; color +=2)
  {
    RGB_UPDATE_R(color);
    HAL_Delay(20);
  }
	HAL_Delay(500);
  RGB_LED_ON(RGB_COLOR_BLACK);
	HAL_Delay(500);
  printf("Test G\n");
  for(color = 0; color < RGB_PWM_MAX; color += 5)
  {
    RGB_UPDATE_G(color);
    HAL_Delay(100);
  }
	HAL_Delay(500);
  RGB_LED_ON(RGB_COLOR_BLACK);
	HAL_Delay(500);
  printf("Test B\n");
  for (color = 0; color < RGB_PWM_MAX; color +=2)
  {
    RGB_UPDATE_B(color);
    HAL_Delay(20);
  }
	HAL_Delay(500);
  RGB_LED_ON(RGB_COLOR_BLACK);
	HAL_Delay(500);
	RGB_LED_ON(RGB_COLOR_PURPO);
	HAL_Delay(500);
	RGB_LED_ON(RGB_COLOR_BLACK);
	HAL_Delay(500);
	RGB_UPDATE_B(0);
	RGB_LED_ON(RGB_COLOR_PURPO);
	HAL_Delay(500);
	RGB_LED_ON(RGB_COLOR_BLACK);
	HAL_Delay(500);
	RGB_LED_ON(RGB_COLOR_RED);
	HAL_Delay(500);
	RGB_LED_ON(RGB_COLOR_BLUE);
	HAL_Delay(500);
	RGB_LED_ON(RGB_COLOR_RED);
	HAL_Delay(500);
	RGB_LED_ON(RGB_COLOR_BLUE);
	HAL_Delay(500);
}
#endif
