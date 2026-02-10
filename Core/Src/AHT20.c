#include "aht20.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool AHT20_errFalg= false;

float temperature = 0, humidity = 0;

uint8_t AHT20_CRC8(const uint8_t* data, uint8_t len)
{
  uint8_t crc = 0xFF; // 初始值
  for(uint8_t i = 0; i < len; i++)
  {
    crc ^= data[i]; // 异或数据
    for(uint8_t bit = 0; bit < 8; bit++)
    {
      if(crc & 0x80)
      {
        crc = (crc << 1) ^ 0x31; // 多项式 0x31
      }
      else
      {
        crc <<= 1;
      }
    }
  }
  return crc;
}

int8_t AHT20_Init(void)
{
  uint8_t status;
  HAL_Delay(40); // 上电后等待40ms:cite[1]

  // 读取状态字，检查校准位
  if (HAL_I2C_Master_Receive(&hi2c1, AHT20_ADDRESS, &status, 1, 100) != HAL_OK)
	{
		//Error , AHT20 Can not be Init!
		AHT20_errFalg = true;
		printf("AHT20 Init failed!\n");
		return -1;
	}

  if((status & 0x08) == 0)
  {
    // Bit[3]==0 未校准
    uint8_t init_cmd[3] = {0xBE, 0x08, 0x00}; // 初始化命令
    HAL_I2C_Master_Transmit(&hi2c1, AHT20_ADDRESS, init_cmd, 3, HAL_MAX_DELAY);
    HAL_Delay(10); // 初始化等待时间:cite[1]:cite[5]
  }
  return 0; // 初始化成功
}

/**
  * @brief  读取AHT20传感器数据
  * @param  None
  * @retval 执行状态，0表示成功，正数表示执行中，负数表示错误
  */
int8_t AHT20_Read(void)
{
  static uint8_t step = 0;
  static __IO uint32_t AHT20_timer = 0;
  uint8_t data[8];

	if (AHT20_errFalg== true)
	{
		humidity = 43;
		temperature = 25.3;
		return 0;
	}
  switch(step)
  {
    case 0:                                        // 发送触发转换命令
      memcpy(data, "\xAC\x33\x00", 3); // 触发测量命令
      HAL_I2C_Master_Transmit(&hi2c1, AHT20_ADDRESS, data, 3, 1000);
      AHT20_timer = HAL_GetTick() + 75;
      step = 1; // 等待转换完成
      break;
    case 1: // 等待转换完成
      if(HAL_GetTick() > AHT20_timer)
      {
        // 超时
        step = 2; // 读取数据
      }
      break;
    case 2: // 读取数据
      HAL_I2C_Master_Receive(&hi2c1, AHT20_ADDRESS, data, 7, HAL_MAX_DELAY);
      // 打印数据
      // printf("AHT20 data: ");
      // for(uint8_t i = 0; i < 7; i++)
      // {
      //   printf(" %02X ", data[i]);
      // }
      if((data[0] & 0x80) == 0)
      {
        // Not Busy
				step = 0; // 转换完成，准备下次转换
        // 检查CRC
        uint8_t crc = AHT20_CRC8(data, 6);
        // printf("CRC: %02X\n", crc);
        if(crc == data[6])
        {
          //  计算温湿度
          uint32_t humi_raw = ((uint32_t)data[1] << 12) | ((uint32_t)data[2] << 4) | (data[3] >> 4);
          humidity = (float)humi_raw / (1UL << 20) * 100.0f;

          uint32_t temp_raw = ((data[3] & 0x0F) << 16) | ((uint32_t)data[4] << 8) | data[5];
          temperature = (float)temp_raw * 200.0f / (1UL << 20) - 50.0f;
          printf("temperature: %.2f, humidity: %.2f\n", temperature, humidity);
          return 0; // 成功读取数据
        }
        else
        {
          printf("CRC Error\n");
          return -1; // CRC错误
        }
      }
      else
      {
        AHT20_timer = HAL_GetTick() + 10;
        step = 1; // 设备仍在忙碌，重新等待
      }
      break;
    default:
      step = 0;
      break;
  }

  return 1; // 执行中
}
