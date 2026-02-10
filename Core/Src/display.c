#include "display.h"
#include "bmp.h"
#include "AHT20.h"
#include <string.h>
#include <stdio.h>
#include <math.h>

void display_init(void)
{
  OLED_Init();
  OLED_ColorTurn(0);//0正常显示，1 反色显示
  OLED_DisplayTurn(0);//0正常显示 1 屏幕翻转显示
}

void display_Temp_Hum(uint8_t position_y)
{
  uint8_t tmpBuff[16];
  sprintf((char *)tmpBuff, "%.1f", temperature);
	sprintf((char *)&tmpBuff[8], "%d%%",(int)round(humidity));
	OLED_ShowChinese(0, position_y, 4, 16, OLED_DISPLAY_NORMAL); //"温"
	OLED_ShowChinese(16, position_y, 6, 16, OLED_DISPLAY_NORMAL); //"度"
	OLED_ShowString(34, position_y, tmpBuff, 16, OLED_DISPLAY_NORMAL);
	OLED_ShowChinese(68, position_y, 5, 16, OLED_DISPLAY_NORMAL); //"湿"
	OLED_ShowChinese(84, position_y, 6, 16, OLED_DISPLAY_NORMAL); //"度"
  OLED_ShowString(102, position_y, &tmpBuff[8], 16, OLED_DISPLAY_NORMAL);
}
void display_welcom(void)
{
	OLED_Clear();
  for (int i = 0; i < 4; i++)
  {
    OLED_ShowChinese(32 + i * 16, 8, i, 16, OLED_DISPLAY_NORMAL); //"创客学院"
  }
  OLED_ShowString(16, 28, version, 16, OLED_DISPLAY_NORMAL);
  display_Temp_Hum(48);
	OLED_Refresh();
	HAL_Delay(2000);
  Face_Xiaoxiao();
}

void Face_Sleep(void)
{
  //OLED_Clear();
  OLED_ShowPicture(0, 0, 128, 64, (uint8_t*)Face_sleep, OLED_DISPLAY_NORMAL); //睡觉
  OLED_Refresh();
}

void Face_Stare(void)
{
  //OLED_Clear();
  OLED_ShowPicture(0, 0, 128, 64, (uint8_t*)Face_stare, OLED_DISPLAY_NORMAL); //瞪大眼
  OLED_Refresh();
}

void Face_Happy(void)
{
  //OLED_Clear();
  OLED_ShowPicture(0, 0, 128, 64, (uint8_t*)Face_happy, OLED_DISPLAY_NORMAL); //快乐
  OLED_Refresh();
}

void Face_Mania(void)
{
  //OLED_Clear();
  OLED_ShowPicture(0, 0, 128, 64, (uint8_t*)Face_mania, OLED_DISPLAY_NORMAL); //狂热
  OLED_Refresh();
}

void Face_VeryHappy(void)
{
  //OLED_Clear();
  OLED_ShowPicture(0, 0, 128, 64, (uint8_t*)Face_very_happy, OLED_DISPLAY_NORMAL); //非常快乐
  OLED_Refresh();
}

void Face_OpenEyes(void)
{
  //OLED_Clear();
  OLED_ShowPicture(0, 0, 128, 64, (uint8_t*)Face_eyes, OLED_DISPLAY_NORMAL); //眼睛
  OLED_Refresh();
}

void Face_Xiaoxiao(void)
{
  OLED_ShowPicture(0, 0, 128, 64, (uint8_t*)Dog_Welcom, OLED_DISPLAY_NORMAL);
  OLED_Refresh();
}
