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
	int currentRow = 0;
	int modX = 0;
	UINT32 value = 0;
	UINT32 *scrnPlotPos = 0;

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
			for (currentRow = y; currentRow <= bitmapEndY;
				 currentRow++, bitmap++)
			{
				if (blackScreen && destructive)
				{
					value = (*scrnPlotPos) & (0xFFFFFFFF >> 32 + x);
					*scrnPlotPos = value | ((*(bitmap) << modX) ^
						(0xFFFFFFFF << modX));

				}
				else if (destructive)
				{
					value = (*scrnPlotPos) & (0xFFFFFFFF >> modX); 
					*scrnPlotPos = value | (*(bitmap) << modX);
				}
				else if (blackScreen)
				{
					*scrnPlotPos ^= *(bitmap) << modX;
				} 
				else
				{
					*scrnPlotPos |= *(bitmap) << modX;
				}
				scrnPlotPos += SCRN_LEN_LONG;
			}
		}
		else if (x > RAST32_MAX_VIS_X)
		{
			for (currentRow = y; currentRow <= bitmapEndY;
				 currentRow++, bitmap++)
			{
				if (blackScreen && destructive)
				{
					value = (*scrnPlotPos) & (0xFFFFFFFF << (32 - modX));
					*scrnPlotPos = value | ((*(bitmap) >> modX) ^
						(0xFFFFFFFF >> modX));
				}
				else if (destructive)
				{
					value = (*scrnPlotPos) & (0xFFFFFFFF << (32 - modX));
					*scrnPlotPos = value | (*(bitmap) >> modX);
				}
				else if (blackScreen)
				{
					*scrnPlotPos ^= *(bitmap) >> modX;
				} 
				else
				{
					*scrnPlotPos |= *(bitmap) >> modX;
				}
				scrnPlotPos += SCRN_LEN_LONG;
			}
		}
		else if (modX == 0)
		{
			for (currentRow = y; currentRow <= bitmapEndY;
				 currentRow++, bitmap++)
			{
				if (blackScreen && destructive)
				{
					*scrnPlotPos = (*(bitmap) ^ 0xFFFFFFFF);
				}
				else if (destructive)
				{
					*scrnPlotPos = *(bitmap);
				}
				else if (blackScreen)
				{
					*scrnPlotPos ^= *(bitmap);
				} 
				else
				{
					*scrnPlotPos |= *(bitmap);
				}
				scrnPlotPos += SCRN_LEN_LONG;
			}
		}
		else
		{
			for (currentRow = y; currentRow <= bitmapEndY;
				 currentRow++, bitmap++)
			{
				if (blackScreen && destructive)
				{
					value = (*scrnPlotPos) & (0xFFFFFFFF << (32 - modX));
					*scrnPlotPos = value | ((*bitmap >> modX) ^
						(0xFFFFFFFF >> modX));

					value = (*(scrnPlotPos + 1)) & (0xFFFFFFFF >> modX);
					*(scrnPlotPos + 1) = value | ((*(bitmap) << (32 - modX)) ^
						(0xFFFFFFFF << (32 - modX)));
				}
				else if (destructive)
				{
					value = (*scrnPlotPos) & (0xFFFFFFFF << (32 - modX));
					*scrnPlotPos = value | (*bitmap >> modX);

					value = (*(scrnPlotPos + 1)) & (0xFFFFFFFF >> modX);
					*(scrnPlotPos + 1) = value | (*(bitmap) << (32 - modX));
				}
				else if (blackScreen)
				{
					*scrnPlotPos ^= *bitmap >> modX;
					*(scrnPlotPos + 1) ^= *(bitmap) << (32 - modX);
				} 
				else
				{
					*scrnPlotPos |= *bitmap >> modX;
					*(scrnPlotPos + 1) |= *(bitmap) << (32 - modX);
				}
				scrnPlotPos += SCRN_LEN_LONG;
			}
		}
	}
}

