/**
 * @file raster.c
 * @author Academia Team
 * @brief Contains functions and macros designed to allow rasters to be
 * plotted to an area in memory for use by the Atari ST's monochrome screen.
 * 
 * @copyright Copyright Academia Team 2023
 */

#include <stdlib.h>
#include "raster.h"

void plot_px(UINT8 *base, int x, int y)
{
	if (x >= 0 && x < SCRN_LEN && y >= 0 && y < SCRN_HEIGHT)
	{
		*(base + y * SCRN_LEN_BYTES + (x >> DIV_SHIFT_BY_8))
		^= (UINT8)0x1 << 7 - (x & 7);
	}
}

void hline(UINT32 *base, int x1, int x2, int y)
{
	int minXLong;
	int maxXLong;
	int minPX;
	int maxPX;
	int index;

	UINT32 *line;

	if ((y >= 0 && y < SCRN_HEIGHT) && (x1 >= 0 || x2 >= 0) 
	     && (x1 < SCRN_LEN || x2 < SCRN_LEN))
	{
		line = base + (y * SCRN_LEN_LONG);
		fitXToScrn(x1);
		fitXToScrn(x2);

		if (x1 > x2)
		{
			swap(x1, x2);
		}

		minPX = x1;
		maxPX = x2;
		minXLong = (x1 >> DIV_SHIFT_BY_32);
		maxXLong = (x2 >> DIV_SHIFT_BY_32);
		line += minXLong;

		if (minXLong == maxXLong)
		{	
			*line |= ((0xFFFFFFFF >> (minPX & 31)) & 
					  (0xFFFFFFFF << (31 - (maxPX & 31))));
		}
		else
		{
			*line |= 0xFFFFFFFF >> (minPX & 31);

			for(index = 1; index < maxXLong - minXLong; index++)
			{
				*(line + index) = 0xFFFFFFFF;
			}

			*(line + index) |= 0xFFFFFFFF << 31 - (maxPX & 31);
		}
	}
}

