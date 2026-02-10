/*
 * led.h
 *
 *  Created on: Jan 30, 2026
 *      Author: LHH1021
 */

#ifndef INC_LED_H_
#define INC_LED_H_

#include "main.h"

#define RGB_TIMER &htim4
#define RGB_NOMAL_FLUSH_TIMER &htim6 //中断周期 10ms
#define RGB_FLASH_FLUSH_TIMER &htim7 //中断周期 10ms

#define RGB_CHANNEL_R TIM_CHANNEL_1
#define RGB_CHANNEL_G TIM_CHANNEL_2
#define RGB_CHANNEL_B TIM_CHANNEL_3

void SysLed_on(void);
void led_rgb_Init(void);
void led_rgb_update(void);
void led_flash_control(void);
void led_flash_begin(void);
void led_rgb_test(void);
#endif /* INC_LED_H_ */
