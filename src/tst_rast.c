/**
 * @file tst_rast.c
 * @author Academia Team
 * @brief It is designed to test the functionality of all raster
 * functions.
 * 
 * @copyright Copyright Academia Team 2023
 */

#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "arg_list.h"
#include "bitmaps.h"
#include "ikbdcode.h"
#include "input.h"
#include "raster.h"
#include "scrn.h"
#include "super.h"
#include "test.h"

#define CLEAR_ON  TRUE
#define CLEAR_OFF FALSE

#define DESTRUCT_ON  TRUE
#define DESTRUCT_OFF FALSE

#define BLACK_SCREEN_ON  TRUE
#define BLACK_SCREEN_OFF FALSE

#define GRID_DOTS_ON  TRUE
#define GRID_DOTS_OFF FALSE

void rastTstWhite(void (*tstFunc)(ArgList *args));
void rastTstWhitePerserve(void (*tstFunc)(ArgList *args));
void rastGDTstWhite(void (*tstFunc)(ArgList *args));
void rastTstBlack(void (*tstFunc)(ArgList *args));
void rastGDTstBlack(void (*tstFunc)(ArgList *args));
void rastTstBlackPerserve(void (*tstFunc)(ArgList *args));
void rastTstCommon(void (*tstFunc)(ArgList *args), BOOL blackScreen,
				   BOOL enableGridDots, BOOL destructive);

void regPlotPxTests(BOOL blackScreen);
void t1PlotPx(ArgList *args);
void t2PlotPx(ArgList *args);
void t3PlotPx(ArgList *args);
void t4PlotPx(ArgList *args);
void t5PlotPx(ArgList *args);
void t6PlotPx(ArgList *args);
void t7PlotPx(ArgList *args);
void t8PlotPx(ArgList *args);
void t9PlotPx(ArgList *args);
void t10PlotPx(ArgList *args);
void t11PlotPx(ArgList *args);
void t12PlotPx(ArgList *args);
void t13PlotPx(ArgList *args);

void regHlineTests();
void t1Hline(ArgList *args);
void t2Hline(ArgList *args);
void t3Hline(ArgList *args);
void t4Hline(ArgList *args);
void t5Hline(ArgList *args);
void t6Hline(ArgList *args);
void t7Hline(ArgList *args);
void t8Hline(ArgList *args);
void t9Hline(ArgList *args);
void t10Hline(ArgList *args);
void t11Hline(ArgList *args);
void t12Hline(ArgList *args);
void t13Hline(ArgList *args);
void t14Hline(ArgList *args);
void t15Hline(ArgList *args);
void t16Hline(ArgList *args);
void t17Hline(ArgList *args);
void t18Hline(ArgList *args);
void t19Hline(ArgList *args);
void t20Hline(ArgList *args);
void t21Hline(ArgList *args);
void t22Hline(ArgList *args);
void t23Hline(ArgList *args);
void t24Hline(ArgList *args);
void t25Hline(ArgList *args);
void t26Hline(ArgList *args);
void t27Hline(ArgList *args);
void t28Hline(ArgList *args);
void t29Hline(ArgList *args);

void regRast32Tests(BOOL blackScreen, BOOL destructive);
void t1Rast32(ArgList *args);
void t2Rast32(ArgList *args);
void t3Rast32(ArgList *args);
void t4Rast32(ArgList *args);
void t5Rast32(ArgList *args);
void t6Rast32(ArgList *args);
void t7Rast32(ArgList *args);
void t8Rast32(ArgList *args);
void t9Rast32(ArgList *args);
void t10Rast32(ArgList *args);
void t11Rast32(ArgList *args);
void t12Rast32(ArgList *args);
void t13Rast32(ArgList *args);
void t14Rast32(ArgList *args);
void t15Rast32(ArgList *args);
void t16Rast32(ArgList *args);
void t17Rast32(ArgList *args);
void t18Rast32(ArgList *args);
void t19Rast32(ArgList *args);
void t20Rast32(ArgList *args);
void t21Rast32(ArgList *args);
void t22Rast32(ArgList *args);
void t23Rast32(ArgList *args);
void t24Rast32(ArgList *args);
void t25Rast32(ArgList *args);
void t26Rast32(ArgList *args);
void t27Rast32(ArgList *args);
void t28Rast32(ArgList *args);
void t29Rast32(ArgList *args);
void t30Rast32(ArgList *args);
void t31Rast32(ArgList *args);
void t32Rast32(ArgList *args);
void t33Rast32(ArgList *args);
void t34Rast32(ArgList *args);
void t35Rast32(ArgList *args);

void regRast16Tests(BOOL blackScreen, BOOL destructive);
void t1Rast16(ArgList *args);
void t2Rast16(ArgList *args);
void t3Rast16(ArgList *args);
void t4Rast16(ArgList *args);
void t5Rast16(ArgList *args);
void t6Rast16(ArgList *args);
void t7Rast16(ArgList *args);
void t8Rast16(ArgList *args);
void t9Rast16(ArgList *args);
void t10Rast16(ArgList *args);
void t11Rast16(ArgList *args);
void t12Rast16(ArgList *args);
void t13Rast16(ArgList *args);
void t14Rast16(ArgList *args);
void t15Rast16(ArgList *args);
void t16Rast16(ArgList *args);
void t17Rast16(ArgList *args);
void t18Rast16(ArgList *args);
void t19Rast16(ArgList *args);
void t20Rast16(ArgList *args);
void t21Rast16(ArgList *args);
void t22Rast16(ArgList *args);
void t23Rast16(ArgList *args);
void t24Rast16(ArgList *args);
void t25Rast16(ArgList *args);
void t26Rast16(ArgList *args);
void t27Rast16(ArgList *args);
void t28Rast16(ArgList *args);
void t29Rast16(ArgList *args);
void t30Rast16(ArgList *args);
void t31Rast16(ArgList *args);
void t32Rast16(ArgList *args);
void t33Rast16(ArgList *args);
void t34Rast16(ArgList *args);
void t35Rast16(ArgList *args);

void tst_plot_rast8(UINT8 *base, BOOL destruct, BOOL blackScreen);

void regRectAreaTests();
void t1RectArea(ArgList *args);
void t2RectArea(ArgList *args);
void t3RectArea(ArgList *args);
void t4RectArea(ArgList *args);
void t5RectArea(ArgList *args);
void t6RectArea(ArgList *args);
void t7RectArea(ArgList *args);
void t8RectArea(ArgList *args);
void t9RectArea(ArgList *args);
void t10RectArea(ArgList *args);
void t11RectArea(ArgList *args);
void t12RectArea(ArgList *args);
void t13RectArea(ArgList *args);

void regClrAreaTests();
void t1ClrArea(ArgList *args);
void t2ClrArea(ArgList *args);
void t3ClrArea(ArgList *args);
void t4ClrArea(ArgList *args);
void t5ClrArea(ArgList *args);
void t6ClrArea(ArgList *args);
void t7ClrArea(ArgList *args);
void t8ClrArea(ArgList *args);
void t9ClrArea(ArgList *args);
void t10ClrArea(ArgList *args);
void t11ClrArea(ArgList *args);
void t12ClrArea(ArgList *args);
void t13ClrArea(ArgList *args);

void gridDots(UINT32 *base);

int main()
{
	TestSuite *tstSuite;
	TestCase  *tstCase;

	int promptResponse;
	BOOL validResponse;

	Vector origKybd;

	regPlotPxTests(BLACK_SCREEN_OFF);
	regPlotPxTests(BLACK_SCREEN_ON);

	regRast32Tests(BLACK_SCREEN_OFF, DESTRUCT_OFF);
	regRast32Tests(BLACK_SCREEN_OFF, DESTRUCT_ON);
	regRast32Tests(BLACK_SCREEN_ON, DESTRUCT_OFF);
	regRast32Tests(BLACK_SCREEN_ON, DESTRUCT_ON);

	regRast16Tests(BLACK_SCREEN_OFF, DESTRUCT_OFF);
	regRast16Tests(BLACK_SCREEN_OFF, DESTRUCT_ON);
	regRast16Tests(BLACK_SCREEN_ON, DESTRUCT_OFF);
	regRast16Tests(BLACK_SCREEN_ON, DESTRUCT_ON);

	regHlineTests();
	regRectAreaTests();
	regClrAreaTests();

	while ((tstSuite = getNextTestSuite()) != NULL)
	{
		showTestSuiteInfo(stdout, tstSuite);

		origKybd = initKybd();
		do
		{
			showTestPrompt(stdout);
			promptResponse = getBAscii();
			validResponse = (promptResponse == '\r' || promptResponse == 'q');
		} while (!validResponse);
		restoreKybd(origKybd);

		if (promptResponse == '\r')
		{
			while ((tstCase = getNextTestCase(tstSuite)) != NULL)
			{
				showTestCaseInfo(stdout, tstCase);

				origKybd = initKybd();
				do
				{
					showTestPrompt(stdout);
					promptResponse = getBAscii();
					validResponse = (promptResponse == '\r' ||
									 promptResponse == 'q');
				} while (!validResponse);
				restoreKybd(origKybd);
				
				if (promptResponse == '\r')
				{
					runTest(tstCase);
				}
			}
		}
	}

	return 0;
}

/**
 * @brief Sets up a blank white screen for testing the raster functions.
 * 
 * @param tstFunc The function to test the raster functions.
 */
void rastTstWhite(void (*tstFunc)(ArgList *args))
{
	rastTstCommon(tstFunc, BLACK_SCREEN_OFF, GRID_DOTS_OFF, DESTRUCT_ON);
}

/**
 * @brief Sets up a blank white screen for testing the raster functions and
 * configures the functions such that any existing imagery doesn't get
 * destroyed.
 * 
 * @param tstFunc The function to test the raster functions.
 */
void rastTstWhitePerserve(void (*tstFunc)(ArgList *args))
{
	rastTstCommon(tstFunc, BLACK_SCREEN_OFF, GRID_DOTS_OFF, DESTRUCT_OFF);
}

/**
 * @brief Sets up a white screen with uniformly distributed dots for testing the
 * raster functions.
 * 
 * @param tstFunc The function to test the raster functions.
 */
void rastGDTstWhite(void (*tstFunc)(ArgList *args))
{
	rastTstCommon(tstFunc, BLACK_SCREEN_OFF, GRID_DOTS_ON, DESTRUCT_ON);
}

/**
 * @brief Sets up a blank black screen for testing the raster functions.
 * 
 * @param tstFunc The function to test the raster functions.
 */
void rastTstBlack(void (*tstFunc)(ArgList *args))
{
	rastTstCommon(tstFunc, BLACK_SCREEN_ON, GRID_DOTS_OFF, DESTRUCT_ON);
}

/**
 * @brief Sets up a blank black screen for testing the raster functions and
 * configures the functions such that any existing imagery doesn't get
 * destroyed.
 * 
 * @param tstFunc The function to test the raster functions.
 */
void rastTstBlackPerserve(void (*tstFunc)(ArgList *args))
{
	rastTstCommon(tstFunc, BLACK_SCREEN_ON, GRID_DOTS_OFF, DESTRUCT_OFF);
}

/**
 * @brief Sets up a black screen with uniformly distributed dots for testing the
 * raster functions.
 * 
 * @param tstFunc The function to test the raster functions.
 */
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

	restoreKybd(origKybd);
}

/**
 * @brief Handle the registration of all tests related to the plot_px()
 * function.
 * 
 * @param blackScreen Whether the tests registered should utilize a blank white
 * or black screen.
 */
