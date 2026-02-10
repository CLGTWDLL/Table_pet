#include "servo.h"

// 4个舵机控制的通道：LF,LR,RF,RR
const uint32_t SERVO_NAME[] = {TIM_CHANNEL_2, TIM_CHANNEL_4, TIM_CHANNEL_1, TIM_CHANNEL_3};

void Servo_Init(void)
{
  HAL_TIM_PWM_Start(SERVO_TIMER, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(SERVO_TIMER, TIM_CHANNEL_2);
  HAL_TIM_Base_Start_IT(SERVO_TIMER);
  HAL_TIM_PWM_Start_IT(SERVO_TIMER, TIM_CHANNEL_3);
  HAL_TIM_PWM_Start_IT(SERVO_TIMER, TIM_CHANNEL_4);
}

void Servo_SetAngle(uint8_t ServoNum, uint16_t newAngle)
{
  uint16_t pulseTime;
  if (newAngle > 180)
  {
    newAngle = newAngle % 180; // 舵机转动角度范围0-180度
  }
  // 0.5ms->0deg, 1.5ms->90deg, 2.5ms->180deg
  // 50->0.5ms, 100->1ms, 150->1.5ms, 200->2ms, 250->2.5ms
  pulseTime = 50 + (newAngle * 10) / 9; // 舵机控制脉冲宽度，单位10us
  __HAL_TIM_SET_COMPARE(SERVO_TIMER, SERVO_NAME[ServoNum], pulseTime);
}

#if 0
void Servo_Test(void)
{
  uint16_t angle;

  for (angle = 0; angle <= 180; angle += 45)
  {
    Servo_SetAngle(SERVO_LF, angle);
    Servo_SetAngle(SERVO_RF, angle);
    Servo_SetAngle(SERVO_LR, angle);
    Servo_SetAngle(SERVO_RR, angle);
    HAL_Delay(2000);
  }
}

#endif

