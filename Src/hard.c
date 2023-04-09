#include "main.h"
#include "hard.h"
#include "UART.h"

void heartbeatLedToggle(void)
{
  HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
}

void heartbeatDrive(uint8_t secund_loc)
{
  static uint8_t secundTmp;
  
  if(secund_loc != secundTmp)
  {
    secundTmp = secund_loc;
#if HEARTBEAT_EN
    heartbeatLedToggle();
    sendUART("Toggle");
#endif
  }
}