void regPlotPxTests(BOOL blackScreen)
{
	TestSuiteID suiteID;

	if (blackScreen)
	{
		suiteID = registerTestSuite("Tests plotting pixels on a black surface.",
									rastTstBlack);
	}
	else
	{
		suiteID = registerTestSuite("Tests plotting pixels on a white surface.",
									rastTstWhite);
	}
	
	registerTestCase(suiteID,
					 "When both x and y are at their minimum value (zero).",
					 NULL, t1PlotPx);

	registerTestCase(suiteID,
					 "When x is at its middle value and y is at its minimum value.",
					 NULL, t2PlotPx);

	registerTestCase(suiteID,
					 "When x is at its maximum value and y is at its minimum value.",
					 NULL, t3PlotPx);

	registerTestCase(suiteID,
					 "When x is at its minimum value and y is at its middle value.",
					 NULL, t4PlotPx);

	registerTestCase(suiteID,
					 "When x is at its minimum value and y is at its maximum value.",
					 NULL, t5PlotPx);

	registerTestCase(suiteID,
					 "When both x and y are at their maximum values.",
					 NULL, t6PlotPx);

	registerTestCase(suiteID,
					 "When both x and y are at their middle values.",
					 NULL, t7PlotPx);

	registerTestCase(suiteID,
					 "When x is negative.",
					 NULL, t8PlotPx);

	registerTestCase(suiteID,
					 "When x is equal to the length of the screen.",
					 NULL, t9PlotPx);

	registerTestCase(suiteID,
					 "When x is greater than the length of the screen.",
					 NULL, t10PlotPx);

	registerTestCase(suiteID,
					 "When y is negative.",
					 NULL, t11PlotPx);

	registerTestCase(suiteID,
					 "When y is equal to the screen height.",
					 NULL, t12PlotPx);

	registerTestCase(suiteID,
					 "When y is greater than the screen height.",
					 NULL, t13PlotPx);
}

/**
 * @brief Tests plot_px() when both x and y are at their minimum value (zero).
 * @details The expected results are that a point will be plotted in the
 * top-left corner of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t1PlotPx(ArgList *args)
{
	plot_px((UINT8 *)getArgFromList("base", args), 0, 0);
}

/**
 * @brief Tests plot_px() when x is at its middle value and y is at its minimum
 * value.
 * @details The expected results are that a point will be plotted on the
 * top-middle portion of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t2PlotPx(ArgList *args)
{
	plot_px((UINT8 *)getArgFromList("base", args), SCRN_MID_X, 0);
}

/**
 * @brief Tests plot_px() when x is at its maximum value and y is at its minimum
 * value.
 * @details The expected results are that a point will be plotted in the
 * top-right corner of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t3PlotPx(ArgList *args)
{
	plot_px((UINT8 *)getArgFromList("base", args), SCRN_MAX_X, 0);
}

/**
 * @brief Tests plot_px() when x is at its minimum value and y is at its middle
 * value.
 * @details The expected results are that a point will be plotted on the left
 * and vertically centered on the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t4PlotPx(ArgList *args)
{
	plot_px((UINT8 *)getArgFromList("base", args), 0, SCRN_MID_Y);
}

/**
 * @brief Tests plot_px() when x is at its minimum value and y is at its maximum
 * value.
 * @details The expected results are that a point will be plotted in the
 * bottom-left corner of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t5PlotPx(ArgList *args)
{
	plot_px((UINT8 *)getArgFromList("base", args), 0, SCRN_MAX_Y);
}

/**
 * @brief Tests plot_px() when both x and y are at their maximum values.
 * @details The expected results are that a point will be plotted in the
 * bottom-right corner of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t6PlotPx(ArgList *args)
{
	plot_px((UINT8 *)getArgFromList("base", args), SCRN_MAX_X, SCRN_MAX_Y);
}

/**
 * @brief Tests plot_px() when both x and y are at their middle values.
 * @details The expected results are that a point will be plotted in the center
 * of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t7PlotPx(ArgList *args)
{
	plot_px((UINT8 *)getArgFromList("base", args), SCRN_MID_X, SCRN_MID_Y);
}

/**
 * @brief Tests plot_px() when x is negative.
 * @details The expected results are that nothing will be plotted on screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t8PlotPx(ArgList *args)
{
	plot_px((UINT8 *)getArgFromList("base", args), -1, 0);
}

/**
 * @brief Tests plot_px() when x is equal to the length of the screen.
 * @details The expected results are that nothing will be plotted on screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t9PlotPx(ArgList *args)
{
	plot_px((UINT8 *)getArgFromList("base", args), SCRN_LEN, 0);
}

/**
 * @brief Tests plot_px() when x is greater than the length of the screen.
 * @details The expected results are that nothing will be plotted on screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t10PlotPx(ArgList *args)
{
	plot_px((UINT8 *)getArgFromList("base", args), SCRN_LEN + 1, 0);
}

/**
 * @brief Tests plot_px() when y is negative.
 * @details The expected results are that nothing will be plotted on screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t11PlotPx(ArgList *args)
{
	plot_px((UINT8 *)getArgFromList("base", args), 0, -1);
}

/**
 * @brief Tests plot_px() when y is equal to the height of the screen.
 * @details The expected results are that nothing will be plotted on screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t12PlotPx(ArgList *args)
{
	plot_px((UINT8 *)getArgFromList("base", args), 0, SCRN_HEIGHT);
}

/**
 * @brief Tests plot_px() when y is greater than the height of the screen.
 * @details The expected results are that nothing will be plotted on screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t13PlotPx(ArgList *args)
{
	plot_px((UINT8 *)getArgFromList("base", args), 0, SCRN_HEIGHT + 1);
}

/**
 * @brief Handle the registration of all tests related to the hline() function.
 */
void regHlineTests()
{
	TestSuiteID suiteID;

	suiteID = registerTestSuite("Tests drawing horizontal lines.", rastTstWhite);

	registerTestCase(suiteID, "When y is at its minimum value (zero).", NULL,
					 t1Hline);

	registerTestCase(suiteID, "When y is at its middle value.", NULL, t2Hline);

	registerTestCase(suiteID, "When y is at its maximum value.", NULL, t3Hline);

	registerTestCase(suiteID, "When the length of the line is 32-bit aligned and x1 is greater than x2.", NULL, t4Hline);

	registerTestCase(suiteID, "When the length of the line is 16-bit aligned and x1 is less than x2.", NULL, t5Hline);

	registerTestCase(suiteID, "When the length of the line is 16-bit aligned and x1 is greater than x2.", NULL, t6Hline);

	registerTestCase(suiteID, "When the length of the line is 8-bit aligned and x1 is less than x2.", NULL, t7Hline);

	registerTestCase(suiteID, "When the length of the line is 8-bit aligned and x1 is greater than x2.", NULL, t8Hline);

	registerTestCase(suiteID, "When the length of the line is not 8-bit aligned and x1 is less than x2.", NULL, t9Hline);

	registerTestCase(suiteID, "When the length of the line is not 8-bit aligned and x1 is greater than x2.", NULL, t10Hline);

	registerTestCase(suiteID, "When the line does not start at the very left of the screen and is within a 32-bit segment.", NULL, t11Hline);

	registerTestCase(suiteID, "When the line does not start at zero and has no middle segments.", NULL, t12Hline);

	registerTestCase(suiteID, "When x1 and x2 are at their minimum visible value.", NULL, t13Hline);

	registerTestCase(suiteID, "When x1 and x2 are at their middle visible value.", NULL, t14Hline);

	registerTestCase(suiteID, "When x1 and x2 are at their maximum visible value.", NULL, t15Hline);

	registerTestCase(suiteID, "When x1 is off the screen to the left and x2 is barely on the screen.", NULL, t16Hline);

	registerTestCase(suiteID, "When x1 is barely on the screen and x2 is off the screen to the right.", NULL, t17Hline);

	registerTestCase(suiteID, "When x1 and x2 are at their minimum and maximum visible value on the screen respectively.", NULL, t18Hline);

	registerTestCase(suiteID, "When x1 and x2 are off the screen to the left and right respectively.", NULL, t19Hline);

	registerTestCase(suiteID, "When the function is executed repeatedly such that it prints lines of different lengths.", NULL, t20Hline);

	registerTestCase(suiteID, "When y is negative.", NULL, t21Hline);

	registerTestCase(suiteID, "When y is equal to the screen height.", NULL,
					 t22Hline);

	registerTestCase(suiteID, "When y is greater than the screen height.", NULL,
					 t23Hline);

	registerTestCase(suiteID, "When x1 and x2 are off the screen to the left and x1 is less than x2.", NULL, t24Hline);

	registerTestCase(suiteID, "When x1 and x2 are off the screen to the left and x1 is equal to x2.", NULL, t25Hline);

	registerTestCase(suiteID, "When x1 and x2 are off the screen to the left and x1 is greater than x2.", NULL, t26Hline);

	registerTestCase(suiteID, "When x1 and x2 are off the screen to the right and x1 is less than x2.", NULL, t27Hline);

	registerTestCase(suiteID, "When x1 and x2 are off the screen to the right and x1 is equal to x2.", NULL, t28Hline);

	registerTestCase(suiteID, "when x1 and x2 are off the screen to the right and x1 is greater than x2.", NULL, t29Hline);
}