void plot_rast32(UINT32 *base, int x, int y, int height, const UINT32 *bitmap, 
				 BOOL destructive, BOOL blackScreen)
{
	int bitmapEndY = y + height - 1;
	int currentRow;
	int modX;
	int numPxFromRight;
	UINT32 *scrnPlotPos;
	
	UINT32 clrMaskVal;
	UINT32 leftClrMaskVal;
	UINT32 rightClrMaskVal;
	UINT32 xorMaskVal;

	if (bitmapEndY > SCRN_MAX_Y)
	{
		bitmapEndY = SCRN_MAX_Y;
	}

	if (x >= RAST32_MIN_X && x < (SCRN_LEN)
	&& bitmapEndY >= 0 && y <= SCRN_MAX_Y 
	&& height > 0)
	{
		modX = (abs(x) & 31);
		scrnPlotPos = (x < 0) ? base : (base + (x >> DIV_SHIFT_BY_32));

		if (y > 0)
		{
			scrnPlotPos += y * SCRN_LEN_LONG;
		}
		if (y < 0)
		{
			bitmap += y * -1; 
			y = 0;
		}

		if (x < 0)
		{
			if (blackScreen && destructive)
			{
				clrMaskVal = 0xFFFFFFFF >> 32 + x;
				xorMaskVal = 0xFFFFFFFF << modX;

				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_LONG)
				{
					*scrnPlotPos = (*scrnPlotPos & clrMaskVal) | (
								   (*bitmap << modX) ^ xorMaskVal);
				}
			}
			else if (destructive)
			{
				clrMaskVal = 0xFFFFFFFF >> modX;

				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_LONG)
				{
					*scrnPlotPos = (*scrnPlotPos & clrMaskVal) |
								   (*bitmap << modX);
				}
			}
			else if (blackScreen)
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_LONG)
				{
					*scrnPlotPos ^= *bitmap << modX;
				}
			}
			else
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_LONG)
				{
					*scrnPlotPos |= *bitmap << modX;
				}
			}
		}
		else if (x > RAST32_MAX_VIS_X)
		{
			if (blackScreen && destructive)
			{
				clrMaskVal = 0xFFFFFFFF << (32 - modX);
				xorMaskVal = 0xFFFFFFFF >> modX;

				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_LONG)
				{
					*scrnPlotPos = (*scrnPlotPos & clrMaskVal) |
								   ((*bitmap >> modX) ^ xorMaskVal);
				}
			}
			else if (destructive)
			{
				clrMaskVal = 0xFFFFFFFF << (32 - modX);

				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_LONG)
				{
					*scrnPlotPos = (*scrnPlotPos & clrMaskVal) |
								   (*bitmap >> modX);
				}
			}
			else if (blackScreen)
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_LONG)
				{
					*scrnPlotPos ^= *bitmap >> modX;
				}
			}
			else
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_LONG)
				{
					*scrnPlotPos |= *bitmap >> modX;
				}
			}
		}
		else if (modX == 0)
		{
			if (blackScreen && destructive)
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_LONG)
				{
					*scrnPlotPos = (*bitmap ^ 0xFFFFFFFF);
				}
			}
			else if (destructive)
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_LONG)
				{
					*scrnPlotPos = *bitmap;
				}
			}
			else if (blackScreen)
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_LONG)
				{
					*scrnPlotPos ^= *bitmap;
				}
			}
			else
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_LONG)
				{
					*scrnPlotPos |= *bitmap;
				}
			}
		}
		else
		{
			numPxFromRight = 32 - modX;

			if (blackScreen && destructive)
			{
				leftClrMaskVal  = 0xFFFFFFFF << numPxFromRight;
				rightClrMaskVal = 0xFFFFFFFF >> modX;

				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_LONG)
				{
					*scrnPlotPos = (*scrnPlotPos & leftClrMaskVal) |
								   ((*bitmap >> modX) ^ rightClrMaskVal);

					*(scrnPlotPos + 1) = (*(scrnPlotPos + 1) &
										 rightClrMaskVal) |
										 ((*bitmap << numPxFromRight) ^
										 leftClrMaskVal);
				}
			}
			else if (destructive)
			{
				leftClrMaskVal  = 0xFFFFFFFF << numPxFromRight;
				rightClrMaskVal = 0xFFFFFFFF >> modX;

				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_LONG)
				{
					*scrnPlotPos = (*scrnPlotPos & leftClrMaskVal) |
								   (*bitmap >> modX);

					*(scrnPlotPos + 1) = (*(scrnPlotPos + 1) &
										  rightClrMaskVal) | (*bitmap <<
										  numPxFromRight);
				}
			}
			else if (blackScreen)
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_LONG)
				{
					*scrnPlotPos ^= *bitmap >> modX;
					*(scrnPlotPos + 1) ^= *bitmap << numPxFromRight;
				}
			}
			else
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_LONG)
				{
					*scrnPlotPos |= *bitmap >> modX;
					*(scrnPlotPos + 1) |= *bitmap << numPxFromRight;
				}
			}
		}
	}
}

