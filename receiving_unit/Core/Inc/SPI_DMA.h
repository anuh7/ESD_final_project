/*
 * Filename: SPI_DMA.h
 * Created on: Nov 25, 2022
 * Author: Shashank and Anuhya
 * Description: This H file contains the function declarations of SPI functions
 * Reference: None
 */

#ifndef INC_SPI_DMA_H_
#define INC_SPI_DMA_H_

#include "stm32f4xx_hal.h"

//HAL SPI instance
#define HSPI_INSTANCE			&hspi1

//CS Pins for the TFT LCD
#define LCD_CS_PORT				GPIOB
#define LCD_CS_PIN				GPIO_PIN_10

extern SPI_HandleTypeDef hspi1;

/*
 * SPI Initialization
 * Parameter Passed: None
 * Parameter returned: None
 */
void MX_SPI1_Init(void);

/*
 * To transmit single data
 * Parameter Passed: data: Single data to be transmitted
 * Parameter returned: None
 */
void SPI_Tx(uint8_t data);

/*
 * To transmit buffer
 * Parameter Passed: buffer: buffer to be transmitted
 * len: Length in the buffer to transmit
 * Parameter returned: None
 */
void SPI_TxBuffer(uint8_t *buffer, uint16_t len);

/*
 * DMA Initialization
 * Parameter Passed: None
 * Parameter returned: None
 */
void MX_DMA_Init(void);

/*
 * Error Handler
 * Parameter Passed: None
 * Parameter returned: None
 */
void Error_Handler(void);

#endif /* INC_SPI_DMA_H_ */