/**
 * @brief Tests plot_hline() when y is at its minimum value (zero).
 * @details The expected results are that a 32 px long horizontal line will be
 * drawn starting at the top-left corner of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t1Hline(ArgList *args)
{
	hline((UINT32 *)getArgFromList("base", args), 0, 31, 0);
}

/**
 * @brief Tests plot_hline() when y is at its middle value.
 * @details The expected results are that a 32 px long horizontal line will be
 * drawn vertically-centered starting at the left of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t2Hline(ArgList *args)
{
	hline((UINT32 *)getArgFromList("base", args), 0, 31, SCRN_MID_Y);
}

/**
 * @brief Tests plot_hline() when y is at its maximum value.
 * @details The expected results are that a 32 px long horizontal line will be
 * drawn starting at the bottom-left corner of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t3Hline(ArgList *args)
{
	hline((UINT32 *)getArgFromList("base", args), 0, 31, SCRN_MAX_Y);
}

/**
 * @brief Tests plot_hline() when the length of the line is 32-bit aligned and
 * x1 is greater than x2.
 * @details The expected results are that a 32 px long horizontal line will be
 * drawn starting at the top-left corner of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t4Hline(ArgList *args)
{
	hline((UINT32 *)getArgFromList("base", args), 31, 0, 0);
}

/**
 * @brief Tests plot_hline() when the length of the line is 16-bit aligned and
 * x1 is less than x2.
 * @details The expected results are that a 16 px long horizontal line will be
 * drawn starting at the top-left corner of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t5Hline(ArgList *args)
{
	hline((UINT32 *)getArgFromList("base", args), 0, 15, 0);
}

/**
 * @brief Tests plot_hline() when the length of the line is 16-bit aligned and
 * x1 is greater than x2.
 * @details The expected results are that a 16 px long horizontal line will be
 * drawn starting at the top-left corner of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t6Hline(ArgList *args)
{
	hline((UINT32 *)getArgFromList("base", args), 15, 0, 0);
}

/**
 * @brief Tests plot_hline() when the length of the line is 8-bit aligned and
 * x1 is less than x2.
 * @details The expected results are that a 8 px long horizontal line will be
 * drawn starting at the top-left corner of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t7Hline(ArgList *args)
{
	hline((UINT32 *)getArgFromList("base", args), 0, 7, 0);
}

/**
 * @brief Tests plot_hline() when the length of the line is 8-bit aligned and
 * x1 is greater than x2.
 * @details The expected results are that a 8 px long horizontal line will be
 * drawn starting at the top-left corner of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t8Hline(ArgList *args)
{
	hline((UINT32 *)getArgFromList("base", args), 7, 0, 0);
}

/**
 * @brief Tests plot_hline() when the length of the line is not 8-bit aligned
 * and x1 is less than x2.
 * @details The expected results are that a 7 px long horizontal line will be
 * drawn starting at the top-left corner of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t9Hline(ArgList *args)
{
	hline((UINT32 *)getArgFromList("base", args), 0, 6, 0);
}

/**
 * @brief Tests plot_hline() when the length of the line is not 8-bit aligned
 * and x1 is greater than x2.
 * @details The expected results are that a 7 px long horizontal line will be
 * drawn starting at the top-left corner of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t10Hline(ArgList *args)
{
	hline((UINT32 *)getArgFromList("base", args), 6, 0, 0);
}

/**
 * @brief Tests plot_hline() when the line does not start at the very left of
 * the screen and is within a 32-bit segment.
 * @details The expected results are that a 26 px long horizontal line will be
 * drawn three pixels in from the top-left corner of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t11Hline(ArgList *args)
{
	hline((UINT32 *)getArgFromList("base", args), 3, 28, 0);
}

/**
 * @brief Tests plot_hline() when the line does not start at zero and has no
 * middle segments.
 * @details The expected results are that a 8 px long horizontal line will be
 * drawn at the top of the screen starting at 29 pixels from the left.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t12Hline(ArgList *args)
{
	hline((UINT32 *)getArgFromList("base", args), 28, 35, 0);
}

/**
 * @brief Tests plot_hline() when x1 and x2 are at their minimum visible value.
 * @details The expected results are that a 1 px wide dot will be in the
 * top-left corner of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t13Hline(ArgList *args)
{
	hline((UINT32 *)getArgFromList("base", args), 0, 0, 0);
}

/**
 * @brief Tests plot_hline() when x1 and x2 are at their middle visible value.
 * @details The expected results are that a 1 px wide dot will be in the
 * top-center position of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t14Hline(ArgList *args)
{
	hline((UINT32 *)getArgFromList("base", args), SCRN_MID_X, SCRN_MID_X, 0);
}

/**
 * @brief Tests plot_hline() when x1 and x2 are at their maximum visible value.
 * @details The expected results are that a 1 px wide dot will be in the
 * top-right corner of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t15Hline(ArgList *args)
{
	hline((UINT32 *)getArgFromList("base", args), SCRN_MAX_X, SCRN_MAX_X, 0);
}

/**
 * @brief Tests plot_hline() when x1 is off the screen to the left and x2 is
 * barely on the screen.
 * @details The expected results are that a 1 px wide dot will be in the
 * top-left corner of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t16Hline(ArgList *args)
{
	hline((UINT32 *)getArgFromList("base", args), -1, 0, 0);
}

/**
 * @brief Tests plot_hline() when x1 is barely on the screen and x2 is off the
 * screen to the right.
 * @details The expected results are that a 1 px wide dot will be in the
 * top-right corner of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t17Hline(ArgList *args)
{
	hline((UINT32 *)getArgFromList("base", args), SCRN_MAX_X, SCRN_LEN, 0);
}

/**
 * @brief Tests plot_hline() when x1 and x2 are at their minimum and maximum
 * visible value on the screen respectively.
 * @details The expected results are that a horizontal line will extend across
 * the very bottom of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t18Hline(ArgList *args)
{
	hline((UINT32 *)getArgFromList("base", args), 0, SCRN_MAX_X, SCRN_MAX_Y);
}

/**
 * @brief Tests plot_hline() when x1 and x2 are off the screen to the left and
 * right respectively.
 * @details The expected results are that a horizontal line will extend across
 * the very bottom of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t19Hline(ArgList *args)
{
	hline((UINT32 *)getArgFromList("base", args), -1, SCRN_LEN, SCRN_MAX_Y);
}

/**
 * @brief Tests plot_hline() when the function is executed repeatedly such that
 * it prints lines of different lengths.
 * @details The expected results are that a large downward facing triangle
 * (whose initial length spans the entire length of the screen) will appear from
 * the top of the screen. Connected to that triangle is a smaller one facing the
 * other direction. Both triangles are completely filled in and together, they
 * take up the entire height of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t20Hline(ArgList *args)
{
	int counter;

	for(counter = -1; counter < SCRN_HEIGHT; counter++)
	{
		hline((UINT32 *)getArgFromList("base", args), counter,
			  SCRN_MAX_X - counter, counter);
	}
}

/**
 * @brief Tests plot_hline() when y is negative.
 * @details The expected results are that nothing will be plotted on screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t21Hline(ArgList *args)
{
	hline((UINT32 *)getArgFromList("base", args), 0, 31, -1);
}

/**
 * @brief Tests plot_hline() when y is equal to the screen height.
 * @details The expected results are that nothing will be plotted on screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t22Hline(ArgList *args)
{
	hline((UINT32 *)getArgFromList("base", args), 0, 31, SCRN_HEIGHT);
}

/**
 * @brief Tests plot_hline() when y is greater than the screen height.
 * @details The expected results are that nothing will be plotted on screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t23Hline(ArgList *args)
{
	hline((UINT32 *)getArgFromList("base", args), 0, 31, SCRN_HEIGHT + 1);
}

/**
 * @brief Tests plot_hline() when x1 and x2 are off the screen to the left and
 * x1 is less than x2.
 * @details The expected results are that nothing will be plotted on screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t24Hline(ArgList *args)
{
	hline((UINT32 *)getArgFromList("base", args), -94, -31, SCRN_MAX_Y);
}

/**
 * @brief Tests plot_hline() when x1 and x2 are off the screen to the left and
 * x1 is equal to x2.
 * @details The expected results are that nothing will be plotted on screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t25Hline(ArgList *args)
{
	hline((UINT32 *)getArgFromList("base", args), -1, -1, SCRN_MAX_Y);
}

/**
 * @brief Tests plot_hline() when x1 and x2 are off the screen to the left and
 * x1 is greater than x2.
 * @details The expected results are that nothing will be plotted on screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t26Hline(ArgList *args)
{
	hline((UINT32 *)getArgFromList("base", args), -31, -94, SCRN_MAX_Y);
}

/**
 * @brief Tests plot_hline() when x1 and x2 are off the screen to the right and
 * x1 is less than x2.
 * @details The expected results are that nothing will be plotted on screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t27Hline(ArgList *args)
{
	hline((UINT32 *)getArgFromList("base", args), SCRN_MAX_X + 32,
		  SCRN_MAX_X + 64, 0);
}

/**
 * @brief Tests plot_hline() when x1 and x2 are off the screen to the right and
 * x1 is equal to x2.
 * @details The expected results are that nothing will be plotted on screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t28Hline(ArgList *args)
{
	hline((UINT32 *)getArgFromList("base", args), SCRN_LEN, SCRN_LEN, 0);
}

/**
 * @brief Tests plot_hline() when x1 and x2 are off the screen to the right and
 * x1 is greater than x2.
 * @details The expected results are that nothing will be plotted on screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t29Hline(ArgList *args)
{
	hline((UINT32 *)getArgFromList("base", args), SCRN_MAX_X + 64,
		  SCRN_MAX_X + 32, 0);
}

/**
 * @brief Handle the registration of all tests related to the plot_rast32()
 * function.
 * 
 * @param blackScreen Whether the tests registered should utilize a blank white
 * or black screen.
 * @param destructive Whether the tests registered should destroy any existing
 * imagery on the surface or not.
 */
void regRast32Tests(BOOL blackScreen, BOOL destructive)
{
	TestSuiteID suiteID;

	if (blackScreen)
	{
		if (destructive)
		{
			suiteID = registerTestSuite("Tests plotting 32px wide bitmaps destructively on a black surface.",
										rastTstBlack);
		}
		else
		{
			suiteID = registerTestSuite("Tests plotting 32px wide bitmaps non-destructively on a black surface.",
										rastTstBlackPerserve);
		}
	}
	else
	{
		if (destructive)
		{
			suiteID = registerTestSuite("Tests plotting 32px wide bitmaps destructively on a white surface.",
										rastTstWhite);
		}
		else
		{
			suiteID = registerTestSuite("Tests plotting 32px wide bitmaps non-destructively on a white surface.",
										rastTstWhitePerserve);
		}
	}

	registerTestCase(suiteID, "When both x and y are at their minimum value (zero).",
					 NULL, t1Rast32);

	registerTestCase(suiteID, "When x is set to a value corresponding to the middle of the screen.",
					 NULL, t2Rast32);

	registerTestCase(suiteID, "When x is set to the maximum value it can be without getting the image cropped.",
					 NULL, t3Rast32);

	registerTestCase(suiteID, "When y is set to a value corresponding to the middle of the screen.",
					 NULL, t4Rast32);

	registerTestCase(suiteID, "When x and y are set to a value corresponding to the middle of the screen.",
					 NULL, t5Rast32);

	registerTestCase(suiteID, "When y is set to the maximum value it can be without getting the image cropped.",
					 NULL, t6Rast32);
	
	registerTestCase(suiteID, "When x and y are set to their maximum values they can have without getting the image cropped.",
					 NULL, t7Rast32);

	registerTestCase(suiteID, "When x is set to a value such that the center of the image is at the horizontal center of the screen.",
					 NULL, t8Rast32);

	registerTestCase(suiteID, "When y is set to a value such that the center of the image is at the vertical center of the screen.",
					 NULL, t9Rast32);

	registerTestCase(suiteID, "When x and y are set to values such that the center of the image is in the center of the screen.",
					 NULL, t10Rast32);

	registerTestCase(suiteID, "When x is set to a value such that the image is cropped by 1px from the left.",
					 NULL, t11Rast32);

	registerTestCase(suiteID, "When x is set to a value such that half of the image is cropped from the left.",
					 NULL, t12Rast32);
	
	registerTestCase(suiteID, "When x is set to a value such that only the rightmost column constituting the image is on screen.",
					 NULL, t13Rast32);

	registerTestCase(suiteID, "When y is set to a value such that the image is cropped by 1px from the top.",
					 NULL, t14Rast32);

	registerTestCase(suiteID, "When y is set to a value such that the top half of the image is cropped off.",
					 NULL, t15Rast32);

	registerTestCase(suiteID, "When y is set to a value such that only the bottommost row constituting the image is on screen.",
					 NULL, t16Rast32);

	registerTestCase(suiteID, "When x is set to a value such that the image is cropped by 1px from the right.",
					 NULL, t17Rast32);

	registerTestCase(suiteID, "When x is set to a value such that half of the image is cropped from the right.",
					 NULL, t18Rast32);

	registerTestCase(suiteID, "When x is set to a value such that only the leftmost column constituting the image is on screen.",
					 NULL, t19Rast32);

	registerTestCase(suiteID, "When y is set to a value such that the image is cropped by 1px from the bottom.",
					 NULL, t20Rast32);
	
	registerTestCase(suiteID, "When y is set to a value such that the bottom half of the image is cropped off.",
					 NULL, t21Rast32);

	registerTestCase(suiteID, "When y is set to a value such that only the topmost row constituting the image is on screen.",
					 NULL, t22Rast32);

	registerTestCase(suiteID, "When the height is set to its minimum possible value.",
					 NULL, t23Rast32);

	registerTestCase(suiteID, "When the height is set to half of the screen's height.",
					 NULL, t24Rast32);

	registerTestCase(suiteID, "When the height given is just below the maximum height of the screen.",
					 NULL, t25Rast32);

	registerTestCase(suiteID, "When the height given is equal to the maximum height of the screen.",
					 NULL, t26Rast32);
	
	registerTestCase(suiteID, "When the height given is greater than the maximum height of the screen.",
					 NULL, t27Rast32);

	registerTestCase(suiteID, "When the height is zero.",
					 NULL, t28Rast32);

	registerTestCase(suiteID, "When the height is negative.",
					 NULL, t29Rast32);

	registerTestCase(suiteID, "When x is 32px off the screen to the left.",
					 NULL, t30Rast32);

	registerTestCase(suiteID, "When x is equal to the screen length.",
					 NULL, t31Rast32);

	registerTestCase(suiteID, "When x is greater than the screen length.",
					 NULL, t32Rast32);

	registerTestCase(suiteID, "When y is 32px upwards off the screen.",
					 NULL, t33Rast32);

	registerTestCase(suiteID, "When y is equal to the screen height.",
					 NULL, t34Rast32);

	registerTestCase(suiteID, "When y is greater than the screen height.",
					 NULL, t35Rast32);
}

