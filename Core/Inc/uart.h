/*
 * uart.h
 *
 *  Created on: Jan 30, 2026
 *      Author: LHH1021
 */

#ifndef INC_UART_H_
#define INC_UART_H_


#include "main.h"

#define INSTRUCTION_UART huart2
#define DEBUG_UART huart1
#define UART_RX_BUFFER_SIZE 32

#define CMD_NOTHING 0xFF //无效命令
#define CMD_READY 0x18 //准备就绪（唤醒词唤醒）
#define CMD_GO 0x19 //前进
#define CMD_BACK 0x20 //后退
#define CMD_TURN_LEFT 0x21 //左转
#define CMD_TURN_RIGHT 0x22 //右转
#define CMD_SHAKE 0x23 //摇摆
#define CMD_GETDOWN 0x24 //趴下
#define CMD_SITDOWN 0x25 //坐下
#define CMD_SLEEP 0x26 //睡觉
#define CMD_SPEED 0x29 //说话
#define CMD_STAND 0x30 //立正
#define CMD_TRUNAROUND 0x31 //转身
#define CMD_SING 0x32 //唱歌

extern uint8_t rxBuff[UART_RX_BUFFER_SIZE];
extern uint16_t rxLen;
extern uint8_t rxCommand;

void uart_rxMonitor(void);
void uart_debugMonitor(void);


#endif /* INC_UART_H_ */