void plot_alpha(UINT32 *base, int x, int y, int height, const UINT32 *bitmap)
{
	int bitmapEndY = y + height - 1;
	int currentRow;
	int modX;
	int numPxFromRight;
	UINT32 *scrnPlotPos;

	UINT32 clrMaskVal;
	UINT32 leftClrMaskVal;
	UINT32 rightClrMaskVal;

	if (bitmapEndY > SCRN_MAX_Y)
	{
		bitmapEndY = SCRN_MAX_Y;
	}

	if (x >= RAST32_MIN_X && x < (SCRN_LEN)
	&& bitmapEndY >= 0 && y <= SCRN_MAX_Y 
	&& height > 0)
	{
		modX = (abs(x) & 31);
		scrnPlotPos = (x < 0) ? base : (base + (x >> DIV_SHIFT_BY_32));

		if (y > 0)
		{
			scrnPlotPos += y * SCRN_LEN_LONG;
		}
		if (y < 0)
		{
			bitmap += y * -1; 
			y = 0;
		}

		if (x < 0)
		{
			clrMaskVal = 0xFFFFFFFF >> modX;

			for (currentRow = y; currentRow <= bitmapEndY;
				 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_LONG)
			{
				*scrnPlotPos &= (*scrnPlotPos & clrMaskVal) | (*bitmap << modX);
			}
		}
		else if (x > RAST32_MAX_VIS_X)
		{
			clrMaskVal = 0xFFFFFFFF << (32 - modX);

			for (currentRow = y; currentRow <= bitmapEndY;
				 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_LONG)
			{
				*scrnPlotPos &= (*scrnPlotPos & clrMaskVal) | (*bitmap >> modX);
			}
		}
		else if (modX == 0)
		{
			for (currentRow = y; currentRow <= bitmapEndY;
				 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_LONG)
			{
				*scrnPlotPos &= *(bitmap);
			}
		}
		else
		{
			numPxFromRight  = 32 - modX;
			leftClrMaskVal  = 0xFFFFFFFF << numPxFromRight;
			rightClrMaskVal = 0xFFFFFFFF >> modX;

			for (currentRow = y; currentRow <= bitmapEndY;
				 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_LONG)
			{
				*scrnPlotPos &= (*scrnPlotPos & leftClrMaskVal) |
								(*bitmap >> modX);
				*(scrnPlotPos + 1) &= (*(scrnPlotPos + 1) & rightClrMaskVal) |
									  (*bitmap << numPxFromRight);
			}
		}
	}
}

