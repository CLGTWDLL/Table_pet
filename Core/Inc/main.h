/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
#define KEY_DELAY_MS 10
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void printBuff(uint8_t *buff, uint16_t len);
void mySysTick_Callback(void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SysLed_Pin GPIO_PIN_4
#define SysLed_GPIO_Port GPIOA
#define RR_IO_Pin GPIO_PIN_4
#define RR_IO_GPIO_Port GPIOC
#define LR_IO_Pin GPIO_PIN_5
#define LR_IO_GPIO_Port GPIOC
#define Led_B_Pin GPIO_PIN_0
#define Led_B_GPIO_Port GPIOB
#define Led_R_Pin GPIO_PIN_1
#define Led_R_GPIO_Port GPIOB
#define Led_G_Pin GPIO_PIN_2
#define Led_G_GPIO_Port GPIOB
#define OLED_CS_Pin GPIO_PIN_12
#define OLED_CS_GPIO_Port GPIOB
#define OLED_DC_Pin GPIO_PIN_6
#define OLED_DC_GPIO_Port GPIOC
#define OLED_RES_Pin GPIO_PIN_7
#define OLED_RES_GPIO_Port GPIOC
#define Key4_Pin GPIO_PIN_11
#define Key4_GPIO_Port GPIOA
#define Key3_Pin GPIO_PIN_12
#define Key3_GPIO_Port GPIOA
#define Key2_Pin GPIO_PIN_15
#define Key2_GPIO_Port GPIOA
#define Key1_Pin GPIO_PIN_3
#define Key1_GPIO_Port GPIOB
#define Key5_Pin GPIO_PIN_4
#define Key5_GPIO_Port GPIOB
#define I2C1_SCL_Pin GPIO_PIN_6
#define I2C1_SCL_GPIO_Port GPIOB
#define I2C1_SDA_Pin GPIO_PIN_7
#define I2C1_SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
extern I2C_HandleTypeDef hi2c1;
extern SPI_HandleTypeDef hspi2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim7;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern uint8_t version[];
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
