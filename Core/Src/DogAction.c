#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "DogAction.h"
#include "key.h"
#include "servo.h"
#include "uart.h"
#include "led.h"
#include "display.h"

#define KEY_DEBUG 0 // 1: 按键调试模式

void Action_Advance(void);
void Action_Back(void);
void Action_TuenLeft(void);
void Action_TurnRight(void);
void Action_TurnAround(void);
void Action_Sit(void);
void Action_Stand(void);
void Action_Sleep(void);
void Action_GetDown(void);
void Action_Hello(void);
void Action_Swing(void);
void Action_Echo(void);

static void Servo_LF(float Angle);
static void Servo_RF(float Angle);
static void Servo_LR(float Angle);
static void Servo_RR(float Angle);

uint32_t SpeedDelay = 200;
bool keyEnableFlag = false;

int DogAction(void)
{
  uint8_t tmpBuff[32];
  static bool dogStandFlag = true;
  if((rxCommand == CMD_GO) || (rxCommand == CMD_BACK) || (rxCommand == CMD_TURN_LEFT) || (rxCommand == CMD_TURN_RIGHT) || (rxCommand == CMD_SHAKE) || (rxCommand == CMD_TRUNAROUND) || (rxCommand == CMD_SPEED))
  {
    // 如果是需要站立完成的动作
    if(dogStandFlag == false)
    {
      // 如果当前不是站立状态
      dogStandFlag = true;
      Action_Stand();
    }
  }
  // 根据串口命令完成动作
  if(rxCommand != CMD_NOTHING)
  {
    printf("Get CMD: %02x \n", rxCommand);
    switch(rxCommand)
    {
      case CMD_GO:
        Face_VeryHappy();
        Action_Advance();
        Face_OpenEyes();
        HAL_Delay(500);
        Action_Stand();
        break;
      case CMD_BACK:
        Face_Happy();
        Action_Back();
        Face_OpenEyes();
        HAL_Delay(500);
        Action_Stand();
        break;
      case CMD_TURN_LEFT:
        Face_Stare();
        Action_TuenLeft();
        Face_OpenEyes();
        HAL_Delay(500);
        Action_Stand();
        break;
      case CMD_TURN_RIGHT:
        Face_Stare();
        Action_TurnRight();
        Face_OpenEyes();
        HAL_Delay(500);
        Action_Stand();
        break;
      case CMD_SHAKE:
        Face_VeryHappy();
        Action_Swing();
        Face_OpenEyes();
        HAL_Delay(500);
        Action_Stand();
        break;
      case CMD_GETDOWN:
        Face_Stare();
        Action_GetDown();
        dogStandFlag = false;
        break;
      case CMD_SITDOWN:
        Face_Happy();
        Action_Sit();
        dogStandFlag = false;
        break;
      case CMD_SLEEP:
        Action_Sleep();
        display_welcom();
        Face_Sleep();
        dogStandFlag = false;
        break;
      case CMD_STAND:
        // 添加按键切换功能
        keyEnableFlag ^= 1;
        Key1Pressed = Key2Pressed = Key3Pressed = Key4Pressed = Key5Pressed = false;
        sprintf((char*)tmpBuff, "Key %s", (keyEnableFlag == true) ? "Enable" : "Disable");
        printf("%s\n", tmpBuff);
        OLED_Clear();
        OLED_ShowString((128 - (strlen((char*)tmpBuff) * 8)) >> 1, 24, tmpBuff, 16, OLED_DISPLAY_NORMAL);
        OLED_Refresh();
        HAL_Delay(2000);
        Face_OpenEyes();
        Action_Stand();
        dogStandFlag = true;
        break;
      case CMD_TRUNAROUND:
        Face_OpenEyes();
        Action_TurnAround();
        HAL_Delay(500);
        Action_Sit();
        break;
      case CMD_SPEED:
        Face_Xiaoxiao();
        break;
      case CMD_SING:
        Action_Sit();
        keyEnableFlag = false;
        break;
      case CMD_READY:
        Face_Xiaoxiao();
        led_flash_begin();
        break;
      default:
        //      Action_Stand();
        //      Action_Echo();
        break;
    }
    rxCommand = CMD_NOTHING;
    rxLen = 0;
  }
  else if(keyEnableFlag)
  {
    // 根据按键完成动作
    if(Key5Pressed)
    {
      Key5Pressed = false;
      printf("Key5 pressed, advance\n");
      // 前进
      rxCommand = CMD_GO;
    }
    if(Key4Pressed)
    {
      Key4Pressed = false;
      printf("Key4 pressed, back\n");
      // 后退
      rxCommand = CMD_BACK;
    }
    if(Key1Pressed)
    {
      Key1Pressed = false;
      printf("Key1 pressed, Turn left\n");
      // 左转
      rxCommand = CMD_TURN_LEFT;
    }
    if(Key2Pressed)
    {
      Key2Pressed = false;
      printf("Key2 pressed, Turn right\n");
      // 右转
      rxCommand = CMD_TURN_RIGHT;
    }
    if(Key3Pressed)
    {
      Key3Pressed = false;
      printf("Key3 pressed, Sit after turn around\n");
      // 转身
      rxCommand = CMD_TRUNAROUND;
    }
  }
  return 0;
}

// 前进
void Action_Advance(void)
{
  uint8_t i;

  printf("Action_Advance\n");
  for(i = 0; i < 5; i++)
  {
    // Step 1
    Servo_RF(120);
    Servo_LR(120);
    HAL_Delay(20);
    Servo_LF(60);
    Servo_RR(60);
    HAL_Delay(SpeedDelay);
    // Step 2
    Servo_RF(150);
    Servo_LR(150);
    HAL_Delay(SpeedDelay);
    // Step 3
    Servo_LF(90);
    Servo_RR(90);
    HAL_Delay(SpeedDelay);
    // Step 4
    Servo_LF(120);
    Servo_RR(120);
    HAL_Delay(20);
    Servo_RF(60);
    Servo_LR(60);
    HAL_Delay(SpeedDelay);
    // Step 5
    Servo_LF(150);
    Servo_RR(150);
    HAL_Delay(SpeedDelay);
    // Step 6
    Servo_RF(90);
    Servo_LR(90);
    HAL_Delay(SpeedDelay);
  }
}

