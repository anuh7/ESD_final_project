/*
 * Filename: SPI_DMA.c
 * Created on: Nov 25, 2022
 * Author: Shashank and Anuhya
 * Description: This C file contains the function definitions of SPI functions
 * Reference: None
 */

#include <SPI_DMA.h>

/*********************************SPI Initialization*******************************************/
void MX_SPI1_Init(void)
{
	/* SPI1 parameter configuration*/
	hspi1.Instance = SPI1;
	hspi1.Init.Mode = SPI_MODE_MASTER;
	hspi1.Init.Direction = SPI_DIRECTION_2LINES;
	hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi1.Init.NSS = SPI_NSS_SOFT;
	hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
	hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi1.Init.CRCPolynomial = 10;
	if (HAL_SPI_Init(&hspi1) != HAL_OK)
	{
		Error_Handler();
	}
}

/*************************HAL SPI Transmit Callback function**********************************
* Parameter Passed: hspi: SPI structure instance which is used to transmit data
* Parameter returned: None
* ********************************************************************************************/
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
  /* Deselect when Tx Complete */
  if(hspi == HSPI_INSTANCE)
  {
	  HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
  }
}

/*************************HAL SPI Transmit single data function******************************/
void SPI_Tx(uint8_t data)
{
	while(!__HAL_SPI_GET_FLAG(HSPI_INSTANCE, SPI_FLAG_TXE));
	HAL_SPI_Transmit_DMA(HSPI_INSTANCE, &data, 1);
}

/*************************HAL SPI Transmit buffer function***********************************/
void SPI_TxBuffer(uint8_t *buffer, uint16_t len)
{
	while(!__HAL_SPI_GET_FLAG(HSPI_INSTANCE, SPI_FLAG_TXE));
	HAL_SPI_Transmit_DMA(HSPI_INSTANCE, buffer, len);
}

/******************************Enable DMA controller clock**********************************/
void MX_DMA_Init(void)
{
	/* DMA controller clock enable */
	__HAL_RCC_DMA2_CLK_ENABLE();

	/* DMA interrupt init */
	/* DMA2_Stream2_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA2_Stream2_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA2_Stream2_IRQn);
}

/***************************************Error Handler***************************************/
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