/**
 * @brief Tests plot_rast32() when both x and y are at their minimum value
 * (zero).
 * @details The expected results are that a image will be plotted starting from
 * the top-left corner of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t1Rast32(ArgList *args)
{
	const int LEN    = 32;
	const int HEIGHT = 32;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT32 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast32((UINT32 *)getArgFromList("base", args), 0, 0, HEIGHT, img,
				destructive, blackScreen);
}

/**
 * @brief Tests plot_rast32() when x is set to a value corresponding to the
 * middle of the screen.
 * @details The expected results are that a image will be plotted starting from
 * the top-center portion of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t2Rast32(ArgList *args)
{
	const int LEN    = 32;
	const int HEIGHT = 32;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT32 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast32((UINT32 *)getArgFromList("base", args), SCRN_MID_X, 0, HEIGHT,
				img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast32() when x is set to the maximum value it can be
 * without getting the image cropped.
 * @details The expected results are that a image will be plotted starting from
 * the top-right portion of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t3Rast32(ArgList *args)
{
	const int LEN    = 32;
	const int HEIGHT = 32;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT32 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast32((UINT32 *)getArgFromList("base", args), RAST32_MAX_VIS_X, 0,
				HEIGHT, img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast32() when y is set to a value corresponding to the
 * middle of the screen.
 * @details The expected results are that a image will be plotted starting from
 * the center-left portion of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t4Rast32(ArgList *args)
{
	const int LEN    = 32;
	const int HEIGHT = 32;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT32 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast32((UINT32 *)getArgFromList("base", args), 0, SCRN_MID_Y, HEIGHT,
				img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast32() when x and y are set to a value corresponding to
 * the middle of the screen.
 * @details The expected results are that a image will be plotted starting at
 * the center of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t5Rast32(ArgList *args)
{
	const int LEN    = 32;
	const int HEIGHT = 32;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT32 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast32((UINT32 *)getArgFromList("base", args), SCRN_MID_X, SCRN_MID_Y,
				HEIGHT, img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast32() when y is set to the maximum value it can be
 * without getting the image cropped.
 * @details The expected results are that a image will be plotted close to the
 * bottom-left portion of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t6Rast32(ArgList *args)
{
	const int LEN    = 32;
	const int HEIGHT = 32;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT32 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast32((UINT32 *)getArgFromList("base", args), 0, RAST32H_MAX_VIS_Y,
				HEIGHT, img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast32() when x and y are set to their maximum values they
 * can have without getting the image cropped.
 * @details The expected results are that a image will be plotted close to the
 * bottom-right portion of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t7Rast32(ArgList *args)
{
	const int LEN    = 32;
	const int HEIGHT = 32;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT32 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast32((UINT32 *)getArgFromList("base", args), RAST32_MAX_VIS_X,
				RAST32H_MAX_VIS_Y, HEIGHT, img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast32() when x is set to a value such that the center of
 * the image is at the horizontal center of the screen.
 * @details The expected results are that a image will be plotted horizontally
 * centered at the top side of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t8Rast32(ArgList *args)
{
	const int LEN    = 32;
	const int HEIGHT = 32;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT32 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast32((UINT32 *)getArgFromList("base", args), RAST32_MID_VIS_X, 0,
				HEIGHT, img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast32() when y is set to a value such that the center of
 * the image is at the vertical center of the screen.
 * @details The expected results are that a image will be plotted vertically
 * centered at the left side of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t9Rast32(ArgList *args)
{
	const int LEN    = 32;
	const int HEIGHT = 32;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT32 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast32((UINT32 *)getArgFromList("base", args), 0, RAST32H_MID_VIS_Y,
				HEIGHT, img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast32() when x and y are set to values such that the
 * center of the image is in the center of the screen.
 * @details The expected results are that a image will be plotted centered on
 * the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t10Rast32(ArgList *args)
{
	const int LEN    = 32;
	const int HEIGHT = 32;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT32 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast32((UINT32 *)getArgFromList("base", args), RAST32_MID_VIS_X,
				RAST32H_MID_VIS_Y, HEIGHT, img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast32() when x is set to a value such that the image is
 * cropped by 1px from the left.
 * @details The expected results are that most of a image, except for the first
 * pixel from the left, will be plotted in the top-left corner of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t11Rast32(ArgList *args)
{
	const int LEN    = 32;
	const int HEIGHT = 32;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT32 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast32((UINT32 *)getArgFromList("base", args), -1, 0, HEIGHT, img,
				destructive, blackScreen);
}

/**
 * @brief Tests plot_rast32() when x is set to a value such that half of the
 * image is cropped from the left.
 * @details The expected results are that the second half of a image will be
 * plotted starting in the top-left corner of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t12Rast32(ArgList *args)
{
	const int LEN    = 32;
	const int HEIGHT = 32;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT32 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast32((UINT32 *)getArgFromList("base", args), RAST32_LHALF_X, 0,
				HEIGHT, img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast32() when x is set to a value such that only the
 * rightmost column constituting the image is on screen.
 * @details The expected results are that a 32px sliver of the rightmost column
 * of the image will appear on the top-left portion of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t13Rast32(ArgList *args)
{
	const int LEN    = 32;
	const int HEIGHT = 32;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT32 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast32((UINT32 *)getArgFromList("base", args), RAST32_MIN_X, 0, HEIGHT,
				img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast32() when y is set to a value such that the image is
 * cropped by 1px from the top.
 * @details The expected results are that most of a image, except the very top,
 * will be plotted in the top-left corner of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t14Rast32(ArgList *args)
{
	const int LEN    = 32;
	const int HEIGHT = 32;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT32 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast32((UINT32 *)getArgFromList("base", args), 0, -1, HEIGHT,
				img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast32() when y is set to a value such that the top half of
 * the image is cropped off.
 * @details The expected results are that a bottom half of the image will be
 * plotted in the top-left corner of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t15Rast32(ArgList *args)
{
	const int LEN    = 32;
	const int HEIGHT = 32;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT32 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast32((UINT32 *)getArgFromList("base", args), 0, RAST32H_THALF_Y,
				HEIGHT, img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast32() when y is set to a value such that only the
 * bottommost row constituting the image is on screen.
 * @details The expected results are that a 32px sliver of the bottommost row of
 * a image will appear on the top-left portion of the screen
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t16Rast32(ArgList *args)
{
	const int LEN    = 32;
	const int HEIGHT = 32;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT32 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast32((UINT32 *)getArgFromList("base", args), 0, RAST32H_MIN_Y,
				HEIGHT, img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast32() when x is set to a value such that the image is
 * cropped by 1px from the right.
 * @details The expected results are that most of a image, except for the first
 * pixels from the right, will be plotted in the top-right corner of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t17Rast32(ArgList *args)
{
	const int LEN    = 32;
	const int HEIGHT = 32;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT32 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast32((UINT32 *)getArgFromList("base", args), RAST32_MAX_VIS_X + 1, 0,
				HEIGHT, img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast32() when x is set to a value such that half of the
 * image is cropped from the right.
 * @details The expected results are that the first half of a image will be
 * plotted starting around the top-right position of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t18Rast32(ArgList *args)
{
	const int LEN    = 32;
	const int HEIGHT = 32;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT32 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast32((UINT32 *)getArgFromList("base", args), RAST32_RHALF_X, 0,
				HEIGHT, img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast32() when x is set to a value such that only the
 * leftmost column constituting the image is on screen.
 * @details The expected results are that a 32px sliver of the leftmost column
 * will appear on the top-right portion of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t19Rast32(ArgList *args)
{
	const int LEN    = 32;
	const int HEIGHT = 32;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT32 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast32((UINT32 *)getArgFromList("base", args), SCRN_MAX_X, 0, HEIGHT,
				img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast32() when y is set to a value such that the image is
 * cropped by 1px from the bottom.
 * @details The expected results are that most of a image, except the very
 * bottom, will be plotted in the bottom-left corner of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t20Rast32(ArgList *args)
{
	const int LEN    = 32;
	const int HEIGHT = 32;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT32 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast32((UINT32 *)getArgFromList("base", args), 0,
				RAST32H_MAX_VIS_Y + 1, HEIGHT, img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast32() when y is set to a value such that the bottom half
 * of the image is cropped off.
 * @details The expected results are that the first half of a image will be
 * plotted starting around the bottom-left position of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t21Rast32(ArgList *args)
{
	const int LEN    = 32;
	const int HEIGHT = 32;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT32 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast32((UINT32 *)getArgFromList("base", args), 0, RAST32H_BHALF_Y,
				HEIGHT, img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast32() when y is set to a value such that only the
 * topmost row constituting the image is on screen.
 * @details The expected results are that a 32px sliver of the topmost row of
 * a image will appear on the bottom-left portion of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t22Rast32(ArgList *args)
{
	const int LEN    = 32;
	const int HEIGHT = 32;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT32 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast32((UINT32 *)getArgFromList("base", args), 0, SCRN_MAX_Y, HEIGHT,
				img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast32() when the height is set to its minimum possible
 * value.
 * @details The expected results are that a 32px sliver of the topmost row of
 * a image will appear on the top-left corner of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t23Rast32(ArgList *args)
{
	const int LEN    = 32;
	const int HEIGHT = 1;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT32 img[SCRN_HEIGHT];

	memset(img, 0xFF, SCRN_HEIGHT * (LEN >> DIV_SHIFT_BY_8));

	plot_rast32((UINT32 *)getArgFromList("base", args), 0, SCRN_MAX_Y, HEIGHT,
				img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast32() when the height is set to half of the screen's
 * height.
 * @details The expected results are that a 32px image will be plotted in the
 * top-left corner of the screen that vertically takes up half the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t24Rast32(ArgList *args)
{
	const int LEN    = 32;
	const int HEIGHT = SCRN_HEIGHT / 2;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT32 img[SCRN_HEIGHT];

	memset(img, 0xFF, SCRN_HEIGHT * (LEN >> DIV_SHIFT_BY_8));

	plot_rast32((UINT32 *)getArgFromList("base", args), 0, SCRN_MAX_Y, HEIGHT,
				img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast32() when the height given is just below the maximum
 * height of the screen.
 * @details The expected results are that a 32px image will be plotted in the
 * top-left corner that extends vertically almost the entire screen except for
 * the bottom row.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t25Rast32(ArgList *args)
{
	const int LEN    = 32;
	const int HEIGHT = SCRN_HEIGHT - 1;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT32 img[SCRN_HEIGHT];

	memset(img, 0xFF, SCRN_HEIGHT * (LEN >> DIV_SHIFT_BY_8));

	plot_rast32((UINT32 *)getArgFromList("base", args), 0, SCRN_MAX_Y, HEIGHT,
				img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast32() when the height given is equal to the maximum
 * height of the screen.
 * @details The expected results are that a 32px image will be plotted in the
 * top-left corner that extends vertically across the entire screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t26Rast32(ArgList *args)
{
	const int LEN    = 32;
	const int HEIGHT = SCRN_HEIGHT;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT32 img[SCRN_HEIGHT];

	memset(img, 0xFF, SCRN_HEIGHT * (LEN >> DIV_SHIFT_BY_8));

	plot_rast32((UINT32 *)getArgFromList("base", args), 0, SCRN_MAX_Y, HEIGHT,
				img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast32() when the height given is greater than the maximum
 * height of the screen.
 * @details The expected results are that a 32px image will be plotted in the
 * top-left corner that extends vertically across the entire screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t27Rast32(ArgList *args)
{
	const int LEN    = 32;
	const int HEIGHT = SCRN_HEIGHT + 1;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT32 img[SCRN_HEIGHT];

	memset(img, 0xFF, SCRN_HEIGHT * (LEN >> DIV_SHIFT_BY_8));

	plot_rast32((UINT32 *)getArgFromList("base", args), 0, SCRN_MAX_Y, HEIGHT,
				img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast32() when the height is zero.
 * @details The expected results are that nothing will be plotted.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t28Rast32(ArgList *args)
{
	const int LEN    = 32;
	const int HEIGHT = 0;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT32 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast32((UINT32 *)getArgFromList("base", args), 0, 0, HEIGHT, img,
				destructive, blackScreen);
}

/**
 * @brief Tests plot_rast32() when the height is negative.
 * @details The expected results are that nothing will be plotted.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t29Rast32(ArgList *args)
{
	const int LEN    = 32;
	const int HEIGHT = -1;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT32 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast32((UINT32 *)getArgFromList("base", args), 0, 0, HEIGHT, img,
				destructive, blackScreen);
}

/**
 * @brief Tests plot_rast32() when x is 32px off the screen to the left.
 * @details The expected results are that nothing will be plotted.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t30Rast32(ArgList *args)
{
	const int LEN    = 32;
	const int HEIGHT = 32;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT32 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast32((UINT32 *)getArgFromList("base", args), -LEN, 0, HEIGHT, img,
				destructive, blackScreen);
}

/**
 * @brief Tests plot_rast32() when x is equal to the screen length.
 * @details The expected results are that nothing will be plotted.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t31Rast32(ArgList *args)
{
	const int LEN    = 32;
	const int HEIGHT = 32;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT32 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast32((UINT32 *)getArgFromList("base", args), SCRN_LEN, 0, HEIGHT,
				img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast32() when x is greater than the screen length.
 * @details The expected results are that nothing will be plotted.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t32Rast32(ArgList *args)
{
	const int LEN    = 32;
	const int HEIGHT = 32;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT32 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast32((UINT32 *)getArgFromList("base", args), SCRN_LEN + 1, 0, HEIGHT,
				img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast32() when y is 32px upwards off the screen.
 * @details The expected results are that nothing will be plotted.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t33Rast32(ArgList *args)
{
	const int LEN    = 32;
	const int HEIGHT = 32;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT32 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast32((UINT32 *)getArgFromList("base", args), 0, -HEIGHT, HEIGHT,
				img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast32() when y is equal to the screen height.
 * @details The expected results are that nothing will be plotted.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t34Rast32(ArgList *args)
{
	const int LEN    = 32;
	const int HEIGHT = 32;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT32 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast32((UINT32 *)getArgFromList("base", args), 0, SCRN_HEIGHT, HEIGHT,
				img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast32() when y is greater than the screen height.
 * @details The expected results are that nothing will be plotted.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t35Rast32(ArgList *args)
{
	const int LEN    = 32;
	const int HEIGHT = 32;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT32 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast32((UINT32 *)getArgFromList("base", args), 0, SCRN_HEIGHT + 1,
				HEIGHT, img, destructive, blackScreen);
}

/**
 * @brief Handle the registration of all tests related to the plot_rast16()
 * function.
 * 
 * @param blackScreen Whether the tests registered should utilize a blank white
 * or black screen.
 * @param destructive Whether the tests registered should destroy any existing
 * imagery on the surface or not.
 */
