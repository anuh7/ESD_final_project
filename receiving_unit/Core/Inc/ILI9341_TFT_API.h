/*
 * Filename: IL9341_TFT_API.h
 * Created on: Nov 26, 2022
 * Author: Shashank and Anuhya
 * Description: This H file contains the function declarations of TFT graphic APIs
 * Reference: https://www.micropeta.com/video37
 */

#ifndef INC_ILI9341_TFT_API_H_
#define INC_ILI9341_TFT_API_H_

#include "stm32f4xx_hal.h"
#include "fonts.h"

/*
 * To generate X shape
 * Parameter Passed: X: x coordinate where X will start
 * Y: y coordinate, color: Desired color of X
 * Parameter returned: None
 */
void ILI9341_DrawX(uint16_t X, uint16_t Y, uint16_t length, uint16_t color);

/*
 * To generate diagonal shape
 * Parameter Passed: X: x coordinate where diagonal will start
 * to start, Y: y coordinate, color: Desired color of the diagonal
 * Parameter returned: None
 */
void ILI9341_diag(uint16_t X, uint16_t Y, uint16_t length, uint16_t diag, uint16_t color);

/*
 * To generate hollow circle
 * Parameter Passed: radius: Radius of the circle, X: x coordinate of center of circle
 * Y: y coordinate, color: Desired color of the circle, bgcolor: Background color
 * Parameter returned: None
 */
void ILI9341_DrawHollowCircle(uint16_t X, uint16_t Y, uint16_t radius, uint16_t color);

/*
 * To generate text
 * Parameter Passed: str: string to be displayed, font[]: Font desired, X: x coordinate where string needs
 * to start, Y: y coordinate, color: Desired color of the text, bgcolor: Background color
 * Parameter returned: None
 */
void ILI9341_DrawText(const char* str, const uint8_t font[], uint16_t X, uint16_t Y, uint16_t color, uint16_t bgcolor);

#endif /* INC_ILI9341_TFT_API_H_ */
