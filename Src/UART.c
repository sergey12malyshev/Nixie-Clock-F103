#include <stdio.h>
#include <stdbool.h>

#include "main.h"
#include "UART.h"

extern UART_HandleTypeDef huart1;
extern RTC_TimeTypeDef RTC_Time;

static uint8_t str[15];
static uint8_t asciiGit[]="\
********************************************************\r\n\
* https://github.com/sergey12malyshev/Nixie-Clock-F103 *\r\n\
********************************************************\r\n";

void sendUART(uint8_t TxBufferUartLocal[])
{ //передача в блокирующем режиме
  const uint8_t blockDelayUART_ms = 50u; //t(sec)=(FRAME/BOUND+MINT)*N = (10/115200+0.00001)*100 = 19 мс
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

void sendTimeUart(void)
{
  sprintf((char *)str, "time: %d.%d.%d\r\n", RTC_Time.Hours, RTC_Time.Minutes, RTC_Time.Seconds);
  sendUART((uint8_t *)str);
}

void sendAsciiGit(void)
{
  sendUART(asciiGit);
}