void regRast16Tests(BOOL blackScreen, BOOL destructive)
{
	TestSuiteID suiteID;

	if (blackScreen)
	{
		if (destructive)
		{
			suiteID = registerTestSuite("Tests plotting 16px wide bitmaps destructively on a black surface.",
										rastTstBlack);
		}
		else
		{
			suiteID = registerTestSuite("Tests plotting 16px wide bitmaps non-destructively on a black surface.",
										rastTstBlackPerserve);
		}
	}
	else
	{
		if (destructive)
		{
			suiteID = registerTestSuite("Tests plotting 16px wide bitmaps destructively on a white surface.",
										rastTstWhite);
		}
		else
		{
			suiteID = registerTestSuite("Tests plotting 16px wide bitmaps non-destructively on a white surface.",
										rastTstWhitePerserve);
		}
	}

	registerTestCase(suiteID, "When both x and y are at their minimum value (zero).",
					 NULL, t1Rast16);

	registerTestCase(suiteID, "When x is set to a value corresponding to the middle of the screen.",
					 NULL, t2Rast16);

	registerTestCase(suiteID, "When x is set to the maximum value it can be without getting the image cropped.",
					 NULL, t3Rast16);

	registerTestCase(suiteID, "When y is set to a value corresponding to the middle of the screen.",
					 NULL, t4Rast16);

	registerTestCase(suiteID, "When x and y are set to a value corresponding to the middle of the screen.",
					 NULL, t5Rast16);

	registerTestCase(suiteID, "When y is set to the maximum value it can be without getting the image cropped.",
					 NULL, t6Rast16);
	
	registerTestCase(suiteID, "When x and y are set to their maximum values they can have without getting the image cropped.",
					 NULL, t7Rast16);

	registerTestCase(suiteID, "When x is set to a value such that the center of the image is at the horizontal center of the screen.",
					 NULL, t8Rast16);

	registerTestCase(suiteID, "When y is set to a value such that the center of the image is at the vertical center of the screen.",
					 NULL, t9Rast16);

	registerTestCase(suiteID, "When x and y are set to values such that the center of the image is in the center of the screen.",
					 NULL, t10Rast16);

	registerTestCase(suiteID, "When x is set to a value such that the image is cropped by 1px from the left.",
					 NULL, t11Rast16);

	registerTestCase(suiteID, "When x is set to a value such that half of the image is cropped from the left.",
					 NULL, t12Rast16);
	
	registerTestCase(suiteID, "When x is set to a value such that only the rightmost column constituting the image is on screen.",
					 NULL, t13Rast16);

	registerTestCase(suiteID, "When y is set to a value such that the image is cropped by 1px from the top.",
					 NULL, t14Rast16);

	registerTestCase(suiteID, "When y is set to a value such that the top half of the image is cropped off.",
					 NULL, t15Rast16);

	registerTestCase(suiteID, "When y is set to a value such that only the bottommost row constituting the image is on screen.",
					 NULL, t16Rast16);

	registerTestCase(suiteID, "When x is set to a value such that the image is cropped by 1px from the right.",
					 NULL, t17Rast16);

	registerTestCase(suiteID, "When x is set to a value such that half of the image is cropped from the right.",
					 NULL, t18Rast16);

	registerTestCase(suiteID, "When x is set to a value such that only the leftmost column constituting the image is on screen.",
					 NULL, t19Rast16);

	registerTestCase(suiteID, "When y is set to a value such that the image is cropped by 1px from the bottom.",
					 NULL, t20Rast16);
	
	registerTestCase(suiteID, "When y is set to a value such that the bottom half of the image is cropped off.",
					 NULL, t21Rast16);

	registerTestCase(suiteID, "When y is set to a value such that only the topmost row constituting the image is on screen.",
					 NULL, t22Rast16);

	registerTestCase(suiteID, "When the height is set to its minimum possible value.",
					 NULL, t23Rast16);

	registerTestCase(suiteID, "When the height is set to half of the screen's height.",
					 NULL, t24Rast16);

	registerTestCase(suiteID, "When the height given is just below the maximum height of the screen.",
					 NULL, t25Rast16);

	registerTestCase(suiteID, "When the height given is equal to the maximum height of the screen.",
					 NULL, t26Rast16);
	
	registerTestCase(suiteID, "When the height given is greater than the maximum height of the screen.",
					 NULL, t27Rast16);

	registerTestCase(suiteID, "When the height is zero.",
					 NULL, t28Rast16);

	registerTestCase(suiteID, "When the height is negative.",
					 NULL, t29Rast16);

	registerTestCase(suiteID, "When x is 16px off the screen to the left.",
					 NULL, t30Rast16);

	registerTestCase(suiteID, "When x is equal to the screen length.",
					 NULL, t31Rast16);

	registerTestCase(suiteID, "When x is greater than the screen length.",
					 NULL, t32Rast16);

	registerTestCase(suiteID, "When y is 16px upwards off the screen.",
					 NULL, t33Rast16);

	registerTestCase(suiteID, "When y is equal to the screen height.",
					 NULL, t34Rast16);

	registerTestCase(suiteID, "When y is greater than the screen height.",
					 NULL, t35Rast16);
}

