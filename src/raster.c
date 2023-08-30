/**
 * @file raster.c
 * @author Academia Team
 * @brief Contains functions and macros designed to allow rasters to be
 * plotted to an area in memory for use by the Atari ST's monochrome screen.
 * 
 * @copyright Copyright Academia Team 2023
 */

#include <stdlib.h>
#include <string.h>

#include "cpu.h"
#include "endian.h"
#include "raster.h"

void plot_px(UINT8* const base, int x, int y)
{
	if (x >= 0 && x < SCRN_LEN && y >= 0 && y < SCRN_HEIGHT)
	{
		*(base + y * SCRN_LEN_BYTES + (x >> DIV_SHIFT_BY_8))
		^= (UINT8)0x1 << (7 - (x & 7));
	}
}

void hline(UINT32* const base, int x1, int x2, int y)
{
	int minXLong;
	int maxXLong;
	int minPX;
	int maxPX;
	int index;

	UINT32* line;

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
			*line |= swap32OnLE(((0xFFFFFFFFu >> (minPX & 31)) & 
					 (0xFFFFFFFFu << (31 - (maxPX & 31)))));
		}
		else
		{
			*line |= swap32OnLE(0xFFFFFFFFu >> (minPX & 31));

			for(index = 1; index < maxXLong - minXLong; index++)
			{
				*(line + index) = swap32OnLE(0xFFFFFFFFu);
			}

			*(line + index) |= swap32OnLE(0xFFFFFFFFu << (31 - (maxPX & 31)));
		}
	}
}

