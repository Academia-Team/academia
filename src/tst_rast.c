/**
 * @file tst_rast.c
 * @author Academia Team
 * @brief Contains constants and functions designed to help test raster
 * functions.
 * 
 * @copyright Copyright Academia Team 2023
 */

#include <stdio.h>

#include "arg_list.h"
#include "input.h"
#include "raster.h"
#include "scrn.h"
#include "tst_rast.h"
#include "types.h"

void rastTstCommon(void (*tstFunc)(ArgList *args), BOOL blackScreen,
				   BOOL enableGridDots, BOOL destructive);
void gridDots(UINT32 *base);
void off_curs();
void on_curs();

void rastTstWhite(void (*tstFunc)(ArgList *args))
{
	rastTstCommon(tstFunc, BLACK_SCREEN_OFF, GRID_DOTS_OFF, DESTRUCT_ON);
}

void rastTstWhitePerserve(void (*tstFunc)(ArgList *args))
{
	rastTstCommon(tstFunc, BLACK_SCREEN_OFF, GRID_DOTS_OFF, DESTRUCT_OFF);
}

void rastGDTstWhite(void (*tstFunc)(ArgList *args))
{
	rastTstCommon(tstFunc, BLACK_SCREEN_OFF, GRID_DOTS_ON, DESTRUCT_ON);
}

void rastTstBlack(void (*tstFunc)(ArgList *args))
{
	rastTstCommon(tstFunc, BLACK_SCREEN_ON, GRID_DOTS_OFF, DESTRUCT_ON);
}

void rastTstBlackPerserve(void (*tstFunc)(ArgList *args))
{
	rastTstCommon(tstFunc, BLACK_SCREEN_ON, GRID_DOTS_OFF, DESTRUCT_OFF);
}

void rastGDTstBlack(void (*tstFunc)(ArgList *args))
{
	rastTstCommon(tstFunc, BLACK_SCREEN_ON, GRID_DOTS_ON, DESTRUCT_ON);
}

/**
 * @brief Contains the common functionality shared by all the raster test
 * manager functions.
 * 
 * @param tstFunc The function to test the raster functions.
 * @param blackScreen Whether there should be a white or black screen.
 * @param enableGridDots When enabled, will show dots that are spaced out by 32
 * pixels horizontally and 16 pixels vertically.
 * @param destructive If the function being tested should destroy existing
 * imagery on the screen (only if supported by the function being tested).
 */
void rastTstCommon(void (*tstFunc)(ArgList *args), BOOL blackScreen,
				   BOOL enableGridDots, BOOL destructive)
{
	ArgList args;
	Vector origKybd = initKybd();
	IKBD_Scancode scancode;

	initArgList(&args);
	appendArgToList("base", get_video_base(), &args);
	appendArgToList("blackScreen", &blackScreen, &args);
	appendArgToList("destructive", &destructive, &args);

	off_curs();

	if (blackScreen)
	{
		fill_scrn((UINT32 *)getArgFromList("base", &args));
	}
	else
	{
		clr_scrn((UINT32 *)getArgFromList("base", &args));
	}

	if (enableGridDots)
	{
		gridDots((UINT32 *)getArgFromList("base", &args));
	}

	tstFunc(&args);

	while ((scancode = getKey()) == NO_KEY);

	on_curs();
	restoreKybd(origKybd);
}

/**
 * @brief Adds dots that are spaced out by 32 pixels horizontally and 16 pixels
 * vertically.
 * @details The plotting of dots starts 31 pixels from the left of the screen
 * and continues until the end of the screen is reached.
 * 
 * @param base The location in memory of start of frame buffer.
 */
void gridDots(UINT32 *base)
{
	int y, x;
	for (y = 0; y < SCRN_HEIGHT; y += 16)
	{
		for (x = 31; x < SCRN_LEN; x += 32)
		{
			plot_px((UINT8 *)base, x, y);
		}
	}
}

/**
 * @brief Disables the cursor.
 */
void off_curs()
{
	printf("\033f");
	fflush(stdout);
}

/**
 * @brief Enables the cursor.
 */
void on_curs()
{
	printf("\033e");
	fflush(stdout);
}