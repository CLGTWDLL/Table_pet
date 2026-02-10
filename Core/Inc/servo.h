/*
 * servo.h
 *
 *  Created on: Jan 30, 2026
 *      Author: LHH1021
 */

#ifndef INC_SERVO_H_
#define INC_SERVO_H_

#include "main.h"
#define SERVO_TIMER &htim3

#define SERVO_LF 0
#define SERVO_LR 1
#define SERVO_RF 2
#define SERVO_RR 3

void Servo_Init(void);
void Servo_SetAngle(uint8_t ServoNum,uint16_t Angle);
void Servo_Test(void);

#endif /* INC_SERVO_H_ */