/**
 * @brief Tests plot_rast16() when both x and y are at their minimum value
 * (zero).
 * @details The expected results are that a image will be plotted starting from
 * the top-left corner of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t1Rast16(ArgList *args)
{
	const int LEN    = 16;
	const int HEIGHT = 16;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT16 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast16((UINT16 *)getArgFromList("base", args), 0, 0, HEIGHT, img,
				destructive, blackScreen);
}

/**
 * @brief Tests plot_rast16() when x is set to a value corresponding to the
 * middle of the screen.
 * @details The expected results are that a image will be plotted starting from
 * the top-center portion of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t2Rast16(ArgList *args)
{
	const int LEN    = 16;
	const int HEIGHT = 16;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT16 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast16((UINT16 *)getArgFromList("base", args), SCRN_MID_X, 0, HEIGHT,
				img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast16() when x is set to the maximum value it can be
 * without getting the image cropped.
 * @details The expected results are that a image will be plotted starting from
 * the top-right portion of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t3Rast16(ArgList *args)
{
	const int LEN    = 16;
	const int HEIGHT = 16;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT16 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast16((UINT16 *)getArgFromList("base", args), RAST16_MAX_VIS_X, 0,
				HEIGHT, img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast16() when y is set to a value corresponding to the
 * middle of the screen.
 * @details The expected results are that a image will be plotted starting from
 * the center-left portion of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t4Rast16(ArgList *args)
{
	const int LEN    = 16;
	const int HEIGHT = 16;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT16 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast16((UINT16 *)getArgFromList("base", args), 0, SCRN_MID_Y, HEIGHT,
				img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast16() when x and y are set to a value corresponding to
 * the middle of the screen.
 * @details The expected results are that a image will be plotted starting at
 * the center of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t5Rast16(ArgList *args)
{
	const int LEN    = 16;
	const int HEIGHT = 16;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT16 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast16((UINT16 *)getArgFromList("base", args), SCRN_MID_X, SCRN_MID_Y,
				HEIGHT, img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast16() when y is set to the maximum value it can be
 * without getting the image cropped.
 * @details The expected results are that a image will be plotted close to the
 * bottom-left portion of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t6Rast16(ArgList *args)
{
	const int LEN    = 16;
	const int HEIGHT = 16;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT16 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast16((UINT16 *)getArgFromList("base", args), 0, RAST16H_MAX_VIS_Y,
				HEIGHT, img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast16() when x and y are set to their maximum values they
 * can have without getting the image cropped.
 * @details The expected results are that a image will be plotted close to the
 * bottom-right portion of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t7Rast16(ArgList *args)
{
	const int LEN    = 16;
	const int HEIGHT = 16;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT16 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast16((UINT16 *)getArgFromList("base", args), RAST16_MAX_VIS_X,
				RAST16H_MAX_VIS_Y, HEIGHT, img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast16() when x is set to a value such that the center of
 * the image is at the horizontal center of the screen.
 * @details The expected results are that a image will be plotted horizontally
 * centered at the top side of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t8Rast16(ArgList *args)
{
	const int LEN    = 16;
	const int HEIGHT = 16;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT16 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast16((UINT16 *)getArgFromList("base", args), RAST16_MID_VIS_X, 0,
				HEIGHT, img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast16() when y is set to a value such that the center of
 * the image is at the vertical center of the screen.
 * @details The expected results are that a image will be plotted vertically
 * centered at the left side of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t9Rast16(ArgList *args)
{
	const int LEN    = 16;
	const int HEIGHT = 16;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT16 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast16((UINT16 *)getArgFromList("base", args), 0, RAST16H_MID_VIS_Y,
				HEIGHT, img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast16() when x and y are set to values such that the
 * center of the image is in the center of the screen.
 * @details The expected results are that a image will be plotted centered on
 * the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t10Rast16(ArgList *args)
{
	const int LEN    = 16;
	const int HEIGHT = 16;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT16 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast16((UINT16 *)getArgFromList("base", args), RAST16_MID_VIS_X,
				RAST16H_MID_VIS_Y, HEIGHT, img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast16() when x is set to a value such that the image is
 * cropped by 1px from the left.
 * @details The expected results are that most of a image, except for the first
 * pixel from the left, will be plotted in the top-left corner of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t11Rast16(ArgList *args)
{
	const int LEN    = 16;
	const int HEIGHT = 16;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT16 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast16((UINT16 *)getArgFromList("base", args), -1, 0, HEIGHT, img,
				destructive, blackScreen);
}

/**
 * @brief Tests plot_rast16() when x is set to a value such that half of the
 * image is cropped from the left.
 * @details The expected results are that the second half of a image will be
 * plotted starting in the top-left corner of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t12Rast16(ArgList *args)
{
	const int LEN    = 16;
	const int HEIGHT = 16;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT16 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast16((UINT16 *)getArgFromList("base", args), RAST16_LHALF_X, 0,
				HEIGHT, img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast16() when x is set to a value such that only the
 * rightmost column constituting the image is on screen.
 * @details The expected results are that a 16px sliver of the rightmost column
 * of the image will appear on the top-left portion of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t13Rast16(ArgList *args)
{
	const int LEN    = 16;
	const int HEIGHT = 16;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT16 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast16((UINT16 *)getArgFromList("base", args), RAST16_MIN_X, 0, HEIGHT,
				img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast16() when y is set to a value such that the image is
 * cropped by 1px from the top.
 * @details The expected results are that most of a image, except the very top,
 * will be plotted in the top-left corner of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t14Rast16(ArgList *args)
{
	const int LEN    = 16;
	const int HEIGHT = 16;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT16 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast16((UINT16 *)getArgFromList("base", args), 0, -1, HEIGHT,
				img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast16() when y is set to a value such that the top half of
 * the image is cropped off.
 * @details The expected results are that a bottom half of the image will be
 * plotted in the top-left corner of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t15Rast16(ArgList *args)
{
	const int LEN    = 16;
	const int HEIGHT = 16;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT16 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast16((UINT16 *)getArgFromList("base", args), 0, RAST16H_THALF_Y,
				HEIGHT, img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast16() when y is set to a value such that only the
 * bottommost row constituting the image is on screen.
 * @details The expected results are that a 16px sliver of the bottommost row of
 * a image will appear on the top-left portion of the screen
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t16Rast16(ArgList *args)
{
	const int LEN    = 16;
	const int HEIGHT = 16;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT16 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast16((UINT16 *)getArgFromList("base", args), 0, RAST16H_MIN_Y,
				HEIGHT, img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast16() when x is set to a value such that the image is
 * cropped by 1px from the right.
 * @details The expected results are that most of a image, except for the first
 * pixels from the right, will be plotted in the top-right corner of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t17Rast16(ArgList *args)
{
	const int LEN    = 16;
	const int HEIGHT = 16;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT16 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast16((UINT16 *)getArgFromList("base", args), RAST16_MAX_VIS_X + 1, 0,
				HEIGHT, img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast16() when x is set to a value such that half of the
 * image is cropped from the right.
 * @details The expected results are that the first half of a image will be
 * plotted starting around the top-right position of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t18Rast16(ArgList *args)
{
	const int LEN    = 16;
	const int HEIGHT = 16;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT16 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast16((UINT16 *)getArgFromList("base", args), RAST16_RHALF_X, 0,
				HEIGHT, img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast16() when x is set to a value such that only the
 * leftmost column constituting the image is on screen.
 * @details The expected results are that a 16px sliver of the leftmost column
 * will appear on the top-right portion of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t19Rast16(ArgList *args)
{
	const int LEN    = 16;
	const int HEIGHT = 16;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT16 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast16((UINT16 *)getArgFromList("base", args), SCRN_MAX_X, 0, HEIGHT,
				img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast16() when y is set to a value such that the image is
 * cropped by 1px from the bottom.
 * @details The expected results are that most of a image, except the very
 * bottom, will be plotted in the bottom-left corner of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t20Rast16(ArgList *args)
{
	const int LEN    = 16;
	const int HEIGHT = 16;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT16 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast16((UINT16 *)getArgFromList("base", args), 0,
				RAST16H_MAX_VIS_Y + 1, HEIGHT, img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast16() when y is set to a value such that the bottom half
 * of the image is cropped off.
 * @details The expected results are that the first half of a image will be
 * plotted starting around the bottom-left position of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t21Rast16(ArgList *args)
{
	const int LEN    = 16;
	const int HEIGHT = 16;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT16 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast16((UINT16 *)getArgFromList("base", args), 0, RAST16H_BHALF_Y,
				HEIGHT, img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast16() when y is set to a value such that only the
 * topmost row constituting the image is on screen.
 * @details The expected results are that a 16px sliver of the topmost row of
 * a image will appear on the bottom-left portion of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t22Rast16(ArgList *args)
{
	const int LEN    = 16;
	const int HEIGHT = 16;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT16 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast16((UINT16 *)getArgFromList("base", args), 0, SCRN_MAX_Y, HEIGHT,
				img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast16() when the height is set to its minimum possible
 * value.
 * @details The expected results are that a 16px sliver of the topmost row of
 * a image will appear on the top-left corner of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t23Rast16(ArgList *args)
{
	const int LEN    = 16;
	const int HEIGHT = 1;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT16 img[SCRN_HEIGHT];

	memset(img, 0xFF, SCRN_HEIGHT * (LEN >> DIV_SHIFT_BY_8));

	plot_rast16((UINT16 *)getArgFromList("base", args), 0, SCRN_MAX_Y, HEIGHT,
				img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast16() when the height is set to half of the screen's
 * height.
 * @details The expected results are that a 16px image will be plotted in the
 * top-left corner of the screen that vertically takes up half the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t24Rast16(ArgList *args)
{
	const int LEN    = 16;
	const int HEIGHT = SCRN_HEIGHT / 2;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT16 img[SCRN_HEIGHT];

	memset(img, 0xFF, SCRN_HEIGHT * (LEN >> DIV_SHIFT_BY_8));

	plot_rast16((UINT16 *)getArgFromList("base", args), 0, SCRN_MAX_Y, HEIGHT,
				img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast16() when the height given is just below the maximum
 * height of the screen.
 * @details The expected results are that a 16px image will be plotted in the
 * top-left corner that extends vertically almost the entire screen except for
 * the bottom row.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t25Rast16(ArgList *args)
{
	const int LEN    = 16;
	const int HEIGHT = SCRN_HEIGHT - 1;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT16 img[SCRN_HEIGHT];

	memset(img, 0xFF, SCRN_HEIGHT * (LEN >> DIV_SHIFT_BY_8));

	plot_rast16((UINT16 *)getArgFromList("base", args), 0, SCRN_MAX_Y, HEIGHT,
				img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast16() when the height given is equal to the maximum
 * height of the screen.
 * @details The expected results are that a 16px image will be plotted in the
 * top-left corner that extends vertically across the entire screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t26Rast16(ArgList *args)
{
	const int LEN    = 16;
	const int HEIGHT = SCRN_HEIGHT;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT16 img[SCRN_HEIGHT];

	memset(img, 0xFF, SCRN_HEIGHT * (LEN >> DIV_SHIFT_BY_8));

	plot_rast16((UINT16 *)getArgFromList("base", args), 0, SCRN_MAX_Y, HEIGHT,
				img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast16() when the height given is greater than the maximum
 * height of the screen.
 * @details The expected results are that a 16px image will be plotted in the
 * top-left corner that extends vertically across the entire screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t27Rast16(ArgList *args)
{
	const int LEN    = 16;
	const int HEIGHT = SCRN_HEIGHT + 1;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT16 img[SCRN_HEIGHT];

	memset(img, 0xFF, SCRN_HEIGHT * (LEN >> DIV_SHIFT_BY_8));

	plot_rast16((UINT16 *)getArgFromList("base", args), 0, SCRN_MAX_Y, HEIGHT,
				img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast16() when the height is zero.
 * @details The expected results are that nothing will be plotted.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t28Rast16(ArgList *args)
{
	const int LEN    = 16;
	const int HEIGHT = 0;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT16 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast16((UINT16 *)getArgFromList("base", args), 0, 0, HEIGHT, img,
				destructive, blackScreen);
}

/**
 * @brief Tests plot_rast16() when the height is negative.
 * @details The expected results are that nothing will be plotted.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t29Rast16(ArgList *args)
{
	const int LEN    = 16;
	const int HEIGHT = -1;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT16 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast16((UINT16 *)getArgFromList("base", args), 0, 0, HEIGHT, img,
				destructive, blackScreen);
}

/**
 * @brief Tests plot_rast16() when x is 16px off the screen to the left.
 * @details The expected results are that nothing will be plotted.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t30Rast16(ArgList *args)
{
	const int LEN    = 16;
	const int HEIGHT = 16;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT16 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast16((UINT16 *)getArgFromList("base", args), -LEN, 0, HEIGHT, img,
				destructive, blackScreen);
}

/**
 * @brief Tests plot_rast16() when x is equal to the screen length.
 * @details The expected results are that nothing will be plotted.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t31Rast16(ArgList *args)
{
	const int LEN    = 16;
	const int HEIGHT = 16;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT16 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast16((UINT16 *)getArgFromList("base", args), SCRN_LEN, 0, HEIGHT,
				img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast16() when x is greater than the screen length.
 * @details The expected results are that nothing will be plotted.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t32Rast16(ArgList *args)
{
	const int LEN    = 16;
	const int HEIGHT = 16;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT16 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast16((UINT16 *)getArgFromList("base", args), SCRN_LEN + 1, 0, HEIGHT,
				img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast16() when y is 16px upwards off the screen.
 * @details The expected results are that nothing will be plotted.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t33Rast16(ArgList *args)
{
	const int LEN    = 16;
	const int HEIGHT = 16;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT16 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast16((UINT16 *)getArgFromList("base", args), 0, -HEIGHT, HEIGHT,
				img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast16() when y is equal to the screen height.
 * @details The expected results are that nothing will be plotted.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t34Rast16(ArgList *args)
{
	const int LEN    = 16;
	const int HEIGHT = 16;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT16 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast16((UINT16 *)getArgFromList("base", args), 0, SCRN_HEIGHT, HEIGHT,
				img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast16() when y is greater than the screen height.
 * @details The expected results are that nothing will be plotted.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 * - blackScreen: Whether an image is being placed on top of a black background
 * or not.
 * - destructive: Whether the image should destroy whatever was at the position
 * it is being plotted at.
 */
void t35Rast16(ArgList *args)
{
	const int LEN    = 16;
	const int HEIGHT = 16;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT16 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast16((UINT16 *)getArgFromList("base", args), 0, SCRN_HEIGHT + 1,
				HEIGHT, img, destructive, blackScreen);
}

