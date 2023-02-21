#include "main.h"
#include "driverNixeTube.h"

static void setNumber(uint8_t number)
{
  switch(number)
  {
    case 0: 
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(D12_GPIO_Port, D12_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(D11_GPIO_Port, D11_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(D10_GPIO_Port, D10_Pin, GPIO_PIN_RESET);
	  break;
	case 1:
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(D12_GPIO_Port, D12_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(D11_GPIO_Port, D11_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(D10_GPIO_Port, D10_Pin, GPIO_PIN_RESET);				
	  break;
	case 2: 
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(D12_GPIO_Port, D12_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(D11_GPIO_Port, D11_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(D10_GPIO_Port, D10_Pin, GPIO_PIN_RESET);
	  break;
	case 3:
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(D12_GPIO_Port, D12_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(D11_GPIO_Port, D11_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(D10_GPIO_Port, D10_Pin, GPIO_PIN_RESET);				
	  break;
	case 4: 
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(D12_GPIO_Port, D12_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(D11_GPIO_Port, D11_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(D10_GPIO_Port, D10_Pin, GPIO_PIN_RESET);
	  break;
	case 5: 
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(D12_GPIO_Port, D12_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(D11_GPIO_Port, D11_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(D10_GPIO_Port, D10_Pin, GPIO_PIN_RESET);
	  break;
	case 6: 
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(D12_GPIO_Port, D12_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(D11_GPIO_Port, D11_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(D10_GPIO_Port, D10_Pin, GPIO_PIN_RESET);
	  break;
	case 7: 
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(D12_GPIO_Port, D12_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(D11_GPIO_Port, D11_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(D10_GPIO_Port, D10_Pin, GPIO_PIN_RESET);;
	  break;
	case 8:
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(D12_GPIO_Port, D12_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(D11_GPIO_Port, D11_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(D10_GPIO_Port, D10_Pin, GPIO_PIN_SET);				
	  break;
	case 9: 
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(D12_GPIO_Port, D12_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(D11_GPIO_Port, D11_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(D10_GPIO_Port, D10_Pin, GPIO_PIN_SET);
	  break;		
  }
}

static void setPosition(uint8_t position)
{
  switch(position)
  {
    case 0: 
	  HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, GPIO_PIN_RESET);
	  break;
	case 1:
	  HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, GPIO_PIN_RESET);		
	  break;
	case 2: 
	  HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, GPIO_PIN_RESET);
	  break;
	case 3:
	  HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, GPIO_PIN_SET);				
	  break;
  }
}

void setVoidPosition(void)
{
  HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, GPIO_PIN_RESET);	
}

void setValue(uint8_t number, uint8_t position)          // функция вывода числа на индикатор
{
  setPosition(position);
  setNumber(number);
}
