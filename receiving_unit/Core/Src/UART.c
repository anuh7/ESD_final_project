/*
 * Filename: UART.c
 * Created on: Nov 25, 2022
 * Author: Shashank and Anuhya
 * Description: This C file contains the UART interfacing functions
 * Reference: None
 */

#include <SPI_DMA.h>
#include <UART.h>

/*****************************************UART2 initialization*********************************/
void MX_USART2_UART_Init(void)
{
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 9600;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart2) != HAL_OK)
	{
		Error_Handler();
	}
}

/********************************UART2 receive callback function********************************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == huart2.Instance)
	{
		HAL_UART_Receive_IT(&huart2, RX_BUFFER, BUFFER_LEN);
	}
}