void plot_alpha(UINT32 *base, int x, int y, int height, const UINT32 *bitmap)
{
	const int bitmapEndY = y + height - 1;
	int currentRow = 0;
	int modX = 0;
	UINT32 value = 0;
	UINT32 *scrnPlotPos = 0;

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
			for (currentRow = y; currentRow <= bitmapEndY;
				 currentRow++, bitmap++)
			{
				value = (*scrnPlotPos) & (0xFFFFFFFF >> modX); 
				*scrnPlotPos &= value | (*(bitmap) << modX);
				scrnPlotPos += SCRN_LEN_LONG;
			}
		}
		else if (x > RAST32_MAX_VIS_X)
		{
			for (currentRow = y; currentRow <= bitmapEndY;
				 currentRow++, bitmap++)
			{
				value = (*scrnPlotPos) & (0xFFFFFFFF << (32 - modX));
				*scrnPlotPos &= value | (*(bitmap) >> modX);
				scrnPlotPos += SCRN_LEN_LONG;
			}
		}
		else if (modX == 0)
		{
			for (currentRow = y; currentRow <= bitmapEndY;
				 currentRow++, bitmap++)
			{
				*scrnPlotPos &= *(bitmap);
				scrnPlotPos += SCRN_LEN_LONG;
			}
		}
		else
		{
			for (currentRow = y; currentRow <= bitmapEndY;
				 currentRow++, bitmap++)
			{
				value = (*scrnPlotPos) & (0xFFFFFFFF << (32 - modX));
				*scrnPlotPos &= value | (*bitmap >> modX);
				value = (*(scrnPlotPos + 1)) & (0xFFFFFFFF >> modX);
				*(scrnPlotPos + 1) &= value | (*(bitmap) << (32 - modX));
				scrnPlotPos += SCRN_LEN_LONG;
			}
		}
	}
}

void plot_rast16(UINT16 *base, int x, int y, int height, const UINT16 *bitmap,
				 BOOL destructive, BOOL blackScreen)
{
	int bitmapEndY = y + height - 1;
	int currentRow = 0;
	int modX = 0;
	UINT16 value = 0;
	UINT16 *scrnPlotPos = 0;

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
			for (currentRow = y; currentRow <= bitmapEndY;
				 currentRow++, bitmap++)
			{
				if (blackScreen && destructive)
				{
					value = (*scrnPlotPos) & (0xFFFF >> 16 + x);
					*scrnPlotPos = value | ((*(bitmap) << modX) ^
						(0xFFFF << modX));

				}
				else if (destructive)
				{
					value = (*scrnPlotPos) & (0xFFFF >> modX); 
					*scrnPlotPos = value | (*(bitmap) << modX);
				}
				else if (blackScreen)
				{
					*scrnPlotPos ^= *(bitmap) << modX;
				} 
				else
				{
					*scrnPlotPos |= *(bitmap) << modX;
				}
				scrnPlotPos += SCRN_LEN_WORDS;
			}
		}
		else if (x > RAST16_MAX_VIS_X)
		{
			for (currentRow = y; currentRow <= bitmapEndY;
				 currentRow++, bitmap++)
			{
				if (blackScreen && destructive)
				{
					value = (*scrnPlotPos) & (0xFFFF << (16 - modX));
					*scrnPlotPos = value | ((*(bitmap) >> modX) ^
						(0xFFFF >> modX));
				}
				else if (destructive)
				{
					value = (*scrnPlotPos) & (0xFFFF << (16 - modX));
					*scrnPlotPos = value | (*(bitmap) >> modX);
				}
				else if (blackScreen)
				{
					*scrnPlotPos ^= *(bitmap) >> modX;
				} 
				else
				{
					*scrnPlotPos |= *(bitmap) >> modX;
				}
				scrnPlotPos += SCRN_LEN_WORDS;
			}
		}
		else if (modX == 0)
		{
			for (currentRow = y; currentRow <= bitmapEndY;
				 currentRow++, bitmap++)
			{
				if (blackScreen && destructive)
				{
					*scrnPlotPos = (*(bitmap) ^ 0xFFFF);
				}
				else if (destructive)
				{
					*scrnPlotPos = *(bitmap);
				}
				else if (blackScreen)
				{
					*scrnPlotPos ^= *(bitmap);
				} 
				else
				{
					*scrnPlotPos |= *(bitmap);
				}
				scrnPlotPos += SCRN_LEN_WORDS;
			}
		}
		else
		{
			for (currentRow = y; currentRow <= bitmapEndY;
				 currentRow++, bitmap++)
			{
				if (blackScreen && destructive)
				{
					value = (*scrnPlotPos) & (0xFFFF << (16 - modX));
					*scrnPlotPos = value | ((*bitmap >> modX) ^
						(0xFFFF >> modX));

					value = (*(scrnPlotPos + 1)) & (0xFFFF >> modX);
					*(scrnPlotPos + 1) = value | ((*(bitmap) << (16 - modX)) ^
						(0xFFFF << (16 - modX)));
				}
				else if (destructive)
				{
					value = (*scrnPlotPos) & (0xFFFF << (16 - modX));
					*scrnPlotPos = value | (*bitmap >> modX);

					value = (*(scrnPlotPos + 1)) & (0xFFFF >> modX);
					*(scrnPlotPos + 1) = value | (*(bitmap) << (16 - modX));
				}
				else if (blackScreen)
				{
					*scrnPlotPos ^= *bitmap >> modX;
					*(scrnPlotPos + 1) ^= *(bitmap) << (16 - modX);
				} 
				else
				{
					*scrnPlotPos |= *bitmap >> modX;
					*(scrnPlotPos + 1) |= *(bitmap) << (16 - modX);
				}
				scrnPlotPos += SCRN_LEN_WORDS;
			}
		}
	}
}