void plot_rast16(UINT16 *base, int x, int y, int height, const UINT16 *bitmap,
				 BOOL destructive, BOOL blackScreen)
{
	int bitmapEndY = y + height - 1;
	int currentRow;
	int modX;
	int numPxFromRight;
	UINT16 *scrnPlotPos;

	UINT16 clrMaskVal;
	UINT16 leftClrMaskVal;
	UINT16 rightClrMaskVal;
	UINT16 xorMaskVal;

	if (bitmapEndY > SCRN_MAX_Y)
	{
		bitmapEndY = SCRN_MAX_Y;
	}

	if (x >= RAST16_MIN_X && x < (SCRN_LEN)
	&& bitmapEndY >= 0 && y <= SCRN_MAX_Y 
	&& height > 0)
	{
		modX = (abs(x) & 15);
		scrnPlotPos = (x < 0) ? base : (base + (x >> DIV_SHIFT_BY_16));

		if (y > 0)
		{
			scrnPlotPos += y * SCRN_LEN_WORDS;
		}
		if (y < 0)
		{
			bitmap += y * -1; 
			y = 0;
		}

		if (x < 0)
		{
			if (blackScreen && destructive)
			{
				clrMaskVal = 0xFFFF >> 16 + x;
				xorMaskVal = 0xFFFF << modX;

				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_WORDS)
				{
					*scrnPlotPos = (*scrnPlotPos & clrMaskVal) | (
								   (*bitmap << modX) ^ xorMaskVal);
				}
			}
			else if (destructive)
			{
				clrMaskVal = 0xFFFF >> modX;

				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_WORDS)
				{
					*scrnPlotPos = (*scrnPlotPos & clrMaskVal) |
								   (*bitmap << modX);
				}
			}
			else if (blackScreen)
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_WORDS)
				{
					*scrnPlotPos ^= *bitmap << modX;
				}
			}
			else
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_WORDS)
				{
					*scrnPlotPos |= *bitmap << modX;
				}
			}
		}
		else if (x > RAST16_MAX_VIS_X)
		{
			if (blackScreen && destructive)
			{
				clrMaskVal = 0xFFFF << (16 - modX);
				xorMaskVal = 0xFFFF >> modX;

				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_WORDS)
				{
					*scrnPlotPos = (*scrnPlotPos & clrMaskVal) | (
								   (*bitmap >> modX) ^ xorMaskVal);
				}
			}
			else if (destructive)
			{
				clrMaskVal = 0xFFFF << (16 - modX);

				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_WORDS)
				{
					*scrnPlotPos = (*scrnPlotPos & clrMaskVal) |
								   (*bitmap >> modX);
				}
			}
			else if (blackScreen)
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_WORDS)
				{
					*scrnPlotPos ^= *bitmap >> modX;
				}
			} 
			else
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_WORDS)
				{
					*scrnPlotPos |= *bitmap >> modX;
				}
			}
		}
		else if (modX == 0)
		{
			if (blackScreen && destructive)
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_WORDS)
				{
					*scrnPlotPos = *bitmap ^ 0xFFFF;
				}
			}
			else if (destructive)
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_WORDS)
				{
					*scrnPlotPos = *bitmap;
				}
			}
			else if (blackScreen)
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_WORDS)
				{
					*scrnPlotPos ^= *bitmap;
				}
			} 
			else
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_WORDS)
				{
					*scrnPlotPos |= *bitmap;
				}
			}
		}
		else
		{
			numPxFromRight = 16 - modX;

			if (blackScreen && destructive)
			{
				leftClrMaskVal  = 0xFFFF << numPxFromRight;
				rightClrMaskVal = 0xFFFF >> modX;

				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_WORDS)
				{
					*scrnPlotPos = (*scrnPlotPos & leftClrMaskVal) | (
								   (*bitmap >> modX) ^ rightClrMaskVal);

					*(scrnPlotPos + 1) = (*(scrnPlotPos + 1) &
										  rightClrMaskVal) | ((*bitmap <<
										  numPxFromRight) ^ leftClrMaskVal);
				}
			}
			else if (destructive)
			{
				leftClrMaskVal  = 0xFFFF << numPxFromRight;
				rightClrMaskVal = 0xFFFF >> modX;

				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_WORDS)
				{
					*scrnPlotPos = (*scrnPlotPos & leftClrMaskVal) | (
								   *bitmap >> modX);

					*(scrnPlotPos + 1) = (*(scrnPlotPos + 1) &
										  rightClrMaskVal) | (*bitmap <<
										  numPxFromRight);
				}
			}
			else if (blackScreen)
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_WORDS)
				{
					*scrnPlotPos ^= *bitmap >> modX;
					*(scrnPlotPos + 1) ^= *bitmap << numPxFromRight;
				}
			}
			else
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_WORDS)
				{
					*scrnPlotPos |= *bitmap >> modX;
					*(scrnPlotPos + 1) |= *bitmap << numPxFromRight;
				}
			}
		}
	}
}