void plot_rast32(UINT32* const base, int x, int y, int height,
				 const UINT32* const bitmap, BOOL destructive,
				 BOOL blackScreen)
{
	const UINT32* bmpSrcPos;

	int bitmapEndY = y + height - 1;
	int currentRow;
	int modX;
	int numPxFromRight;
	UINT32* scrnPlotPos;
	
	UINT32 clrMaskVal;
	UINT32 leftClrMaskVal;
	UINT32 rightClrMaskVal;
	UINT32 scrnPlotVal;
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
		bmpSrcPos = bitmap;

		if (y > 0)
		{
			scrnPlotPos += y * SCRN_LEN_LONG;
		}
		else if (y < 0)
		{
			bmpSrcPos += y * -1;
			y = 0;
		}

		if (x < 0)
		{
			if (blackScreen && destructive)
			{
				clrMaskVal = 0xFFFFFFFFu >> (32 + x);
				xorMaskVal = 0xFFFFFFFFu << modX;

				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_LONG)
				{
					scrnPlotVal = swap32OnLE(*scrnPlotPos);

					*scrnPlotPos = swap32OnLE((scrnPlotVal & clrMaskVal) |
								   ((*bmpSrcPos << modX) ^ xorMaskVal));
				}
			}
			else if (destructive)
			{
				clrMaskVal = 0xFFFFFFFFu >> modX;

				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_LONG)
				{
					scrnPlotVal = swap32OnLE(*scrnPlotPos);

					*scrnPlotPos = swap32OnLE((scrnPlotVal & clrMaskVal) |
								   (*bmpSrcPos << modX));
				}
			}
			else if (blackScreen)
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_LONG)
				{
					*scrnPlotPos ^= swap32OnLE(*bmpSrcPos << modX);
				}
			}
			else
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_LONG)
				{
					*scrnPlotPos |= swap32OnLE(*bmpSrcPos << modX);
				}
			}
		}
		else if (x > RAST32_MAX_VIS_X)
		{
			if (blackScreen && destructive)
			{
				clrMaskVal = 0xFFFFFFFFu << (32 - modX);
				xorMaskVal = 0xFFFFFFFFu >> modX;

				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_LONG)
				{
					scrnPlotVal = swap32OnLE(*scrnPlotPos);

					*scrnPlotPos = swap32OnLE((scrnPlotVal & clrMaskVal) |
								   ((*bmpSrcPos >> modX) ^ xorMaskVal));
				}
			}
			else if (destructive)
			{
				clrMaskVal = 0xFFFFFFFFu << (32 - modX);

				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_LONG)
				{
					scrnPlotVal = swap32OnLE(*scrnPlotPos);

					*scrnPlotPos = swap32OnLE((scrnPlotVal & clrMaskVal) |
								   (*bmpSrcPos >> modX));
				}
			}
			else if (blackScreen)
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_LONG)
				{
					*scrnPlotPos ^= swap32OnLE(*bmpSrcPos >> modX);
				}
			}
			else
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_LONG)
				{
					*scrnPlotPos |= swap32OnLE(*bmpSrcPos >> modX);
				}
			}
		}
		else if (modX == 0)
		{
			if (blackScreen && destructive)
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_LONG)
				{
					*scrnPlotPos = swap32OnLE(*bmpSrcPos ^ 0xFFFFFFFFu);
				}
			}
			else if (destructive)
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_LONG)
				{
					*scrnPlotPos = swap32OnLE(*bmpSrcPos);
				}
			}
			else if (blackScreen)
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_LONG)
				{
					*scrnPlotPos ^= swap32OnLE(*bmpSrcPos);
				}
			}
			else
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_LONG)
				{
					*scrnPlotPos |= swap32OnLE(*bmpSrcPos);
				}
			}
		}
		else
		{
			numPxFromRight = 32 - modX;

			if (blackScreen && destructive)
			{
				leftClrMaskVal  = 0xFFFFFFFFu << numPxFromRight;
				rightClrMaskVal = 0xFFFFFFFFu >> modX;

				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_LONG)
				{
					scrnPlotVal = swap32OnLE(*scrnPlotPos);

					*scrnPlotPos = swap32OnLE((scrnPlotVal & leftClrMaskVal) |
								   ((*bmpSrcPos >> modX) ^ rightClrMaskVal));
					
					scrnPlotVal = swap32OnLE(*(scrnPlotPos + 1));

					*(scrnPlotPos + 1) = swap32OnLE((scrnPlotVal &
										 rightClrMaskVal) | ((*bmpSrcPos <<
										 numPxFromRight) ^ leftClrMaskVal));
				}
			}
			else if (destructive)
			{
				leftClrMaskVal  = 0xFFFFFFFFu << numPxFromRight;
				rightClrMaskVal = 0xFFFFFFFFu >> modX;

				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_LONG)
				{
					scrnPlotVal = swap32OnLE(*scrnPlotPos);

					*scrnPlotPos = swap32OnLE((scrnPlotVal & leftClrMaskVal) |
								   (*bmpSrcPos >> modX));
					
					scrnPlotVal = swap32OnLE(*(scrnPlotPos + 1));

					*(scrnPlotPos + 1) = swap32OnLE((scrnPlotVal &
										 rightClrMaskVal) | (*bmpSrcPos <<
										 numPxFromRight));
				}
			}
			else if (blackScreen)
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_LONG)
				{
					*scrnPlotPos ^= swap32OnLE(*bmpSrcPos >> modX);
					*(scrnPlotPos + 1) ^= swap32OnLE(*bmpSrcPos <<
													 numPxFromRight);
				}
			}
			else
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_LONG)
				{
					*scrnPlotPos |= swap32OnLE(*bmpSrcPos >> modX);
					*(scrnPlotPos + 1) |= swap32OnLE(*bmpSrcPos <<
													 numPxFromRight);
				}
			}
		}
	}
}

