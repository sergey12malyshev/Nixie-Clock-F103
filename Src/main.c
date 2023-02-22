/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdbool.h> 
#include "driverNixeTube.h"
#include "smooth.h"
#include "ds18b20.h"


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
RTC_HandleTypeDef hrtc;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

RTC_DateTypeDef RTC_Date;                     
RTC_TimeTypeDef RTC_Time;  

bool flag, flag2 = false;

bool setHoursButton = false;
bool setMinitButton = false;
bool timeSetButton = false;
extern uint32_t time_exti3_irq;
extern uint32_t time_exti15_irq; 
const uint8_t antiChatter_ms = 45; // https://istarik.ru/blog/stm32/148.html

uint8_t hour, minit, secund;

const uint8_t hello_clock []= "Hello Clock!\r\n";
char str1[30];

float temper;
uint8_t dt[8];
uint16_t raw_temper;

const uint8_t softWare_version = 1;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_RTC_Init(void);
/* USER CODE BEGIN PFP */
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void time_out(void)
{
  setValue(hour / 10, 0);
  DelayMicro(500);
  setValue(hour % 10, 1);
  DelayMicro(500);	
  setValue(minit / 10, 2);
  DelayMicro(500);
  setValue(minit % 10, 3);
  DelayMicro(500);	
}

void temper_out(void)   // выполняеться за 2 мс
{
  int temper_int = temper * 100;	
  setValue(temper_int/1000, 0);
  DelayMicro(500);
  setValue((temper_int/100)%10, 1);
  DelayMicro(500);	
  setValue((temper_int/10)%10, 2);
  DelayMicro(500);
#if 0
  setValue(temper_int%10,3);
#else
  setVoidPosition();  
#endif
  DelayMicro(500);
	
}

static void timeDataOutput(void)  
{
  flag2 = false;
  if (flag == false)   // 200-250 мС https://habr.com/ru/post/431868/
  {
    smooth_transition_time();
	  flag = true;
  }
  else
  {
    temper_out();
  }	
}

static void tempDataOutput(void)  
{
  flag = false;
  if (flag2 == false)   // 200-250 мС https://habr.com/ru/post/431868/
  {
    smooth_transition_temp();
	  flag2 = true;
  }
  else time_out();
}

static void checkButtonTemp(void)  
{
  uint16_t timeDelay = 950;

  if((HAL_GetTick() - time_exti15_irq) > antiChatter_ms)
  {
    if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15)== 0) 
    {
      smooth_transition_time();
	    while (--timeDelay)	temper_out();
      smooth_transition_temp();
    }

    timeSetButton = false;
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_15); 
    NVIC_ClearPendingIRQ(EXTI15_10_IRQn); 
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);  
  } 
}

static void checkButtonSetHours(void)  
{
  if((HAL_GetTick() - time_exti3_irq) > antiChatter_ms)
  {
    if ((RTC_Time.Hours < 24)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)== 0))
    {
      RTC_Time.Hours++;
      HAL_RTC_SetTime(&hrtc, &RTC_Time, RTC_FORMAT_BIN);
    }
  
    setHoursButton = false;	
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_3); 
    NVIC_ClearPendingIRQ(EXTI3_IRQn); 
    HAL_NVIC_EnableIRQ(EXTI3_IRQn);  
  } 
}

static void checkButtonSetMinutes(void)  
{
  if((HAL_GetTick() - time_exti15_irq) > antiChatter_ms)
  {
    if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14)== 0)
    {
      if ((RTC_Time.Minutes < 59))
      {
        RTC_Time.Minutes++;
        HAL_RTC_SetTime(&hrtc, &RTC_Time, RTC_FORMAT_BIN);
      }
      else
      {
        RTC_Time.Minutes = 0;
	      HAL_RTC_SetTime(&hrtc, &RTC_Time, RTC_FORMAT_BIN);
      }
    } 
  
    setMinitButton = false;
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_14);  // очищаем бит EXTI_PR
    NVIC_ClearPendingIRQ(EXTI15_10_IRQn);   // очищаем бит NVIC_ICPRx
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);     // включаем внешнее прерывание
  }
}