// 后退
void Action_Back(void)
{
  uint8_t i;

  printf("Action_Back\n");
  for(i = 0; i < 5; i++)
  {
    // Step 1
    Servo_RF(120);
    Servo_LR(120);
    HAL_Delay(20);
    Servo_LF(150);
    Servo_RR(150);
    HAL_Delay(SpeedDelay);
    // Step 2
    Servo_RF(60);
    Servo_LR(60);
    HAL_Delay(SpeedDelay);
    // Step 3
    Servo_LF(120);
    Servo_RR(120);
    HAL_Delay(20);
    Servo_RF(150);
    Servo_LR(150);
    HAL_Delay(SpeedDelay);
    // Step 4
    Servo_LF(90);
    Servo_RR(90);
    HAL_Delay(SpeedDelay);
    // Step 5
    Servo_LF(60);
    Servo_RR(60);
    HAL_Delay(SpeedDelay);
  }
}

// 向左旋转
void Action_TuenLeft(void)
{
  uint8_t i;

  printf("Action_TuenLeft\n");
  for(i = 0; i < 7; i++)
  {
    // Step 1
    Servo_RF(45);
    Servo_LR(150);
    HAL_Delay(SpeedDelay);
    // Step 2
    Servo_LF(45);
    Servo_RR(150);
    HAL_Delay(SpeedDelay);
    // Step 3
    Servo_RF(90);
    Servo_LR(90);
    HAL_Delay(SpeedDelay);
    // Step 4
    Servo_LF(90);
    Servo_RR(90);
    HAL_Delay(SpeedDelay);
  }
}

// 向右旋转
void Action_TurnRight(void)
{
  uint8_t i;

  printf("Action_TurnRight\n");
  for(i = 0; i < 7; i++)
  {
    // Step 1
    Servo_LF(45);
    Servo_RR(150);
    HAL_Delay(SpeedDelay);
    // Step 2
    Servo_RF(45);
    Servo_LR(150);
    HAL_Delay(SpeedDelay);
    // Step 3
    Servo_LF(90);
    Servo_RR(90);
    HAL_Delay(SpeedDelay);
    // Step 4
    Servo_RF(90);
    Servo_LR(90);
    HAL_Delay(SpeedDelay);
  }
}

// 转身
void Action_TurnAround(void)
{
  uint8_t i;

  printf("Action_TurnAround\n");
  for(i = 0; i < 2; i++)
  {
    Action_TurnRight();
  }
}

// 坐下
void Action_Sit(void)
{
  printf("Action_Sit\n");
  Servo_LF(120);
  Servo_RF(120);
  HAL_Delay(50);
  Servo_LR(60);
  Servo_RR(60);
}

// 站立
void Action_Stand(void)
{
  printf("Action_Stand\n");
  Servo_LF(120);
  Servo_RF(120);
  HAL_Delay(50);
  Servo_LR(120);
  Servo_RR(120);
	HAL_Delay(200);
}

// 睡觉
void Action_Sleep(void)
{
  printf("Action_Sleep\n");
  Servo_LF(180);
  Servo_RF(180);
  HAL_Delay(50);
  Servo_LR(0);
  Servo_RR(0);
}

// 趴下
void Action_GetDown(void)
{
  printf("Action_GetDown\n");
  Servo_LF(0);
  Servo_RF(0);
  HAL_Delay(50);
  Servo_LR(0);
  Servo_RR(0);
}

// 打招呼（说话）
void Action_Hello(void)
{
  uint8_t i;
  int16_t angle;

  printf("Action_Hello\n");
  Action_Sit();
  HAL_Delay(500);
  for(i = 0; i < 3; i++)
  {
    for(angle = 60; angle >= 0; angle -= 5)
    {
      Servo_RF(angle);
      HAL_Delay(10);
    }
    HAL_Delay(300);
    for(angle = 0; angle <= 60; angle += 5)
    {
      Servo_RF(angle);
      HAL_Delay(10);
    }
  }
  HAL_Delay(SpeedDelay);
  Servo_RF(120);
}

// 摇摆
void Action_Swing(void)
{
  uint8_t i;

  printf("Action_Swing\n");
  for(i = 0; i < 5; i++)
  {
    Servo_LF(45);
    Servo_RF(45);
    HAL_Delay(50);
    Servo_LR(45);
    Servo_RR(45);
    HAL_Delay(SpeedDelay);
    Servo_LF(135);
    Servo_RF(135);
    HAL_Delay(135);
    Servo_LR(135);
    Servo_RR(135);
    HAL_Delay(SpeedDelay);
  }
}

// 回声
void Action_Echo(void)
{
  printf("Action_Echo\n");
  Servo_RF(45);
  HAL_Delay(SpeedDelay);
  Servo_RF(120);
}

// 左前脚
static void Servo_LF(float Angle)
{
  Servo_SetAngle(SERVO_LF, Angle);
}

// 右前脚
static void Servo_RF(float Angle)
{
  Servo_SetAngle(SERVO_RF, 180 - Angle);
}

// 左后脚
static void Servo_LR(float Angle)
{
  Servo_SetAngle(SERVO_LR, Angle);
}

// 右后脚
static void Servo_RR(float Angle)
{
  Servo_SetAngle(SERVO_RR, 180 - Angle);
}
