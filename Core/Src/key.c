/*
 * key.c
 *
 *  Created on: Feb 5, 2026
 *      Author: LHH1021
 */


#include "key.h"

bool Key1Pressed = false, Key2Pressed = false, Key3Pressed = false, Key4Pressed = false, Key5Pressed = false;
uint8_t Key1Delay = 0, Key2Delay = 0, Key3Delay = 0, Key4Delay = 0, Key5Delay = 0;

void key_debounce(void)
{
  if (Key1Delay != 0)
  {
    Key1Delay--;
    if (Key1Delay == 0)
    {
      if (HAL_GPIO_ReadPin(Key1_GPIO_Port, Key1_Pin) == GPIO_PIN_RESET)
      {
        Key1Pressed = true;
      }
    }
  }
  if (Key2Delay != 0)
  {
    Key2Delay--;
    if (Key2Delay == 0)
    {
      if (HAL_GPIO_ReadPin(Key2_GPIO_Port, Key2_Pin) == GPIO_PIN_RESET)
      {
        Key2Pressed = true;
      }
    }
  }
  if (Key3Delay != 0)
  {
    Key3Delay--;
    if (Key3Delay == 0)
    {
      if (HAL_GPIO_ReadPin(Key3_GPIO_Port, Key3_Pin) == GPIO_PIN_RESET)
      {
        Key3Pressed = true;
      }
    }
  }
  if (Key4Delay != 0)
  {
    Key4Delay--;
    if (Key4Delay == 0)
    {
      if (HAL_GPIO_ReadPin(Key4_GPIO_Port, Key4_Pin) == GPIO_PIN_RESET)
      {
        Key4Pressed = true;
      }
    }
  }
  if (Key5Delay != 0)
  {
    Key5Delay--;
    if (Key5Delay == 0)
    {
      if (HAL_GPIO_ReadPin(Key5_GPIO_Port, Key5_Pin) == GPIO_PIN_RESET)
      {
        Key5Pressed = true;
      }
    }
  }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  switch (GPIO_Pin)
  {
  case Key1_Pin:
    Key1Delay = KEY_DELAY_MS;
    break;
  case Key2_Pin:
    Key2Delay = KEY_DELAY_MS;
    break;
  case Key3_Pin:
    Key3Delay = KEY_DELAY_MS;
    break;
  case Key4_Pin:
    Key4Delay = KEY_DELAY_MS;
    break;
  case Key5_Pin:
    Key5Delay = KEY_DELAY_MS;
    break;
  default:
		break;
  }
}