static void read_DS18b20_process(void)
{
  static uint16_t ms_4;

	if (ms_4 == 1)
	{
		ds18b20_MeasureTemperCmd(SKIP_ROM, 0);
	}
	
	if (ms_4 == 600)
	{
		ds18b20_ReadStratcpad(SKIP_ROM, dt, 0);
		raw_temper = ((uint16_t)dt[1] << 8)|dt[0];
		temper = ds18b20_Convert(raw_temper);
	}
	if (ms_4 == 800)
  {
    ms_4 = 0;
  }
  ms_4++;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	uint8_t status;

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_RTC_Init();
  /* USER CODE BEGIN 2 */
	
  HAL_UART_Transmit(&huart1, (uint8_t*)hello_clock, 14, 1000);
	
  port_init();
  status = ds18b20_init(SKIP_ROM);
  sprintf(str1,"Init Status: %d\r\n",status);
  HAL_UART_Transmit(&huart1, (uint8_t*)str1, strlen(str1), 0x200);
	
  HAL_RTC_GetTime(&hrtc, &RTC_Time, RTC_FORMAT_BIN);
  hour = RTC_Time.Hours;
  minit = RTC_Time.Minutes;
  secund = RTC_Time.Seconds;
		
  ds18b20_MeasureTemperCmd(SKIP_ROM, 0);
  HAL_Delay(750);
  ds18b20_ReadStratcpad(SKIP_ROM, dt, 0);
  raw_temper = ((uint16_t)dt[1]<<8)|dt[0];
  temper = ds18b20_Convert(raw_temper);
								
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
/* 
*  Внимание!! при генерации кода в кубе - стирается коментирование в инициалзации  MX_RTC_Init() 
*  - для работы необходимо закомментировать установку времени и даты - для сохранения данных при потере питания
*/		
#if DATE
  HAL_RTC_GetDate(&hrtc,&RTC_Date,RTC_FORMAT_BIN);
#endif
  HAL_RTC_GetTime(&hrtc,&RTC_Time,RTC_FORMAT_BIN);
 	
  hour = RTC_Time.Hours;
  minit = RTC_Time.Minutes;
  secund = RTC_Time.Seconds;
		
  if (((RTC_Time.Seconds > 0)&&(RTC_Time.Seconds < 5))||((RTC_Time.Seconds > 20) \
  &&(RTC_Time.Seconds < 25))||((RTC_Time.Seconds > 40)&&(RTC_Time.Seconds < 45)))  
  {	
    timeDataOutput();  
  }
  else                        
  {
    tempDataOutput();  
  }
				
  if (timeSetButton == true)  // показ температуры
  { 
    checkButtonTemp();  
  }	
  if (setMinitButton == true) // установка минут
  { 
    checkButtonSetMinutes();
  }
  if (setHoursButton == true)  // установка часов
  { 
     checkButtonSetHours();
  }
			
	/* Чтение датчика температуры происходит три раза в секунду */		
  if (((RTC_Time.Seconds > 58)&&(RTC_Time.Seconds <= 0))||((RTC_Time.Seconds > 17) \
		&&(RTC_Time.Seconds < 20))||((RTC_Time.Seconds > 37)&&(RTC_Time.Seconds < 40)))  
  {
    read_DS18b20_process();
  }	
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */
  /*
  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef DateToUpdate = {0};
  */
  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */
  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
  hrtc.Init.OutPut = RTC_OUTPUTSOURCE_ALARM;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */
    
  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
 /*sTime.Hours = 0x12;
  sTime.Minutes = 0x12;
  sTime.Seconds = 0x0;

  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  DateToUpdate.WeekDay = RTC_WEEKDAY_MONDAY;
  DateToUpdate.Month = RTC_MONTH_JANUARY;
  DateToUpdate.Date = 0x1;
  DateToUpdate.Year = 0x0;

  if (HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
	*/
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, D13_Pin|D12_Pin|D11_Pin|D7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, D6_Pin|D5_Pin|D4_Pin|D10_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : D13_Pin D12_Pin D11_Pin D7_Pin */
  GPIO_InitStruct.Pin = D13_Pin|D12_Pin|D11_Pin|D7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : D6_Pin D5_Pin D4_Pin D10_Pin */
  GPIO_InitStruct.Pin = D6_Pin|D5_Pin|D4_Pin|D10_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : ds18b20_Pin */
  GPIO_InitStruct.Pin = ds18b20_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(ds18b20_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : D8_Pin D2_Pin D3_Pin */
  GPIO_InitStruct.Pin = D8_Pin|D2_Pin|D3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