void plot_alpha(UINT32* const base, int x, int y, int height,
				const UINT32* const bitmap)
{
	const UINT32* bmpSrcPos;

	int bitmapEndY = y + height - 1;
	int currentRow;
	int modX;
	int numPxFromRight;
	UINT32* scrnPlotPos;

	UINT32 clrMaskVal;
	UINT32 leftClrMaskVal;
	UINT32 rightClrMaskVal;
	UINT32 scrnPlotVal;

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
		bmpSrcPos = bitmap;

		if (y > 0)
		{
			scrnPlotPos += y * SCRN_LEN_LONG;
		}
		else if (y < 0)
		{
			bmpSrcPos += y * -1;
			y = 0;
		}

		if (x < 0)
		{
			clrMaskVal = 0xFFFFFFFFu >> modX;

			for (currentRow = y; currentRow <= bitmapEndY;
				 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_LONG)
			{
				scrnPlotVal = swap32OnLE(*scrnPlotPos);

				*scrnPlotPos &= swap32OnLE((scrnPlotVal & clrMaskVal) |
								(*bmpSrcPos << modX));
			}
		}
		else if (x > RAST32_MAX_VIS_X)
		{
			clrMaskVal = 0xFFFFFFFFu << (32 - modX);

			for (currentRow = y; currentRow <= bitmapEndY;
				 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_LONG)
			{
				scrnPlotVal = swap32OnLE(*scrnPlotPos);

				*scrnPlotPos &= swap32OnLE((scrnPlotVal & clrMaskVal) |
								(*bmpSrcPos >> modX));
			}
		}
		else if (modX == 0)
		{
			for (currentRow = y; currentRow <= bitmapEndY;
				 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_LONG)
			{
				*scrnPlotPos &= swap32OnLE(*(bmpSrcPos));
			}
		}
		else
		{
			numPxFromRight  = 32 - modX;
			leftClrMaskVal  = 0xFFFFFFFFu << numPxFromRight;
			rightClrMaskVal = 0xFFFFFFFFu >> modX;

			for (currentRow = y; currentRow <= bitmapEndY;
				 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_LONG)
			{
				scrnPlotVal = swap32OnLE(*scrnPlotPos);

				*scrnPlotPos &= swap32OnLE((scrnPlotVal & leftClrMaskVal) |
								(*bmpSrcPos >> modX));
				
				scrnPlotVal = swap32OnLE(*(scrnPlotPos + 1));

				*(scrnPlotPos + 1) &= swap32OnLE((scrnPlotVal & rightClrMaskVal) |
									  (*bmpSrcPos << numPxFromRight));
			}
		}
	}
}