void plot_rast8(UINT8 *base, int x, int y, int height, const UINT8 *bitmap,
				BOOL destructive, BOOL blackScreen)
{
	int bitmapEndY = y + height - 1;
	int currentRow;
	int modX;
	int numPxFromRight;
	UINT8 *scrnPlotPos;

	UINT8 clrMaskVal;
	UINT8 leftClrMaskVal;
	UINT8 rightClrMaskVal;
	UINT8 xorMaskVal;

	if (bitmapEndY > SCRN_MAX_Y)
	{
		bitmapEndY = SCRN_MAX_Y;
	}

	if (x >= RAST8_MIN_X && x < (SCRN_LEN)
	&& bitmapEndY >= 0 && y <= SCRN_MAX_Y 
	&& height > 0)
	{
		modX = (abs(x) & 7);
		scrnPlotPos = (x < 0) ? base : (base + (x >> DIV_SHIFT_BY_8));

		if (y > 0)
		{
			scrnPlotPos += y * SCRN_LEN_BYTES;
		}
		if (y < 0)
		{
			bitmap += y * -1; 
			y = 0;
		}

		if (x < 0)
		{
			if (blackScreen && destructive)
			{
				clrMaskVal = 0xFF >> 8 + x;
				xorMaskVal = 0xFF << modX;

				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_BYTES)
				{
					*scrnPlotPos = (*scrnPlotPos & clrMaskVal) | ((*bitmap <<
								   modX) ^ xorMaskVal);
				}
			}
			else if (destructive)
			{
				clrMaskVal = 0xFF >> modX;

				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_BYTES)
				{ 
					*scrnPlotPos = (*scrnPlotPos & clrMaskVal) |
								   (*bitmap << modX);
				}
			}
			else if (blackScreen)
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_BYTES)
				{
					*scrnPlotPos ^= *bitmap << modX;
				}
			}
			else
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_BYTES)
				{
					*scrnPlotPos |= *bitmap << modX;
				}
			}
		}
		else if (x > RAST8_MAX_VIS_X)
		{
			if (blackScreen && destructive)
			{
				clrMaskVal = 0xFF << (8 - modX);
				xorMaskVal = 0xFF >> modX;

				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_BYTES)
				{
					*scrnPlotPos = (*scrnPlotPos & clrMaskVal) | ((*bitmap >>
								   modX) ^ xorMaskVal);
				}
			}
			else if (destructive)
			{
				clrMaskVal = 0xFF << (8 - modX);

				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_BYTES)
				{
					*scrnPlotPos = (*scrnPlotPos & clrMaskVal) | (*bitmap >>
								   modX);
				}
			}
			else if (blackScreen)
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_BYTES)
				{
					*scrnPlotPos ^= *bitmap >> modX;
				}
			}
			else
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_BYTES)
				{
					*scrnPlotPos |= *bitmap >> modX;
				}
			}
		}
		else if (modX == 0)
		{
			if (blackScreen && destructive)
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_BYTES)
				{
					*scrnPlotPos = (*bitmap ^ 0xFF);
				}
			}
			else if (destructive)
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_BYTES)
				{
					*scrnPlotPos = *bitmap;
				}
			}
			else if (blackScreen)
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_BYTES)
				{
					*scrnPlotPos ^= *bitmap;
				}
			}
			else
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_BYTES)
				{
					*scrnPlotPos |= *bitmap;
				}
			}
		}
		else
		{
			numPxFromRight = 8 - modX;

			if (blackScreen && destructive)
			{
				leftClrMaskVal  = 0xFF << numPxFromRight;
				rightClrMaskVal = 0xFF >> modX;

				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_BYTES)
				{
					*scrnPlotPos = (*scrnPlotPos & leftClrMaskVal) | (
									(*bitmap >> modX) ^ rightClrMaskVal);

					*(scrnPlotPos + 1) = (*(scrnPlotPos + 1) &
										  rightClrMaskVal) | ((*bitmap <<
										  numPxFromRight) ^ leftClrMaskVal);
				}
			}
			else if (destructive)
			{
				leftClrMaskVal  = 0xFF << numPxFromRight;
				rightClrMaskVal = 0xFF >> modX;

				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_BYTES)
				{
					*scrnPlotPos = (*scrnPlotPos & leftClrMaskVal) |
								   (*bitmap >> modX);

					*(scrnPlotPos + 1) = (*(scrnPlotPos + 1) &
										  rightClrMaskVal) | (*bitmap <<
										  numPxFromRight);
				}
			}
			else if (blackScreen)
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_BYTES)
				{
					*scrnPlotPos ^= *bitmap >> modX;
					*(scrnPlotPos + 1) ^= *bitmap << numPxFromRight;
				}
			}
			else
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bitmap++, scrnPlotPos += SCRN_LEN_BYTES)
				{
					*scrnPlotPos |= *bitmap >> modX;
					*(scrnPlotPos + 1) |= *bitmap << numPxFromRight;
				}
			}
		}
	}
}

