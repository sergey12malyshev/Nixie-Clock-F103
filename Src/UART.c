#include <stdio.h>
#include <stdbool.h>

#include "main.h"
#include "UART.h"

extern UART_HandleTypeDef huart1;
static uint8_t str[25];

void sendUART(uint8_t TxBufferUartLocal[])
{ //передача в блокирующем режиме
  const uint8_t blockDelayUART_ms = 50; //t(sec)=(FRAME/BOUND+MINT)*N = (10/115200+0.00001)*100 = 19 мс
  HAL_UART_Transmit(&huart1, (uint8_t*) TxBufferUartLocal, strlen((char *) TxBufferUartLocal), blockDelayUART_ms);
}

void sendUART_SNversion(void)
{
  sprintf((char *)str, "Version: %d", VERSION_MAJOR);
  sendUART(str);
  sendUART(".");
  sprintf((char *)str, "%d", VERSION_MINOR);
  sendUART(str);
  sendUART(".");
  sprintf((char *)str, "%d\r\n", VERSION_PATCH);
  sendUART(str);
}