void plot_rast16(UINT16* const base, int x, int y, int height,
				 const UINT16* const bitmap, BOOL destructive,
				 BOOL blackScreen)
{
	const UINT16* bmpSrcPos;
	
	int bitmapEndY = y + height - 1;
	int currentRow;
	int modX;
	int numPxFromRight;
	UINT16* scrnPlotPos;

	UINT16 clrMaskVal;
	UINT16 leftClrMaskVal;
	UINT16 rightClrMaskVal;
	UINT16 scrnPlotVal;
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
		bmpSrcPos = bitmap;

		if (y > 0)
		{
			scrnPlotPos += y * SCRN_LEN_WORDS;
		}
		else if (y < 0)
		{
			bmpSrcPos += y * -1;
			y = 0;
		}

		if (x < 0)
		{
			if (blackScreen && destructive)
			{
				clrMaskVal = 0xFFFFu >> (16 + x);
				xorMaskVal = 0xFFFFu << modX;

				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_WORDS)
				{
					scrnPlotVal = swap16OnLE(*scrnPlotPos);

					*scrnPlotPos = swap16OnLE((scrnPlotVal & clrMaskVal) | (
								   (*bmpSrcPos << modX) ^ xorMaskVal));
				}
			}
			else if (destructive)
			{
				clrMaskVal = 0xFFFFu >> modX;

				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_WORDS)
				{
					scrnPlotVal = swap16OnLE(*scrnPlotPos);

					*scrnPlotPos = swap16OnLE((scrnPlotVal & clrMaskVal) |
								   (*bmpSrcPos << modX));
				}
			}
			else if (blackScreen)
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_WORDS)
				{
					*scrnPlotPos ^= swap16OnLE(*bmpSrcPos << modX);
				}
			}
			else
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_WORDS)
				{
					*scrnPlotPos |= swap16OnLE(*bmpSrcPos << modX);
				}
			}
		}
		else if (x > RAST16_MAX_VIS_X)
		{
			if (blackScreen && destructive)
			{
				clrMaskVal = 0xFFFFu << (16 - modX);
				xorMaskVal = 0xFFFFu >> modX;

				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_WORDS)
				{
					scrnPlotVal = swap16OnLE(*scrnPlotPos);

					*scrnPlotPos = swap16OnLE((scrnPlotVal & clrMaskVal) | (
								   (*bmpSrcPos >> modX) ^ xorMaskVal));
				}
			}
			else if (destructive)
			{
				clrMaskVal = 0xFFFFu << (16 - modX);

				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_WORDS)
				{
					scrnPlotVal = swap16OnLE(*scrnPlotPos);

					*scrnPlotPos = swap16OnLE((scrnPlotVal & clrMaskVal) |
								   (*bmpSrcPos >> modX));
				}
			}
			else if (blackScreen)
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_WORDS)
				{
					*scrnPlotPos ^= swap16OnLE(*bmpSrcPos >> modX);
				}
			} 
			else
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_WORDS)
				{
					*scrnPlotPos |= swap16OnLE(*bmpSrcPos >> modX);
				}
			}
		}
		else if (modX == 0)
		{
			if (blackScreen && destructive)
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_WORDS)
				{
					*scrnPlotPos = swap16OnLE(*bmpSrcPos ^ 0xFFFFu);
				}
			}
			else if (destructive)
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_WORDS)
				{
					*scrnPlotPos = swap16OnLE(*bmpSrcPos);
				}
			}
			else if (blackScreen)
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_WORDS)
				{
					*scrnPlotPos ^= swap16OnLE(*bmpSrcPos);
				}
			} 
			else
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_WORDS)
				{
					*scrnPlotPos |= swap16OnLE(*bmpSrcPos);
				}
			}
		}
		else
		{
			numPxFromRight = 16 - modX;

			if (blackScreen && destructive)
			{
				leftClrMaskVal  = 0xFFFFu << numPxFromRight;
				rightClrMaskVal = 0xFFFFu >> modX;

				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_WORDS)
				{
					scrnPlotVal = swap16OnLE(*scrnPlotPos);

					*scrnPlotPos = swap16OnLE((scrnPlotVal & leftClrMaskVal) |
								   ((*bmpSrcPos >> modX) ^ rightClrMaskVal));

					scrnPlotVal = swap16OnLE(*(scrnPlotPos + 1));

					*(scrnPlotPos + 1) = swap16OnLE((scrnPlotVal &
										 rightClrMaskVal) | ((*bmpSrcPos <<
										 numPxFromRight) ^ leftClrMaskVal));
				}
			}
			else if (destructive)
			{
				leftClrMaskVal  = 0xFFFFu << numPxFromRight;
				rightClrMaskVal = 0xFFFFu >> modX;

				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_WORDS)
				{
					scrnPlotVal = swap16OnLE(*scrnPlotPos);

					*scrnPlotPos = swap16OnLE((scrnPlotVal & leftClrMaskVal) |
								   (*bmpSrcPos >> modX));

					scrnPlotVal = swap16OnLE(*(scrnPlotPos + 1));

					*(scrnPlotPos + 1) = swap16OnLE((scrnPlotVal &
										 rightClrMaskVal) | (*bmpSrcPos <<
										 numPxFromRight));
				}
			}
			else if (blackScreen)
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_WORDS)
				{
					*scrnPlotPos ^= swap16OnLE(*bmpSrcPos >> modX);
					*(scrnPlotPos + 1) ^= swap16OnLE(*bmpSrcPos <<
													 numPxFromRight);
				}
			}
			else
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_WORDS)
				{
					*scrnPlotPos |= swap16OnLE(*bmpSrcPos >> modX);
					*(scrnPlotPos + 1) |= swap16OnLE(*bmpSrcPos <<
													 numPxFromRight);
				}
			}
		}
	}
}