void plot_rast8(UINT8 *base, int x, int y, int height, const UINT8 *bitmap,
				BOOL destructive, BOOL blackScreen)
{
	int bitmapEndY = y + height - 1;
	int currentRow = 0;
	int modX = 0;
	UINT8 value = 0;
	UINT8 *scrnPlotPos = 0;

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
			for (currentRow = y; currentRow <= bitmapEndY;
				 currentRow++, bitmap++)
			{
				if (blackScreen && destructive)
				{
					value = (*scrnPlotPos) & (0xFF >> 8 + x);
					*scrnPlotPos = value | ((*(bitmap) << modX) ^
						(0xFF << modX));

				}
				else if (destructive)
				{
					value = (*scrnPlotPos) & (0xFF >> modX); 
					*scrnPlotPos = value | (*(bitmap) << modX);
				}
				else if (blackScreen)
				{
					*scrnPlotPos ^= *(bitmap) << modX;
				} 
				else
				{
					*scrnPlotPos |= *(bitmap) << modX;
				}
				scrnPlotPos += SCRN_LEN_BYTES;
			}
		}
		else if (x > RAST8_MAX_VIS_X)
		{
			for (currentRow = y; currentRow <= bitmapEndY;
				 currentRow++, bitmap++)
			{
				if (blackScreen && destructive)
				{
					value = (*scrnPlotPos) & (0xFF << (8 - modX));
					*scrnPlotPos = value | ((*(bitmap) >> modX) ^
						(0xFF >> modX));
				}
				else if (destructive)
				{
					value = (*scrnPlotPos) & (0xFF << (8 - modX));
					*scrnPlotPos = value | (*(bitmap) >> modX);
				}
				else if (blackScreen)
				{
					*scrnPlotPos ^= *(bitmap) >> modX;
				} 
				else
				{
					*scrnPlotPos |= *(bitmap) >> modX;
				}
				scrnPlotPos += SCRN_LEN_BYTES;
			}
		}
		else if (modX == 0)
		{
			for (currentRow = y; currentRow <= bitmapEndY;
				 currentRow++, bitmap++)
			{
				if (blackScreen && destructive)
				{
					*scrnPlotPos = (*(bitmap) ^ 0xFF);
				}
				else if (destructive)
				{
					*scrnPlotPos = *(bitmap);
				}
				else if (blackScreen)
				{
					*scrnPlotPos ^= *(bitmap);
				} 
				else
				{
					*scrnPlotPos |= *(bitmap);
				}
				scrnPlotPos += SCRN_LEN_BYTES;
			}
		}
		else
		{
			for (currentRow = y; currentRow <= bitmapEndY;
				 currentRow++, bitmap++)
			{
				if (blackScreen && destructive)
				{
					value = (*scrnPlotPos) & (0xFF << (8 - modX));
					*scrnPlotPos = value | ((*bitmap >> modX) ^ (0xFF >> modX));

					value = (*(scrnPlotPos + 1)) & (0xFF >> modX);
					*(scrnPlotPos + 1) = value | ((*(bitmap) << (8 - modX)) ^
						(0xFF << (8 - modX)));
				}
				else if (destructive)
				{
					value = (*scrnPlotPos) & (0xFF << (8 - modX));
					*scrnPlotPos = value | (*bitmap >> modX);

					value = (*(scrnPlotPos + 1)) & (0xFF >> modX);
					*(scrnPlotPos + 1) = value | (*(bitmap) << (8 - modX));
				}
				else if (blackScreen)
				{
					*scrnPlotPos ^= *bitmap >> modX;
					*(scrnPlotPos + 1) ^= *(bitmap) << (8 - modX);
				} 
				else
				{
					*scrnPlotPos |= *bitmap >> modX;
					*(scrnPlotPos + 1) |= *(bitmap) << (8 - modX);
				}
				scrnPlotPos += SCRN_LEN_BYTES;
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