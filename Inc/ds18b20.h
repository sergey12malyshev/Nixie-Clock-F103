#ifndef DS18B20_H_
#define DS18B20_H_

#include "stm32f1xx_hal.h"
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define SKIP_ROM            0u
#define NO_SKIP_ROM         1u

#define RESOLUTION_9BIT     0x1F
#define RESOLUTION_10BIT    0x3F
#define RESOLUTION_11BIT    0x5F
#define RESOLUTION_12BIT    0x7F


__STATIC_INLINE void DelayMicro(__IO uint32_t micros)
{
  micros *= (SystemCoreClock / 1000000) / 9;
  /* Wait till done */
  while (micros--);
}

void port_init(void);
uint8_t ds18b20_init(uint8_t mode);
void ds18b20_MeasureTemperCmd(uint8_t mode, uint8_t DevNum);
void ds18b20_ReadStratcpad(uint8_t mode, uint8_t *Data, uint8_t DevNum);
uint8_t ds18b20_GetSign(uint16_t dt);
float ds18b20_Convert(uint16_t dt);

#endif /* DS18B20_H_ */
