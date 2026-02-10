/*
 * timer.c
 *
 *  Created on: Jan 30, 2026
 *      Author: LHH1021
 */

#include "timer.h"
#include "led.h"
#include "servo.h"

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
  if (htim == SERVO_TIMER)
  {
    // 以下部分，代码控制输出舵机需要的PWM波形
    // 手动翻转PC4/PC5
    // CNT==CCR，输出PWM mode 2 的有效电平(高电平)
    if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3)
    {
      HAL_GPIO_WritePin(RR_IO_GPIO_Port, RR_IO_Pin, GPIO_PIN_SET);
    }
    else if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4)
    {
      HAL_GPIO_WritePin(LR_IO_GPIO_Port, LR_IO_Pin, GPIO_PIN_SET);
    }
  }
  else if (htim == RGB_TIMER)
  {
    if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
    {
      // 以下部分，代码控制输出 LED R 所需要的PWM波形
      // 手动翻转Led_G
      // CNT==CCR，输出PWM mode 1 的无效电平(低电平)
      HAL_GPIO_WritePin(Led_R_GPIO_Port, Led_R_Pin, GPIO_PIN_RESET);
    }
    else if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
    {
      // 以下部分，代码控制输出 LED R 所需要的PWM波形
      // 手动翻转Led_G
      // CNT==CCR，输出PWM mode 1 的无效电平(低电平)
      HAL_GPIO_WritePin(Led_G_GPIO_Port, Led_G_Pin, GPIO_PIN_RESET);
    }
    else if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3)
    {
      // 以下部分，代码控制输出 LED R 所需要的PWM波形
      // 手动翻转Led_G
      // CNT==CCR，输出PWM mode 1 的无效电平(低电平)
      HAL_GPIO_WritePin(Led_B_GPIO_Port, Led_B_Pin, GPIO_PIN_RESET);
    }
  }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if(htim == SERVO_TIMER)
  {
    // 20ms周期回调，控制舵机PWM周期
    // 在每个PWM周期开始，输出 PWM mode 2 的无效电平(低电平)
    // 因为后面有反相器，输出低电平
    HAL_GPIO_WritePin(LR_IO_GPIO_Port, LR_IO_Pin | RR_IO_Pin, GPIO_PIN_RESET);
  }
  else if(htim == RGB_TIMER)
  {
    //控制LED_R, LED_G, LED_B的PWM波形
    //在每个PWM周期开始，输出 PWM mode 1 的有效电平(高电平)
    HAL_GPIO_WritePin(Led_G_GPIO_Port, Led_R_Pin | Led_G_Pin | Led_B_Pin, GPIO_PIN_SET);
  }
  else if(htim == RGB_NOMAL_FLUSH_TIMER)
  {
    led_rgb_update();
  }
  else if(htim == RGB_FLASH_FLUSH_TIMER)
  {
    led_flash_control();
  }
}