/**
 * @brief A function that tests plot_rast8().
 * @details The screen will be cleared before every test. Enter has to be
 * pressed after every test.
 * 
 * @param base The location in memory of start of frame buffer.
 * @param destruct Is TRUE when plot_rast32()'s destructive capabilities
 * will be tested.
 * @param blackScreen Is TRUE when plot_rast32()'s ability to print
 * colour-inverted images on a black screen will be tested.
 */
void tst_plot_rast8(UINT8 *base, BOOL destruct, BOOL blackScreen)
{
	const UINT32 *base_32 = (UINT32 *)base;

	const int height = 8; /*Height of raster that is being used, doesn't apply to 
	                   height boundary testing*/

	UINT8 tstBmp[8];
	UINT8 fullScrnBmp[SCRN_HEIGHT];

	memset(fullScrnBmp, 0xFF, SCRN_HEIGHT * UINT8_BYTES);

	getBlockyBitmap(8, tstBmp);

	/*TEST 1: When both x and y are at their minimum visible position 
	on screen.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, 0, 0, height, tstBmp, destruct, blackScreen);
	Cconin();

	/*TEST 2: When x is set to a value corresponding to the middle of 
	the screen.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, SCRN_MID_X, 0, height, tstBmp, destruct, blackScreen);
	Cconin();

	/*TEST 3: When x is set to the maximum value it can be without getting 
	the image cropped.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, RAST8_MAX_VIS_X, 0, height, tstBmp, destruct,
		blackScreen);
	Cconin();

	/*TEST 4: When y is set to a value corresponding to the middle of 
	the screen.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, 0, SCRN_MID_Y, height, tstBmp, destruct, blackScreen);
	Cconin();

	/*TEST 5: When x and y are set to a value corresponding to the middle 
	of the screen.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, SCRN_MID_X, SCRN_MID_Y, height, tstBmp, destruct,
		blackScreen);
	Cconin();

	/*TEST 6: When y is set to the maximum value it can be without getting 
	the image cropped.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, 0, RAST8H_MAX_VIS_Y, height, tstBmp, destruct,
		blackScreen);
	Cconin();

	/*TEST 7: When x and y are set to their maximum values they can have 
	without getting the image cropped.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, RAST8_MAX_VIS_X, RAST8H_MAX_VIS_Y, height, tstBmp,
		destruct, blackScreen);
	Cconin();

	/*TEST 8: When x is set to a value such that the center of the image 
	is contained in the horizontal center of the screen.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, RAST8_MID_VIS_X, 0, height, tstBmp, destruct,
		blackScreen);
	Cconin();

	/*TEST 9: When y is set to a value such that the center of the image 
	is contained in the vertical center of the screen.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, 0, RAST8H_MID_VIS_Y, height, tstBmp, destruct,
		blackScreen);
	Cconin();

	/*TEST 10: When x and y are set to values such that the center of the 
	image is in the center of the screen.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, RAST8_MID_VIS_X, RAST8H_MID_VIS_Y, height,
		tstBmp, destruct, blackScreen);
	Cconin();

	/*TEST 11: When x is set to a value such that the image is cropped by 
	1px from the left.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, -1, 0, height, tstBmp, destruct, blackScreen);
	Cconin();

	/*TEST 12: When x is set to a value such that half of the image is 
	cropped from the left.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, RAST8_LHALF_X, 0, height, tstBmp, destruct, blackScreen);
	Cconin();

	/*TEST 13: When x is set to a value such that only the rightmost column 
	constituting the image is on screen.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, RAST8_MIN_X, 0, height, tstBmp, destruct, blackScreen);
	Cconin();

	/*TEST 14: When y is set to a value such that the image is cropped by 
	1px from the top.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, 0, -1, height, tstBmp, destruct, blackScreen);
	Cconin();

	/*TEST 15: When y is set to a value such that the top half of the image 
	is cropped off.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, 0, RAST8H_THALF_Y, height, tstBmp, destruct, blackScreen);
	Cconin();

	/*TEST 16: When y is set to a value such that only the bottommost row 
	constituting the image is on screen.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, 0, RAST8H_MIN_Y, height, tstBmp, destruct, blackScreen);
	Cconin();

	/*TEST 17: When x is set to a value such that the image is cropped by 
	1px from the right.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, RAST8_MAX_VIS_X + 1, 0, height, tstBmp, destruct,
		blackScreen);
	Cconin();

	/*TEST 18: When x is set to a value such that half of the image is 
	cropped from the right.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, RAST8_MID_VIS_X, 0, height, tstBmp, destruct, 
			blackScreen);
	Cconin();

	/*TEST 19: When x is set to a value such that only the leftmost column 
	constituting the image is on screen.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, SCRN_MAX_X, 0, height, tstBmp, destruct, blackScreen);
	Cconin();

	/*TEST 20: When y is set to a value such that the image is cropped by 
	1px from the bottom.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, 0, RAST8H_MAX_VIS_Y, height, tstBmp, destruct,
		blackScreen);
	Cconin();

	/*TEST 21: When y is set to a value such that the bottom half of the 
	image is cropped off.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, 0, RAST8H_BHALF_Y, height, tstBmp, 
			destruct, blackScreen);
	Cconin();

	/*TEST 22: When y is set to a value such that only the topmost row 
	constituting the image is on screen.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, 0, SCRN_MAX_Y, height, tstBmp, destruct, blackScreen);
	Cconin();

	/*TEST 23: When the height is set to its minimum possible value.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, 0, 0, 1, fullScrnBmp, destruct, blackScreen);
	Cconin();

	/*TEST 24: When the height is set to half of the screen's height.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, 0, 0, SCRN_HEIGHT / 2, fullScrnBmp, destruct,
		blackScreen);
	Cconin();

	/*TEST 25: When the height given is just below the maximum height 
	of the screen.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, 0, 0, SCRN_HEIGHT - 1, fullScrnBmp, destruct,
		blackScreen);
	Cconin();

	/*TEST 26: When the height given is the maximum height of the screen.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, 0, 0, SCRN_HEIGHT, fullScrnBmp, destruct, blackScreen);
	Cconin();

	/*TEST 27: When the height given is greater than the maximum height 
	of the screen.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, 0, 0, SCRN_HEIGHT + 1, fullScrnBmp, destruct,
		blackScreen);
	Cconin();

	/*TEST 28: When the height given is zero.*/
	blackScreen ?
		fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, 0, 0, 0, tstBmp, destruct, blackScreen);
	Cconin();

	/*TEST 29: When the height given is negative.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, 0, 0, -1, tstBmp, destruct, blackScreen);
	Cconin();

	/*TEST 30: When x is 8px off the screen to the left.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, -8, 0, height, tstBmp, destruct, blackScreen);
	Cconin();

	/*TEST 31: When x is equal to the screen length.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, SCRN_LEN, 0, height, tstBmp, destruct, blackScreen);
	Cconin();

	/*TEST 32: When x is greater than the screen length.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, SCRN_LEN + 1, 0, height, tstBmp, destruct,
		blackScreen);
	Cconin();

	/*TEST 33: When y is 8px upwards off the screen.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, 0, -8, height, tstBmp, destruct, blackScreen);
	Cconin();

	/*TEST 34: When y is equal to the screen height.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, 0, SCRN_HEIGHT, height, tstBmp, destruct, blackScreen);
	Cconin();

	/*TEST 35: When y is greater than the screen height.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, 0, SCRN_HEIGHT + 1, height, tstBmp, destruct,
		blackScreen);
	Cconin();
}

/**
 * @brief Handle the registration of all tests related to the rect_area()
 * function.
 */
void regRectAreaTests()
{
	TestSuiteID suiteID;

	suiteID = registerTestSuite("Tests drawing filled-in rectangles.",
								rastGDTstWhite);

	registerTestCase(suiteID, "When both x and y are at their minimum value (zero).", NULL, t1RectArea);

	registerTestCase(suiteID, "When x is at its middle value", NULL,
					 t2RectArea);

	registerTestCase(suiteID, "When x is at its maximum value such that the resultant rectangle is completely visible on screen.", NULL, t3RectArea);

	registerTestCase(suiteID, "When y is at its middle value.", NULL,
					 t4RectArea);

	registerTestCase(suiteID, "When y is at its maximum value such that the rectangle is still completely visible on screen.", NULL, t5RectArea);

	registerTestCase(suiteID, "When x is at a value such that the center of the rectangle is at the horizontal center of the screen.", NULL, t6RectArea);

	registerTestCase(suiteID, "When y is at a value such that the center of the rectangle is at the vertical center of the screen.", NULL, t7RectArea);

	registerTestCase(suiteID, "When x and y are set to the value such that the middle of the plotted rectangle is in the center of the screen.", NULL, t8RectArea);

	registerTestCase(suiteID, "When x and y are set to their maximum values.",
					 NULL, t9RectArea);

	registerTestCase(suiteID, "When the length and height are set to their minimum values (1).", NULL, t10RectArea);

	registerTestCase(suiteID, "When the length and height are set to the size of the screen.", NULL, t11RectArea);

	registerTestCase(suiteID, "When the length and height are greater than the size of the screen.", NULL, t12RectArea);

	registerTestCase(suiteID, "When the value of the length is different from the height.", NULL, t13RectArea);
}