void plot_rast8(UINT8* const base, int x, int y, int height,
				const UINT8* const bitmap, BOOL destructive, BOOL blackScreen)
{
	const UINT8* bmpSrcPos;

	int bitmapEndY = y + height - 1;
	int currentRow;
	int modX;
	int numPxFromRight;
	UINT8* scrnPlotPos;

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
		bmpSrcPos = bitmap;

		if (y > 0)
		{
			scrnPlotPos += y * SCRN_LEN_BYTES;
		}
		else if (y < 0)
		{
			bmpSrcPos += y * -1; 
			y = 0;
		}

		if (x < 0)
		{
			if (blackScreen && destructive)
			{
				clrMaskVal = 0xFFu >> (8 + x);
				xorMaskVal = 0xFFu << modX;

				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_BYTES)
				{
					*scrnPlotPos = (*scrnPlotPos & clrMaskVal) | ((*bmpSrcPos <<
								   modX) ^ xorMaskVal);
				}
			}
			else if (destructive)
			{
				clrMaskVal = 0xFFu >> modX;

				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_BYTES)
				{ 
					*scrnPlotPos = (*scrnPlotPos & clrMaskVal) |
								   (*bmpSrcPos << modX);
				}
			}
			else if (blackScreen)
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_BYTES)
				{
					*scrnPlotPos ^= *bmpSrcPos << modX;
				}
			}
			else
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_BYTES)
				{
					*scrnPlotPos |= *bmpSrcPos << modX;
				}
			}
		}
		else if (x > RAST8_MAX_VIS_X)
		{
			if (blackScreen && destructive)
			{
				clrMaskVal = 0xFFu << (8 - modX);
				xorMaskVal = 0xFFu >> modX;

				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_BYTES)
				{
					*scrnPlotPos = (*scrnPlotPos & clrMaskVal) | ((*bmpSrcPos >>
								   modX) ^ xorMaskVal);
				}
			}
			else if (destructive)
			{
				clrMaskVal = 0xFFu << (8 - modX);

				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_BYTES)
				{
					*scrnPlotPos = (*scrnPlotPos & clrMaskVal) | (*bmpSrcPos >>
								   modX);
				}
			}
			else if (blackScreen)
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_BYTES)
				{
					*scrnPlotPos ^= *bmpSrcPos >> modX;
				}
			}
			else
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_BYTES)
				{
					*scrnPlotPos |= *bmpSrcPos >> modX;
				}
			}
		}
		else if (modX == 0)
		{
			if (blackScreen && destructive)
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_BYTES)
				{
					*scrnPlotPos = (*bmpSrcPos ^ 0xFFu);
				}
			}
			else if (destructive)
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_BYTES)
				{
					*scrnPlotPos = *bmpSrcPos;
				}
			}
			else if (blackScreen)
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_BYTES)
				{
					*scrnPlotPos ^= *bmpSrcPos;
				}
			}
			else
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_BYTES)
				{
					*scrnPlotPos |= *bmpSrcPos;
				}
			}
		}
		else
		{
			numPxFromRight = 8 - modX;

			if (blackScreen && destructive)
			{
				leftClrMaskVal  = 0xFFu << numPxFromRight;
				rightClrMaskVal = 0xFFu >> modX;

				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_BYTES)
				{
					*scrnPlotPos = (*scrnPlotPos & leftClrMaskVal) | (
									(*bmpSrcPos >> modX) ^ rightClrMaskVal);

					*(scrnPlotPos + 1) = (*(scrnPlotPos + 1) &
										  rightClrMaskVal) | ((*bmpSrcPos <<
										  numPxFromRight) ^ leftClrMaskVal);
				}
			}
			else if (destructive)
			{
				leftClrMaskVal  = 0xFFu << numPxFromRight;
				rightClrMaskVal = 0xFFu >> modX;

				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_BYTES)
				{
					*scrnPlotPos = (*scrnPlotPos & leftClrMaskVal) |
								   (*bmpSrcPos >> modX);

					*(scrnPlotPos + 1) = (*(scrnPlotPos + 1) &
										  rightClrMaskVal) | (*bmpSrcPos <<
										  numPxFromRight);
				}
			}
			else if (blackScreen)
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_BYTES)
				{
					*scrnPlotPos ^= *bmpSrcPos >> modX;
					*(scrnPlotPos + 1) ^= *bmpSrcPos << numPxFromRight;
				}
			}
			else
			{
				for (currentRow = y; currentRow <= bitmapEndY;
					 currentRow++, bmpSrcPos++, scrnPlotPos += SCRN_LEN_BYTES)
				{
					*scrnPlotPos |= *bmpSrcPos >> modX;
					*(scrnPlotPos + 1) |= *bmpSrcPos << numPxFromRight;
				}
			}
		}
	}
}

