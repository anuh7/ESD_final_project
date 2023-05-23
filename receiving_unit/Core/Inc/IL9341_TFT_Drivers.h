/*
 * Filename: IL9341_TFT_Drivers.h
 * Created on: Nov 26, 2022
 * Author: Shashank and Anuhya
 * Description: This H file contains the function declarations of TFT graphic drivers
 * Reference: https://www.micropeta.com/video37
 */

#ifndef INC_IL9341_TFT_DRIVERS_H_
#define INC_IL9341_TFT_DRIVERS_H_

#include "stm32f4xx_hal.h"


#define ILI9341_SCREEN_HEIGHT 	240
#define ILI9341_SCREEN_WIDTH 	320

/* PIN Configuration */
#define LCD_DC_PORT				GPIOB
#define LCD_DC_PIN				GPIO_PIN_0
#define	LCD_RST_PORT			GPIOB
#define	LCD_RST_PIN				GPIO_PIN_1

/*Color options*/
#define BURST_MAX_SIZE 			500
#define BLACK      				0x0000
#define WHITE       			0xFFFF

/*For user fill screen*/
#define USER_MSG_BOUND          270
#define USER_MSG_SPACE          50

/*Screen rotation options*/
#define SCREEN_HORIZONTAL		1
#define SCREEN_VERTICAL			2


/*
 * To write command to the TFT
 * Parameter Passed: cmd: Command
 * Parameter returned: None
 */
void ILI9341_WriteCommand(uint8_t cmd);

/*
 * To write single data to the TFT
 * Parameter Passed: data: The single data to be written
 * Parameter returned: None
 */
void ILI9341_WriteData(uint8_t data);

/*
 * To write buffer to the TFT
 * Parameter Passed: data: buffer: Buffer to be written
 * len: Length of buffer to be transmitted
 * Parameter returned: None
 */
void ILI9341_WriteBuffer(uint8_t *buffer, uint16_t len);

/*
 * To set address in the TFT
 * Parameter Passed: data: x1: starting x coordinate
 * y1: starting y coordinate, x2: ending x coordinate
 * y2: ending y coordinate
 * Parameter returned: None
 */
void ILI9341_SetAddress(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

/*
 * To reset the TFT
 * Parameter Passed: data: None
 * Parameter returned: None
 */
void ILI9341_Reset(void);

/*
 * To enable the TFT
 * Parameter Passed: data: None
 * Parameter returned: None
 */
void ILI9341_Enable(void);

/*
 * Initialize the TFT
 * Parameter Passed: data: None
 * Parameter returned: None
 */
void ILI9341_Init(void);

/*
 * Rotate the TFT screen
 * Parameter Passed: data: rotation: To rotate either in horizontal or vertical
 * Parameter returned: None
 */
void ILI9341_SetRotation(uint8_t rotation);

/*
 * To fill color for single data
 * Parameter Passed: data: color: The color to be used
 * Parameter returned: None
 */
void ILI9341_DrawColor(uint16_t color);

/*
 * To fill color for buffer of data
 * Parameter Passed: data: color: The color to be used
 * Parameter returned: None
 */
void ILI9341_DrawColorBurst(uint16_t color, uint32_t size);

/*
 * To fill the entire screen with color
 * Parameter Passed: data: color: The color to be filled with
 * Parameter returned: None
 */
void ILI9341_FillScreen(uint16_t color);

/*
 * To fill portion of the screen with color
 * Parameter Passed: data: color: The color to be filled with
 * Parameter returned: None
 */
void ILI9341_Usermsg(uint16_t color);

/*
 * To write values to pixels
 * Parameter Passed: data: x: pixel's x coordinate
 * y: pixel's y coordinate
 * color: The color of the pixel
 * Parameter returned: None
 */
void ILI9341_DrawPixel(uint16_t x,uint16_t y,uint16_t color);

/*
 * To draw rectangle
 * Parameter Passed: data: x: starting x coordinate
 * y: starting y coordinate
 * width: Width of the rectangle needed
 * height: Height of the rectangle needed
 * color: The color of the rectangle
 * Parameter returned: None
 */
void ILI9341_DrawRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color);

/*
 * To draw horizontal line
 * Parameter Passed: data: x: starting x coordinate
 * y: starting y coordinate
 * width: length of the line needed
 * color: The color of the line
 * Parameter returned: None
 */
void ILI9341_DrawHLine(uint16_t x, uint16_t y, uint16_t width, uint16_t color);

/*
 * To draw vertical line
 * Parameter Passed: data: x: starting x coordinate
 * y: starting y coordinate
 * height: length of the line needed
 * color: The color of the line
 * Parameter returned: None
 */
void ILI9341_DrawVLine(uint16_t x, uint16_t y, uint16_t height, uint16_t color);

#endif /* INC_IL9341_TFT_DRIVERS_H_ */