/**
 * @brief Tests rect_area() when both x and y are at their minimum value (zero).
 * @details The expected results are that a 32 by 32 pixel square will be
 * plotted at the top-left corner of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t1RectArea(ArgList *args)
{
	const int RECT_LEN    = 32;
	const int RECT_HEIGHT = 32;

	rect_area((UINT32 *)getArgFromList("base", args), 0, RECT_LEN, 0,
			  RECT_HEIGHT);
}

/**
 * @brief Tests rect_area() when x is at its middle value.
 * @details The expected results are that a 32 by 32 pixel square will be
 * plotted starting at the top-middle portion of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t2RectArea(ArgList *args)
{
	const int RECT_LEN    = 32;
	const int RECT_HEIGHT = 32;

	rect_area((UINT32 *)getArgFromList("base", args), SCRN_MID_X, RECT_LEN, 0,
			  RECT_HEIGHT);
}

/**
 * @brief Tests rect_area() when x is at its maximum value such that the
 * resultant rectangle is completely visible on screen.
 * @details The expected results are that a 32 by 32 pixel square will be
 * plotted at the top-right corner of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t3RectArea(ArgList *args)
{
	const int RECT_LEN    = 32;
	const int RECT_HEIGHT = 32;

	rect_area((UINT32 *)getArgFromList("base", args), RAST32_MAX_VIS_X,
			  RECT_LEN, 0, RECT_HEIGHT);
}

/**
 * @brief Tests rect_area() when y is at its middle value.
 * @details The expected results are that a 32 by 32 pixel square will be
 * plotted starting at the left-middle portion of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t4RectArea(ArgList *args)
{
	const int RECT_LEN    = 32;
	const int RECT_HEIGHT = 32;

	rect_area((UINT32 *)getArgFromList("base", args), 0, RECT_LEN, SCRN_MID_Y,
			  RECT_HEIGHT);
}

/**
 * @brief Tests rect_area() when y is at its maximum value such that the
 * rectangle is still completely visible on screen.
 * @details The expected results are that a 32 by 32 pixel square will be
 * plotted at the bottom-left corner of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t5RectArea(ArgList *args)
{
	const int RECT_LEN    = 32;
	const int RECT_HEIGHT = 32;

	rect_area((UINT32 *)getArgFromList("base", args), 0, RECT_LEN,
			  RAST32H_MAX_VIS_Y, RECT_HEIGHT);
}

/**
 * @brief Tests rect_area() when x is at a value such that the center of the
 * rectangle is at the horizontal center of the screen.
 * @details The expected results are that a 32 by 32 pixel square will be
 * plotted at the top of the screen and horizontally-centered.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t6RectArea(ArgList *args)
{
	const int RECT_LEN    = 32;
	const int RECT_HEIGHT = 32;

	rect_area((UINT32 *)getArgFromList("base", args), RAST32_MID_VIS_X,
			  RECT_LEN, 0, RECT_HEIGHT);
}

/**
 * @brief Tests rect_area() when y is at a value such that the center of the
 * rectangle is at the vertical center of the screen.
 * @details The expected results are that a 32 by 32 pixel square will be
 * plotted at the left of the screen and vertically-centered.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t7RectArea(ArgList *args)
{
	const int RECT_LEN    = 32;
	const int RECT_HEIGHT = 32;

	rect_area((UINT32 *)getArgFromList("base", args), 0, RECT_LEN,
			  RAST32H_MID_VIS_Y, RECT_HEIGHT);
}

/**
 * @brief Tests rect_area() when x and y are set to the value such that the
 * middle of the plotted rectangle is in the center of the screen.
 * @details The expected results are that a 32 by 32 pixel square will be
 * plotted in the center of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t8RectArea(ArgList *args)
{
	const int RECT_LEN    = 32;
	const int RECT_HEIGHT = 32;

	rect_area((UINT32 *)getArgFromList("base", args), RAST32_MID_VIS_X,
			  RECT_LEN, RAST32H_MID_VIS_Y, RECT_HEIGHT);
}

/**
 * @brief Tests rect_area() when x and y are set to their maximum values.
 * @details The expected results are that a dot will be plotted in the
 * bottom-right corner of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t9RectArea(ArgList *args)
{
	const int RECT_LEN    = 32;
	const int RECT_HEIGHT = 32;

	rect_area((UINT32 *)getArgFromList("base", args), SCRN_MAX_X, RECT_LEN,
			  SCRN_MAX_Y, RECT_HEIGHT);
}

/**
 * @brief Tests rect_area() when the length and height are set to their minimum
 * values (1).
 * @details The expected results are that a dot will be plotted in the
 * top-left corner of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t10RectArea(ArgList *args)
{
	const int RECT_LEN    = 1;
	const int RECT_HEIGHT = 1;

	rect_area((UINT32 *)getArgFromList("base", args), 0, RECT_LEN, 0,
			  RECT_HEIGHT);
}

/**
 * @brief Tests rect_area() when the length and height are set to the size of
 * the screen.
 * @details The expected results are that the entire screen will be filled
 * black.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t11RectArea(ArgList *args)
{
	const int RECT_LEN    = SCRN_LEN;
	const int RECT_HEIGHT = SCRN_HEIGHT;

	rect_area((UINT32 *)getArgFromList("base", args), 0, RECT_LEN, 0,
			  RECT_HEIGHT);
}

/**
 * @brief Tests rect_area() when the length and height are greater than the size
 * of the screen.
 * @details The expected results are that the entire screen will be filled
 * black.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t12RectArea(ArgList *args)
{
	const int RECT_LEN    = SCRN_LEN    + 1;
	const int RECT_HEIGHT = SCRN_HEIGHT + 1;

	rect_area((UINT32 *)getArgFromList("base", args), 0, RECT_LEN, 0,
			  RECT_HEIGHT);
}

/**
 * @brief Tests rect_area() when the value of the length is different from the
 * height.
 * @details The expected results are that a 16 by 32 px rectangle will be
 * plotted starting at the top-left corner.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t13RectArea(ArgList *args)
{
	const int RECT_LEN    = 16;
	const int RECT_HEIGHT = 32;

	rect_area((UINT32 *)getArgFromList("base", args), 0, RECT_LEN, 0,
			  RECT_HEIGHT);
}

/**
 * @brief Handle the registration of all tests related to the clr_area()
 * function.
 */
void regClrAreaTests()
{
	TestSuiteID suiteID;

	suiteID = registerTestSuite("Tests clearing rectangular areas on screen.",
								rastGDTstBlack);

	registerTestCase(suiteID, "When both x and y are at their minimum value (zero).", NULL, t1ClrArea);

	registerTestCase(suiteID, "When x is at its middle value", NULL,
					 t2ClrArea);

	registerTestCase(suiteID, "When x is at its maximum value such that the resultant rectangle is completely visible on screen.", NULL, t3ClrArea);

	registerTestCase(suiteID, "When y is at its middle value.", NULL,
					 t4ClrArea);

	registerTestCase(suiteID, "When y is at its maximum value such that the rectangle is still completely visible on screen.", NULL, t5ClrArea);

	registerTestCase(suiteID, "When x is at a value such that the center of the rectangle is at the horizontal center of the screen.", NULL, t6ClrArea);

	registerTestCase(suiteID, "When y is at a value such that the center of the rectangle is at the vertical center of the screen.", NULL, t7ClrArea);

	registerTestCase(suiteID, "When x and y are set to the value such that the middle of the plotted rectangle is in the center of the screen.", NULL, t8ClrArea);

	registerTestCase(suiteID, "When x and y are set to their maximum values.",
					 NULL, t9ClrArea);

	registerTestCase(suiteID, "When the length and height are set to their minimum values (1).", NULL, t10ClrArea);

	registerTestCase(suiteID, "When the length and height are set to the size of the screen.", NULL, t11ClrArea);

	registerTestCase(suiteID, "When the length and height are greater than the size of the screen.", NULL, t12ClrArea);

	registerTestCase(suiteID, "When the value of the length is different from the height.", NULL, t13ClrArea);
}

/**
 * @brief Tests clr_area() when both x and y are at their minimum value (zero).
 * @details The expected results are that a 32 by 32 pixel square will be
 * plotted at the top-left corner of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t1ClrArea(ArgList *args)
{
	const int RECT_LEN    = 32;
	const int RECT_HEIGHT = 32;

	clr_area((UINT32 *)getArgFromList("base", args), 0, RECT_LEN, 0,
			 RECT_HEIGHT);
}

/**
 * @brief Tests clr_area() when x is at its middle value.
 * @details The expected results are that a 32 by 32 pixel square will be
 * plotted starting at the top-middle portion of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t2ClrArea(ArgList *args)
{
	const int RECT_LEN    = 32;
	const int RECT_HEIGHT = 32;

	clr_area((UINT32 *)getArgFromList("base", args), SCRN_MID_X, RECT_LEN, 0,
			 RECT_HEIGHT);
}

/**
 * @brief Tests clr_area() when x is at its maximum value such that the
 * resultant rectangle is completely visible on screen.
 * @details The expected results are that a 32 by 32 pixel square will be
 * plotted at the top-right corner of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t3ClrArea(ArgList *args)
{
	const int RECT_LEN    = 32;
	const int RECT_HEIGHT = 32;

	clr_area((UINT32 *)getArgFromList("base", args), RAST32_MAX_VIS_X,
			 RECT_LEN, 0, RECT_HEIGHT);
}

/**
 * @brief Tests clr_area() when y is at its middle value.
 * @details The expected results are that a 32 by 32 pixel square will be
 * plotted starting at the left-middle portion of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t4ClrArea(ArgList *args)
{
	const int RECT_LEN    = 32;
	const int RECT_HEIGHT = 32;

	clr_area((UINT32 *)getArgFromList("base", args), 0, RECT_LEN, SCRN_MID_Y,
			 RECT_HEIGHT);
}

/**
 * @brief Tests clr_area() when y is at its maximum value such that the
 * rectangle is still completely visible on screen.
 * @details The expected results are that a 32 by 32 pixel square will be
 * plotted at the bottom-left corner of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t5ClrArea(ArgList *args)
{
	const int RECT_LEN    = 32;
	const int RECT_HEIGHT = 32;

	clr_area((UINT32 *)getArgFromList("base", args), 0, RECT_LEN,
			 RAST32H_MAX_VIS_Y, RECT_HEIGHT);
}

/**
 * @brief Tests clr_area() when x is at a value such that the center of the
 * rectangle is at the horizontal center of the screen.
 * @details The expected results are that a 32 by 32 pixel square will be
 * plotted at the top of the screen and horizontally-centered.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t6ClrArea(ArgList *args)
{
	const int RECT_LEN    = 32;
	const int RECT_HEIGHT = 32;

	clr_area((UINT32 *)getArgFromList("base", args), RAST32_MID_VIS_X,
			 RECT_LEN, 0, RECT_HEIGHT);
}

/**
 * @brief Tests clr_area() when y is at a value such that the center of the
 * rectangle is at the vertical center of the screen.
 * @details The expected results are that a 32 by 32 pixel square will be
 * plotted at the left of the screen and vertically-centered.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t7ClrArea(ArgList *args)
{
	const int RECT_LEN    = 32;
	const int RECT_HEIGHT = 32;

	clr_area((UINT32 *)getArgFromList("base", args), 0, RECT_LEN,
			 RAST32H_MID_VIS_Y, RECT_HEIGHT);
}

/**
 * @brief Tests clr_area() when x and y are set to the value such that the
 * middle of the plotted rectangle is in the center of the screen.
 * @details The expected results are that a 32 by 32 pixel square will be
 * plotted in the center of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t8ClrArea(ArgList *args)
{
	const int RECT_LEN    = 32;
	const int RECT_HEIGHT = 32;

	clr_area((UINT32 *)getArgFromList("base", args), RAST32_MID_VIS_X,
			 RECT_LEN, RAST32H_MID_VIS_Y, RECT_HEIGHT);
}

/**
 * @brief Tests clr_area() when x and y are set to their maximum values.
 * @details The expected results are that a dot will be plotted in the
 * bottom-right corner of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t9ClrArea(ArgList *args)
{
	const int RECT_LEN    = 32;
	const int RECT_HEIGHT = 32;

	clr_area((UINT32 *)getArgFromList("base", args), SCRN_MAX_X, RECT_LEN,
			 SCRN_MAX_Y, RECT_HEIGHT);
}

/**
 * @brief Tests clr_area() when the length and height are set to their minimum
 * values (1).
 * @details The expected results are that a dot will be plotted in the
 * top-left corner of the screen.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t10ClrArea(ArgList *args)
{
	const int RECT_LEN    = 1;
	const int RECT_HEIGHT = 1;

	clr_area((UINT32 *)getArgFromList("base", args), 0, RECT_LEN, 0,
			 RECT_HEIGHT);
}

/**
 * @brief Tests clr_area() when the length and height are set to the size of
 * the screen.
 * @details The expected results are that the entire screen will be filled
 * black.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t11ClrArea(ArgList *args)
{
	const int RECT_LEN    = SCRN_LEN;
	const int RECT_HEIGHT = SCRN_HEIGHT;

	clr_area((UINT32 *)getArgFromList("base", args), 0, RECT_LEN, 0,
			 RECT_HEIGHT);
}

/**
 * @brief Tests clr_area() when the length and height are greater than the size
 * of the screen.
 * @details The expected results are that the entire screen will be filled
 * black.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t12ClrArea(ArgList *args)
{
	const int RECT_LEN    = SCRN_LEN    + 1;
	const int RECT_HEIGHT = SCRN_HEIGHT + 1;

	clr_area((UINT32 *)getArgFromList("base", args), 0, RECT_LEN, 0,
			 RECT_HEIGHT);
}

/**
 * @brief Tests clr_area() when the value of the length is different from the
 * height.
 * @details The expected results are that a 16 by 32 px rectangle will be
 * plotted starting at the top-left corner.
 * @note This has not been tested on both TOS and SDL2.
 * 
 * @param args The list of arguments required by the function.
 * 
 * - base: The location in memory to plot at.
 */
void t13ClrArea(ArgList *args)
{
	const int RECT_LEN    = 16;
	const int RECT_HEIGHT = 32;

	clr_area((UINT32 *)getArgFromList("base", args), 0, RECT_LEN, 0,
			  RECT_HEIGHT);
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