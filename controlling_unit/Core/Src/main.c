/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Code for the controlling unit (STM32). The pushbuttons on the gaming console
  * 				  are polled continuously and checked for external interrupt. This information is
  * 				  transmitted to the receiving unit (STM32) through UART via HC-05 (bluetooth module).
  * 				  The external interrupt handler is defined in this file.
  * @authors		: Anuhya Kuraparthy & Shashank
  ******************************************************************************
*/


/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;
char transmit1[]="A";				/* transmit a character corresponding to the pushbutton pressed */
char transmit2[]="B";
char transmit3[]="C";
char transmit4[]="D";
char transmit5[]="E";
char transmit6[]="F";
char transmit7[]="G";
char transmit8[]="H";
char transmit9[]="I";
char transmit10[]="X";
char transmit11[]="O";

uint32_t previousMillis0 = 0;		/* variables for software debouncing */
uint32_t previousMillis1 = 0;
uint32_t previousMillis2 = 0;
uint32_t previousMillis3 = 0;
uint32_t previousMillis4 = 0;
uint32_t previousMillis5 = 0;
uint32_t previousMillis6 = 0;
uint32_t currentMillis = 0;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);


/**
  * @brief  The application entry point.
  * @return int
  */
int main(void)
{
  /* MCU Configuration--------------------------------------------------------*/
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();

  /* Infinite loop */
  while (1)
  {
	  if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == 1)						/* PortB-Pin0 initialized as GPIO input pin */
	  {
		  HAL_UART_Transmit(&huart2, (uint8_t *) transmit1, 1, 0);
	  }

	  else if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2) == 1)					/* GPIO input polling*/
	  {
			  HAL_UART_Transmit(&huart2, (uint8_t *) transmit2, 1, 0);
	  }

	  else if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == 1)
	  {
			  HAL_UART_Transmit(&huart2, (uint8_t *) transmit3, 1, 0);	/* if pressed, transmit character through UART via HC-05 */
	  }

	  else if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4) == 1)
	  {
			  HAL_UART_Transmit(&huart2, (uint8_t *) transmit4, 1, 0);
	  }

	  else if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5) == 1)
	  {
			  HAL_UART_Transmit(&huart2, (uint8_t *) transmit10, 1, 0);
	  }

	  else if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_10) == 1)
	  {
			  HAL_UART_Transmit(&huart2, (uint8_t *) transmit11, 1, 0);
	  }
  }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 80;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;							/* UART baud rate setting */
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
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
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pins : PC0 PC1 PC2 PC3 PC4 */
	GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                        |GPIO_PIN_4;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;					/* interrupt on rising edge */
	GPIO_InitStruct.Pull = GPIO_NOPULL;							/* no internal pull up/down registers */
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/*Configure GPIO pins : PC5 PC10 */
	GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_10;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;						/* initialized as GPIO input */
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/*Configure GPIO pins : PB0 PB2 PB3 PB4 */
	GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/* EXTI interrupt init*/
	HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);						/*  enabling external interrupts */

	HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI1_IRQn);

	HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI2_IRQn);

	HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI3_IRQn);

	HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI4_IRQn);

}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	currentMillis = HAL_GetTick();							/* gets tick value since starting of program in milliseconds */

	if(GPIO_Pin == GPIO_PIN_0 && (currentMillis - previousMillis0 > 300))			/*  software debouncing */
	  {
	  HAL_UART_Transmit(&huart2, (uint8_t *) transmit5, 1, 0);				/*  if pressed, transmit character through UART via HC-05 */
	  previousMillis0 = currentMillis;
	  }

	if(GPIO_Pin == GPIO_PIN_1 && (currentMillis - previousMillis1 > 300))
	  {
	  HAL_UART_Transmit(&huart2, (uint8_t *) transmit6, 1, 0);
	  previousMillis1 = currentMillis;
	  }

	if(GPIO_Pin == GPIO_PIN_2 && (currentMillis - previousMillis2 > 300))
	   {
	   HAL_UART_Transmit(&huart2, (uint8_t *) transmit7, 1, 0);
	   previousMillis2 = currentMillis;
	   }

	if(GPIO_Pin == GPIO_PIN_3 && (currentMillis - previousMillis3 > 300))
		 {
		 HAL_UART_Transmit(&huart2, (uint8_t *) transmit8, 1, 0);
		 previousMillis3 = currentMillis;
		 }

	if(GPIO_Pin == GPIO_PIN_4 && (currentMillis - previousMillis4 > 300))
		 {
		 HAL_UART_Transmit(&huart2, (uint8_t *) transmit9, 1, 0);
		 previousMillis4 = currentMillis;
		 }
}



/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