void rect_area(UINT32* const base, int x, int length, int y, int height)
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

	UINT32* scrnPlotPos;

	if (x >= 0 && x < SCRN_LEN && length > 0 &&
		y >= 0 && y < SCRN_HEIGHT && height > 0)
	{
		xMaxVal = (FINAL_X < SCRN_LEN ? FINAL_X : SCRN_MAX_X);
		yMaxVal = (FINAL_Y < SCRN_HEIGHT ? FINAL_Y : SCRN_MAX_Y);

		xLong = (x >> DIV_SHIFT_BY_32);
		xMaxLong = (xMaxVal >> DIV_SHIFT_BY_32);
		xDiffLong = xMaxLong - xLong;

		scrnPlotPos = base + (y * SCRN_LEN_LONG) + xLong;

		leftSegBitpattern = 0xFFFFFFFFu >> (x & 31);
		rightSegBitpattern = 0xFFFFFFFFu << (31 - (xMaxVal & 31));

		if (xLong == xMaxLong)
		{
			for (yCounter = y; yCounter <= yMaxVal;
				 yCounter++, scrnPlotPos += SCRN_LEN_LONG)
			{	
				*scrnPlotPos |= swap32OnLE(leftSegBitpattern &
										   rightSegBitpattern);
			}
		}
		else
		{
			for (yCounter = y; yCounter <= yMaxVal;
				 yCounter++, scrnPlotPos += SCRN_LEN_LONG)
			{
				*scrnPlotPos |= swap32OnLE(leftSegBitpattern);

				for (xIndex = 1; xIndex < xDiffLong; xIndex++)
				{
					*(scrnPlotPos + xIndex) = 0xFFFFFFFFu;
				}

				*(scrnPlotPos + xIndex) |= swap32OnLE(rightSegBitpattern);
			}
		}
	}
}

void clr_area(UINT32* const base, int x, int length, int y, int height)
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

	UINT32* scrnPlotPos;

	if (x >= 0 && x < SCRN_LEN && length > 0 &&
		y >= 0 && y < SCRN_HEIGHT && height > 0)
	{
		xMaxVal = (FINAL_X < SCRN_LEN ? FINAL_X : SCRN_MAX_X);
		yMaxVal = (FINAL_Y < SCRN_HEIGHT ? FINAL_Y : SCRN_MAX_Y);

		xLong = (x >> DIV_SHIFT_BY_32);
		xMaxLong = (xMaxVal >> DIV_SHIFT_BY_32);
		xDiffLong = xMaxLong - xLong;

		scrnPlotPos = base + (y * SCRN_LEN_LONG) + xLong;

		leftSegBitpattern = 0xFFFFFFFFu << (32 - (x & 31));
		rightSegBitpattern = 0xFFFFFFFFu >> (1 + (xMaxVal & 31));

		if (xLong == xMaxLong)
		{
			for (yCounter = y; yCounter <= yMaxVal;
				 yCounter++, scrnPlotPos += SCRN_LEN_LONG)
			{	
				*scrnPlotPos &= swap32OnLE(leftSegBitpattern ^
										   rightSegBitpattern);
			}
		}
		else
		{
			for (yCounter = y; yCounter <= yMaxVal;
				 yCounter++, scrnPlotPos += SCRN_LEN_LONG)
			{
				*scrnPlotPos &= swap32OnLE(leftSegBitpattern);

				for (xIndex = 1; xIndex < xDiffLong; xIndex++)
				{
					*(scrnPlotPos + xIndex) = 0;
				}

				*(scrnPlotPos + xIndex) &= swap32OnLE(rightSegBitpattern);
			}
		}
	}
}

#ifndef M68K_CPU
void fill_scrn(UINT32* const base)
{
	int index;

	for (index = 0; index < SCRN_LONGS; index++)
	{
		base[index] = 0xFFFFFFFFu;
	}
}

void clr_scrn(UINT32* const base)
{
	int index;

	for (index = 0; index < SCRN_LONGS; index++)
	{
		base[index] = 0x00000000u;
	}
}
#endif