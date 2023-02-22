#include "main.h"
#include "driverNixeTube.h"

const uint8_t voidPos = 10;

static void setDecoderNumber(uint8_t dec0, uint8_t dec1, uint8_t dec2, uint8_t dec3) 
{
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5,(GPIO_PinState) dec0);
  HAL_GPIO_WritePin(D12_GPIO_Port, D12_Pin, (GPIO_PinState) dec1);
  HAL_GPIO_WritePin(D11_GPIO_Port, D11_Pin, (GPIO_PinState) dec2);
  HAL_GPIO_WritePin(D10_GPIO_Port, D10_Pin, (GPIO_PinState) dec3);
}

static void setDecoderPosition(uint8_t dec0, uint8_t dec1, uint8_t dec2, uint8_t dec3) 
{
  HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, (GPIO_PinState) dec0);
  HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, (GPIO_PinState) dec1);
  HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, (GPIO_PinState) dec2);
  HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, (GPIO_PinState) dec3);
}

static void setNumber(uint8_t number)
{
  switch(number)
  {
    case 0: 
      setDecoderNumber(0, 0, 0, 0);
	  break;
	case 1:
      setDecoderNumber(1, 0, 0, 0);				
	  break;
	case 2: 
      setDecoderNumber(0, 1, 0, 0);
	  break;
	case 3:
      setDecoderNumber(1, 1, 0, 0);				
	  break;
	case 4: 
      setDecoderNumber(0, 0, 1, 0);
	  break;
	case 5: 
      setDecoderNumber(1, 0, 1, 0);
	  break;
	case 6: 
      setDecoderNumber(0, 1, 1, 0);
	  break;
	case 7: 
      setDecoderNumber(1, 1, 1, 0);
	  break;
	case 8:
      setDecoderNumber(0, 0, 0, 1);				
	  break;
	case 9: 
      setDecoderNumber(1, 0, 0, 1);
	  break;		
  }
}

static void setPosition(uint8_t position)
{
  switch(position)
  {
    case 0: 
      setDecoderPosition(1, 0, 0, 0);
	  break;
	case 1:
      setDecoderPosition(0, 1, 0, 0);		
	  break;
	case 2: 
      setDecoderPosition(0, 0, 1, 0);
	  break;
	case 3:
      setDecoderPosition(0, 0, 0, 1);				
	  break;
    case voidPos:
      setDecoderPosition(0, 0, 0, 0);
      break;
  }
}

void setVoidPosition(void)
{
  setPosition(voidPos);	
}

void setValue(uint8_t number, uint8_t position)          // функция вывода числа на индикатор
{
  setPosition(position);
  setNumber(number);
}