void rect_area(UINT32 *base, int x, int length, int y, int height)
{
	const int FINAL_X = x + length - 1;
	const int FINAL_Y = y + height - 1;

	int xIndex;
	int yCounter;
	int xMaxVal;
	int yMaxVal;
	int xLong;
	int xMaxLong;
	int xDiffLong;

	UINT32 leftSegBitpattern;
	UINT32 rightSegBitpattern;

	UINT32 *scrnPlotPos;

	if (x >= 0 && x < SCRN_LEN && length > 0 &&
		y >= 0 && y < SCRN_HEIGHT && height > 0)
	{
		xMaxVal = (FINAL_X < SCRN_LEN ? FINAL_X : SCRN_MAX_X);
		yMaxVal = (FINAL_Y < SCRN_HEIGHT ? FINAL_Y : SCRN_MAX_Y);

		xLong = (x >> DIV_SHIFT_BY_32);
		xMaxLong = (xMaxVal >> DIV_SHIFT_BY_32);
		xDiffLong = xMaxLong - xLong;

		scrnPlotPos = base + (y * SCRN_LEN_LONG) + xLong;

		leftSegBitpattern = 0xFFFFFFFF >> (x & 31);
		rightSegBitpattern = 0xFFFFFFFF << 31 - (xMaxVal & 31);

		if (xLong == xMaxLong)
		{
			for (yCounter = y; yCounter <= yMaxVal;
				 yCounter++, scrnPlotPos += SCRN_LEN_LONG)
			{	
				*scrnPlotPos |= leftSegBitpattern & rightSegBitpattern;
			}
		}
		else
		{
			for (yCounter = y; yCounter <= yMaxVal;
				 yCounter++, scrnPlotPos += SCRN_LEN_LONG)
			{
				*scrnPlotPos |= leftSegBitpattern;

				for (xIndex = 1; xIndex < xDiffLong; xIndex++)
				{
					*(scrnPlotPos + xIndex) = 0xFFFFFFFF;
				}

				*(scrnPlotPos + xIndex) |= rightSegBitpattern;
			}
		}
	}
}

void clr_area(UINT32 *base, int x, int length, int y, int height)
{
	const int FINAL_X = x + length - 1;
	const int FINAL_Y = y + height - 1;

	int xIndex;
	int yCounter;
	int xMaxVal;
	int yMaxVal;
	int xLong;
	int xMaxLong;
	int xDiffLong;

	UINT32 leftSegBitpattern;
	UINT32 rightSegBitpattern;

	UINT32 *scrnPlotPos;

	if (x >= 0 && x < SCRN_LEN && length > 0 &&
		y >= 0 && y < SCRN_HEIGHT && height > 0)
	{
		xMaxVal = (FINAL_X < SCRN_LEN ? FINAL_X : SCRN_MAX_X);
		yMaxVal = (FINAL_Y < SCRN_HEIGHT ? FINAL_Y : SCRN_MAX_Y);

		xLong = (x >> DIV_SHIFT_BY_32);
		xMaxLong = (xMaxVal >> DIV_SHIFT_BY_32);
		xDiffLong = xMaxLong - xLong;

		scrnPlotPos = base + (y * SCRN_LEN_LONG) + xLong;

		leftSegBitpattern = 0xFFFFFFFF << 32 - (x & 31);
		rightSegBitpattern = 0xFFFFFFFF >> 1 + (xMaxVal & 31);

		if (xLong == xMaxLong)
		{
			for (yCounter = y; yCounter <= yMaxVal;
				 yCounter++, scrnPlotPos += SCRN_LEN_LONG)
			{	
				*scrnPlotPos &= leftSegBitpattern ^ rightSegBitpattern;
			}
		}
		else
		{
			for (yCounter = y; yCounter <= yMaxVal;
				 yCounter++, scrnPlotPos += SCRN_LEN_LONG)
			{
				*scrnPlotPos &= leftSegBitpattern;

				for (xIndex = 1; xIndex < xDiffLong; xIndex++)
				{
					*(scrnPlotPos + xIndex) = 0;
				}

				*(scrnPlotPos + xIndex) &= rightSegBitpattern;
			}
		}
	}
}