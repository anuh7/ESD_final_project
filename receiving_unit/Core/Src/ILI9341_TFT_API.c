/*
 * Filename: IL9341_TFT_API.c
 * Created on: Nov 26, 2022
 * Author: Shashank and Anuhya
 * Description: This C file contains the function definitions of TFT graphic APIs
 * Reference: https://www.micropeta.com/video37
 */

#include <IL9341_TFT_Drivers.h>
#include <ILI9341_TFT_API.h>

/************************************ To generate small delay **********************************/
void DelayUs(volatile uint32_t us)
{
	us *= (SystemCoreClock / 1000000);
	while (us--);
}

/****************************************To generate X******************************************/
void ILI9341_DrawX(uint16_t X, uint16_t Y, uint16_t length, uint16_t color)
{
	int j=0;
	for(int i=0;i<length;i++)
	{
		ILI9341_DrawPixel(X+i,Y+i,color);
	}
	for(int i=length-1;i>=0;i--)
	{
		ILI9341_DrawPixel(X+i,Y+j,color);
		j++;
	}
}

/****************************************To generate diagonals*********************************/
void ILI9341_diag(uint16_t X, uint16_t Y, uint16_t length, uint16_t diag, uint16_t color)
{
	if(diag==1)
	{
		for(int i=0;i<length;i++)
			ILI9341_DrawPixel(X+i,Y+i,color);
	}
	else if (diag==2)
	{
		for(int i=0;i<length;i++)
			ILI9341_DrawPixel(X+i,Y-i,color);
	}
}

/***********************************To generate hollow circle**********************************/
void ILI9341_DrawHollowCircle(uint16_t X, uint16_t Y, uint16_t radius, uint16_t color)
{
	int x = radius-1;
	int y = 0;
	int dx = 1;
	int dy = 1;
	int err = dx - (radius << 1);

	while (x >= y)
	{
		ILI9341_DrawPixel(X + x, Y + y, color);
		ILI9341_DrawPixel(X + y, Y + x, color);
		ILI9341_DrawPixel(X - y, Y + x, color);
		ILI9341_DrawPixel(X - x, Y + y, color);
		ILI9341_DrawPixel(X - x, Y - y, color);
		ILI9341_DrawPixel(X - y, Y - x, color);
		ILI9341_DrawPixel(X + y, Y - x, color);
		ILI9341_DrawPixel(X + x, Y - y, color);

		if (err <= 0)
		{
			y++;
			err += dy;
			dy += 2;
		}

		if (err > 0)
		{
			x--;
			dx += 2;
			err += (-radius << 1) + dx;
		}
	}
}


/********************************To generate single character**********************************
* Parameter Passed: ch: Character, font[]: Font desired, X: x coordinate where character is to
* placed, Y: y coordinate, color: Desired color of the character, bgcolor: Background color
* Parameter returned: None
* ********************************************************************************************/
void ILI9341_DrawChar(char ch, const uint8_t font[], uint16_t X, uint16_t Y, uint16_t color, uint16_t bgcolor)
{
	if ((ch < 31) || (ch > 127)) return;

	uint8_t fOffset, fWidth, fHeight, fBPL;
	uint8_t *tempChar;

	fOffset = font[0];
	fWidth = font[1];
	fHeight = font[2];
	fBPL = font[3];

	tempChar = (uint8_t*)&font[((ch - 0x20) * fOffset) + 4]; /* Current Character = Meta + (Character Index * Offset) */

	/* Clear background first */
	ILI9341_DrawRectangle(X, Y, fWidth, fHeight, bgcolor);

	for (int j=0; j < fHeight; j++)
	{
		for (int i=0; i < fWidth; i++)
		{
			uint8_t z =  tempChar[fBPL * i + ((j & 0xF8) >> 3) + 1]; /* (j & 0xF8) >> 3, increase one by 8-bits */
			uint8_t b = 1 << (j & 0x07);
			if (( z & b ) != 0x00)
			{
				ILI9341_DrawPixel(X+i, Y+j, color);
			}
		}
	}
}

/********************************To generate text***********************************************/
void ILI9341_DrawText(const char* str, const uint8_t font[], uint16_t X, uint16_t Y, uint16_t color, uint16_t bgcolor)
{
	uint8_t charWidth;			/* Width of character */
	uint8_t fOffset = font[0];	/* Offset of character */
	uint8_t fWidth = font[1];	/* Width of font */

	while (*str)
	{
		ILI9341_DrawChar(*str, font, X, Y, color, bgcolor);

		/* Check character width and calculate proper position */
		uint8_t *tempChar = (uint8_t*)&font[((*str - 0x20) * fOffset) + 4];
		charWidth = tempChar[0];

		if(charWidth + 2 < fWidth)
		{
			/* If character width is smaller than font width */
			X += (charWidth + 2);
		}
		else
		{
			X += fWidth;
		}

		str++;
	}
}
