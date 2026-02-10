/*
 * uart.c
 *
 *  Created on: Feb 1, 2026
 *      Author: LHH1021
 */

#include "uart.h"

uint8_t rxBuff[UART_RX_BUFFER_SIZE] = {0};
uint16_t rxLen = 0;
uint8_t rxCommand = CMD_NOTHING;
uint8_t debugBuff[UART_RX_BUFFER_SIZE] = {0};

void uart_rxMonitor(void)
{
  HAL_UARTEx_ReceiveToIdle_IT(&INSTRUCTION_UART, (uint8_t *)rxBuff, sizeof(rxBuff));
}

void uart_debugMonitor(void)
{
  HAL_UARTEx_ReceiveToIdle_IT(&DEBUG_UART, (uint8_t *)debugBuff, sizeof(debugBuff));
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
  if (huart == &INSTRUCTION_UART)
  {
    rxLen = Size;
    rxCommand = rxBuff[0];
    uart_rxMonitor();
  }
  else if (huart == &DEBUG_UART)
  {
    if (Size == 1)
    {
      rxCommand = debugBuff[0];
      uart_debugMonitor();
    }
  }
}

