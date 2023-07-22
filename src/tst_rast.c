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

#include "arg_list.h"
#include "ikbdcode.h"
#include "input.h"
#include "raster.h"
#include "scrn.h"
#include "super.h"
#include "test.h"
#include "tst_bmp.h"

#define CLEAR_ON  TRUE
#define CLEAR_OFF FALSE

#define DESTRUCT_ON  TRUE
#define DESTRUCT_OFF FALSE

#define BLACK_SCREEN_ON  TRUE
#define BLACK_SCREEN_OFF FALSE

void rastTstWhite(void (*tstFunc)(ArgList *args));
void rastTstBlack(void (*tstFunc)(ArgList *args));
void rastTstCommon(void (*tstFunc)(ArgList *args), BOOL blackScreen);

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

void tst_plot_rast32(UINT32 *base, BOOL destruct, BOOL blackScreen);
void tst_plot_rast16(UINT16 *base, BOOL destruct, BOOL blackScreen);
void tst_plot_rast8(UINT8 *base, BOOL destruct, BOOL blackScreen);
void tst_rect_area(UINT32 *base);
void tst_clr_area(UINT32 *base);

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
	regHlineTests();

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
	rastTstCommon(tstFunc, BLACK_SCREEN_OFF);
}

/**
 * @brief Sets up a blank black screen for testing the raster functions.
 * 
 * @param tstFunc The function to test the raster functions.
 */
void rastTstBlack(void (*tstFunc)(ArgList *args))
{
	rastTstCommon(tstFunc, BLACK_SCREEN_ON);
}

/**
 * @brief Contains the common functionality shared by all the raster test
 * manager functions.
 * 
 * @param tstFunc The function to test the raster functions.
 * @param blackScreen Whether there should be a white or black screen.
 */
void rastTstCommon(void (*tstFunc)(ArgList *args), BOOL blackScreen)
{
	ArgList args;
	Vector origKybd = initKybd();
	IKBD_Scancode scancode;

	initArgList(&args);
	appendArgToList("base", get_video_base(), &args);

	if (blackScreen)
	{
		fill_scrn((UINT32 *)getArgFromList("base", &args));
	}
	else
	{
		clr_scrn((UINT32 *)getArgFromList("base", &args));
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

	registerTestCase(suiteID, "When y is equal to the screen height.", NULL, t22Hline);

	registerTestCase(suiteID, "When y is greater than the screen height.", NULL, t23Hline);

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
 * @brief A function that tests plot_rast32().
 * @details The screen will be cleared before every test. Enter has to be
 * pressed after every test.
 * 
 * @param base The location in memory of start of frame buffer.
 * @param destruct Is TRUE when plot_rast32()'s destructive capabilities
 * will be tested.
 * @param blackScreen Is TRUE when plot_rast32()'s ability to print
 * colour-inverted images on a black screen will be tested.
 */
void tst_plot_rast32(UINT32 *base, BOOL destruct, BOOL blackScreen)
{
	const int height = 32; /*Height of raster that is being used, doesn't apply to 
	                   height boundary testing*/

	/*TEST 1: When both x and y are at their minimum visible position 
	on screen.*/
	blackScreen ? fill_scrn(base) : clr_scrn(base);
	plot_rast32(base, 0, 0, height, BMP_32_TST, destruct, blackScreen);
	Cconin();

	/*TEST 2: When x is set to a value corresponding to the middle of 
	the screen.*/
	blackScreen ? fill_scrn(base) : clr_scrn(base);
	plot_rast32(base, SCRN_MID_X, 0, height, BMP_32_TST, destruct, blackScreen);
	Cconin();

	/*TEST 3: When x is set to the maximum value it can be without getting 
	the image cropped.*/
	blackScreen ? fill_scrn(base) : clr_scrn(base);
	plot_rast32(base, RAST32_MAX_VIS_X, 0, height, BMP_32_TST, destruct,
		blackScreen);
	Cconin();

	/*TEST 4: When y is set to a value corresponding to the middle of 
	the screen.*/
	blackScreen ? fill_scrn(base) : clr_scrn(base);
	plot_rast32(base, 0, SCRN_MID_Y, height, BMP_32_TST, destruct, blackScreen);
	Cconin();

	/*TEST 5: When x and y are set to a value corresponding to the middle 
	of the screen.*/
	blackScreen ? fill_scrn(base) : clr_scrn(base);
	plot_rast32(base, SCRN_MID_X, SCRN_MID_Y, height, BMP_32_TST, destruct,
		blackScreen);
	Cconin();

	/*TEST 6: When y is set to the maximum value it can be without getting 
	the image cropped.*/
	blackScreen ? fill_scrn(base) : clr_scrn(base);
	plot_rast32(base, 0, (SCRN_HEIGHT - 32), height, BMP_32_TST, destruct,
		blackScreen);
	Cconin();

	/*TEST 7: When x and y are set to their maximum values they can have 
	without getting the image cropped.*/
	blackScreen ? fill_scrn(base) : clr_scrn(base);
	plot_rast32(base, RAST32_MAX_VIS_X, (SCRN_HEIGHT - 32), height, BMP_32_TST,
		destruct, blackScreen);
	Cconin();

	/*TEST 8: When x is set to a value such that the center of the image 
	is contained in the horizontal center of the screen.*/
	blackScreen ? fill_scrn(base) : clr_scrn(base);
	plot_rast32(base, RAST32_MID_VIS_X, 0, height, BMP_32_TST, destruct,
		blackScreen);
	Cconin();

	/*TEST 9: When y is set to a value such that the center of the image 
	is contained in the vertical center of the screen.*/
	blackScreen ? fill_scrn(base) : clr_scrn(base);
	plot_rast32(base, 0, ((SCRN_HEIGHT / 2) - 16), height, BMP_32_TST, destruct,
		blackScreen);
	Cconin();

	/*TEST 10: When x and y are set to values such that the center of the 
	image is in the center of the screen.*/
	blackScreen ? fill_scrn(base) : clr_scrn(base);
	plot_rast32(base, SCRN_MID_X, ((SCRN_HEIGHT / 2) - 16), height, BMP_32_TST,
		destruct, blackScreen);
	Cconin();

	/*TEST 11: When x is set to a value such that the image is cropped by 
	1px from the left.*/
	blackScreen ? fill_scrn(base) : clr_scrn(base);
	plot_rast32(base, -1, 0, height, BMP_32_TST, destruct, blackScreen);
	Cconin();

	/*TEST 12: When x is set to a value such that half of the image is 
	cropped from the left.*/
	blackScreen ? fill_scrn(base) : clr_scrn(base);
	plot_rast32(base, -16, 0, height, BMP_32_TST, destruct, blackScreen);
	Cconin();

	/*TEST 13: When x is set to a value such that only the rightmost column 
	constituting the image is on screen.*/
	blackScreen ? fill_scrn(base) : clr_scrn(base);
	plot_rast32(base, RAST32_MIN_X, 0, height, BMP_32_TST, destruct,
		blackScreen);
	Cconin();

	/*TEST 14: When y is set to a value such that the image is cropped by 
	1px from the top.*/
	blackScreen ? fill_scrn(base) : clr_scrn(base);
	plot_rast32(base, 0, -1, height, BMP_32_TST, destruct, blackScreen);
	Cconin();

	/*TEST 15: When y is set to a value such that the top half of the image 
	is cropped off.*/
	blackScreen ? fill_scrn(base) : clr_scrn(base);
	plot_rast32(base, 0, -16, height, BMP_32_TST, destruct, blackScreen);
	Cconin();

	/*TEST 16: When y is set to a value such that only the bottommost row 
	constituting the image is on screen.*/
	blackScreen ? fill_scrn(base) : clr_scrn(base);
	plot_rast32(base, 0, -31, height, BMP_32_TST, destruct, blackScreen);
	Cconin();

	/*TEST 17: When x is set to a value such that the image is cropped by 
	1px from the right.*/
	blackScreen ? fill_scrn(base) : clr_scrn(base);
	plot_rast32(base, RAST32_MAX_VIS_X + 1, 0, height, BMP_32_TST, destruct,
		blackScreen);
	Cconin();

	/*TEST 18: When x is set to a value such that half of the image is 
	cropped from the right.*/
	blackScreen ? fill_scrn(base) : clr_scrn(base);
	plot_rast32(base, (SCRN_LEN - 16), 0, height, BMP_32_TST, destruct,
		blackScreen);
	Cconin();

	/*TEST 19: When x is set to a value such that only the leftmost column 
	constituting the image is on screen.*/
	blackScreen ? fill_scrn(base) : clr_scrn(base);
	plot_rast32(base, SCRN_MAX_X, 0, height, BMP_32_TST, destruct, blackScreen);
	Cconin();

	/*TEST 20: When y is set to a value such that the image is cropped by 
	1px from the bottom.*/
	blackScreen ? fill_scrn(base) : clr_scrn(base);
	plot_rast32(base, 0, (SCRN_HEIGHT - 31), height, BMP_32_TST, destruct,
		blackScreen);
	Cconin();

	/*TEST 21: When y is set to a value such that the bottom half of the 
	image is cropped off.*/
	blackScreen ? fill_scrn(base) : clr_scrn(base);
	plot_rast32(base, 0, (SCRN_HEIGHT - 16), height, BMP_32_TST, destruct,
		blackScreen);
	Cconin();

	/*TEST 22: When y is set to a value such that only the topmost row 
	constituting the image is on screen.*/
	blackScreen ? fill_scrn(base) : clr_scrn(base);
	plot_rast32(base, 0, SCRN_MAX_Y, height, BMP_32_TST, destruct, blackScreen);
	Cconin();

	/*TEST 23: When the height is set to its minimum possible value.*/
	blackScreen ? fill_scrn(base) : clr_scrn(base);
	plot_rast32(base, 0, 0, 1, BMP_HIGH_TST, destruct, blackScreen);
	Cconin();

	/*TEST 24: When the height is set to half of the screen’s height.*/
	blackScreen ? fill_scrn(base) : clr_scrn(base);
	plot_rast32(base, 0, 0, (SCRN_HEIGHT / 2), BMP_HIGH_TST, destruct,
		blackScreen);
	Cconin();

	/*TEST 25: When the height given is just below the maximum height 
	of the screen.*/
	blackScreen ? fill_scrn(base) : clr_scrn(base);
	plot_rast32(base, 0, 0, (SCRN_HEIGHT - 1), BMP_HIGH_TST, destruct,
		blackScreen);
	Cconin();

	/*TEST 26: When the height given is the maximum height of the screen.*/
	blackScreen ? fill_scrn(base) : clr_scrn(base);
	plot_rast32(base, 0, 0, SCRN_HEIGHT, BMP_HIGH_TST, destruct, blackScreen);
	Cconin();

	/*TEST 27: When the height given is greater than the maximum height 
	of the screen.*/
	blackScreen ? fill_scrn(base) : clr_scrn(base);
	plot_rast32(base, 0, 0, (SCRN_HEIGHT + 1), BMP_HIGH_TST, destruct,
		blackScreen);
	Cconin();

	/*TEST 28: When the height given is zero.*/
	blackScreen ? fill_scrn(base) : clr_scrn(base);
	plot_rast32(base, 0, 0, 0, BMP_32_TST, destruct, blackScreen);
	Cconin();

	/*TEST 29: When the height given is negative.*/
	blackScreen ? fill_scrn(base) : clr_scrn(base);
	plot_rast32(base, 0, 0, -1, BMP_32_TST, destruct, blackScreen);
	Cconin();

	/*TEST 30: When x is 32px off the screen to the left.*/
	blackScreen ? fill_scrn(base) : clr_scrn(base);
	plot_rast32(base, -32, 0, height, BMP_32_TST, destruct, blackScreen);
	Cconin();

	/*TEST 31: When x is equal to the screen length.*/
	blackScreen ? fill_scrn(base) : clr_scrn(base);
	plot_rast32(base, SCRN_LEN, 0, height, BMP_32_TST, destruct, blackScreen);
	Cconin();

	/*TEST 32: When x is greater than the screen length.*/
	blackScreen ? fill_scrn(base) : clr_scrn(base);
	plot_rast32(base, (SCRN_LEN + 1), 0, height, BMP_32_TST, destruct,
		blackScreen);
	Cconin();

	/*TEST 33: When y is 32px upwards off the screen.*/
	blackScreen ? fill_scrn(base) : clr_scrn(base);
	plot_rast32(base, 0, -32, height, BMP_32_TST, destruct, blackScreen);
	Cconin();

	/*TEST 34: When y is equal to the screen height.*/
	blackScreen ? fill_scrn(base) : clr_scrn(base);
	plot_rast32(base, 0, SCRN_HEIGHT, height, BMP_32_TST, destruct,
		blackScreen);
	Cconin();

	/*TEST 35: When y is greater than the screen height.*/
	blackScreen ? fill_scrn(base) : clr_scrn(base);
	plot_rast32(base, 0, (SCRN_HEIGHT + 1), height, BMP_32_TST, destruct,
		blackScreen);
	Cconin();
}

/**
 * @brief A function that tests plot_rast16().
 * @details The screen will be cleared before every test. Enter has to be
 * pressed after every test.
 * 
 * @param base The location in memory of start of frame buffer.
 * @param destruct Is TRUE when plot_rast32()'s destructive capabilities
 * will be tested.
 * @param blackScreen Is TRUE when plot_rast32()'s ability to print
 * colour-inverted images on a black screen will be tested.
 */
void tst_plot_rast16(UINT16 *base, BOOL destruct, BOOL blackScreen)
{
	const int height = 16; /*Height of raster that is being used, doesn't apply
							 to height boundary testing.*/
	const UINT32 *base_32 = (UINT32 *)base;

	const UINT16 *BMP16_HIGH_TST = (UINT16 *)BMP_HIGH_TST;

	/*TEST 1: When both x and y are at their minimum visible position 
	on screen.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast16(base, 0, 0, height, BMP_16_TST, destruct, blackScreen);
	Cconin();

	/*TEST 2: When x is set to a value corresponding to the middle of 
	the screen.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast16(base, SCRN_MID_X, 0, height, BMP_16_TST, destruct, blackScreen);
	Cconin();

	/*TEST 3: When x is set to the maximum value it can be without getting 
	the image cropped.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast16(base, RAST16_MAX_VIS_X, 0, height, BMP_16_TST, destruct,
		blackScreen);
	Cconin();

	/*TEST 4: When y is set to a value corresponding to the middle of 
	the screen.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast16(base, 0, SCRN_MID_Y, height, BMP_16_TST, destruct, blackScreen);
	Cconin();

	/*TEST 5: When x and y are set to a value corresponding to the middle 
	of the screen.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast16(base, SCRN_MID_X, SCRN_MID_Y, height, BMP_16_TST, destruct,
		blackScreen);
	Cconin();

	/*TEST 6: When y is set to the maximum value it can be without getting 
	the image cropped.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast16(base, 0, (SCRN_HEIGHT - 16), height, BMP_16_TST, destruct,
		blackScreen);
	Cconin();

	/*TEST 7: When x and y are set to their maximum values they can have 
	without getting the image cropped.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast16(base, RAST16_MAX_VIS_X, (SCRN_HEIGHT - 16), height, BMP_16_TST,
		destruct, blackScreen);
	Cconin();

	/*TEST 8: When x is set to a value such that the center of the image 
	is contained in the horizontal center of the screen.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast16(base, RAST16_MID_VIS_X, 0, height, BMP_16_TST, destruct,
		blackScreen);
	Cconin();

	/*TEST 9: When y is set to a value such that the center of the image 
	is contained in the vertical center of the screen.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast16(base, 0, ((SCRN_HEIGHT / 2) - 8), height, BMP_16_TST, destruct,
		blackScreen);
	Cconin();

	/*TEST 10: When x and y are set to values such that the center of the 
	image is in the center of the screen.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast16(base, RAST16_MID_VIS_X, ((SCRN_HEIGHT / 2) - 8), height,
		BMP_16_TST, destruct, blackScreen);
	Cconin();

	/*TEST 11: When x is set to a value such that the image is cropped by 
	1px from the left.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast16(base, -1, 0, height, BMP_16_TST, destruct, blackScreen);
	Cconin();

	/*TEST 12: When x is set to a value such that half of the image is 
	cropped from the left.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast16(base, -8, 0, height, BMP_16_TST, destruct, blackScreen);
	Cconin();

	/*TEST 13: When x is set to a value such that only the rightmost column 
	constituting the image is on screen.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast16(base, RAST16_MIN_X, 0, height, BMP_16_TST, destruct,
		blackScreen);
	Cconin();

	/*TEST 14: When y is set to a value such that the image is cropped by 
	1px from the top.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast16(base, 0, -1, height, BMP_16_TST, destruct, blackScreen);
	Cconin();

	/*TEST 15: When y is set to a value such that the top half of the image 
	is cropped off.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast16(base, 0, -8, height, BMP_16_TST, destruct, blackScreen);
	Cconin();

	/*TEST 16: When y is set to a value such that only the bottommost row 
	constituting the image is on screen.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast16(base, 0, -15, height, BMP_16_TST, destruct, blackScreen);
	Cconin();

	/*TEST 17: When x is set to a value such that the image is cropped by 
	1px from the right.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast16(base, RAST16_MAX_VIS_X + 1, 0, height, BMP_16_TST, destruct,
		blackScreen);
	Cconin();

	/*TEST 18: When x is set to a value such that half of the image is 
	cropped from the right.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast16(base, (SCRN_LEN - 8), 0, height, BMP_16_TST, destruct,
		blackScreen);
	Cconin();

	/*TEST 19: When x is set to a value such that only the leftmost column 
	constituting the image is on screen.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast16(base, SCRN_MAX_X, 0, height, BMP_16_TST, destruct, blackScreen);
	Cconin();

	/*TEST 20: When y is set to a value such that the image is cropped by 
	1px from the bottom.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast16(base, 0, (SCRN_HEIGHT - 15), height, BMP_16_TST, destruct,
		blackScreen);
	Cconin();

	/*TEST 21: When y is set to a value such that the bottom half of the 
	image is cropped off.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast16(base, 0, (SCRN_HEIGHT - 8), height, BMP_16_TST, destruct,
		blackScreen);
	Cconin();

	/*TEST 22: When y is set to a value such that only the topmost row 
	constituting the image is on screen.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast16(base, 0, SCRN_MAX_Y, height, BMP_16_TST, destruct, blackScreen);
	Cconin();

	/*TEST 23: When the height is set to its minimum possible value.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast16(base, 0, 0, 1, BMP16_HIGH_TST, destruct, blackScreen);
	Cconin();

	/*TEST 24: When the height is set to half of the screen’s height.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast16(base, 0, 0, (SCRN_HEIGHT / 2), BMP16_HIGH_TST, destruct,
		blackScreen);
	Cconin();

	/*TEST 25: When the height given is just below the maximum height 
	of the screen.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast16(base, 0, 0, (SCRN_HEIGHT - 1), BMP16_HIGH_TST, destruct,
		blackScreen);
	Cconin();

	/*TEST 26: When the height given is the maximum height of the screen.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast16(base, 0, 0, SCRN_HEIGHT, BMP16_HIGH_TST, destruct, blackScreen);
	Cconin();

	/*TEST 27: When the height given is greater than the maximum height 
	of the screen.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast16(base, 0, 0, (SCRN_HEIGHT + 1), BMP16_HIGH_TST, destruct,
		blackScreen);
	Cconin();

	/*TEST 28: When the height given is zero.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast16(base, 0, 0, 0, BMP_16_TST, destruct, blackScreen);
	Cconin();

	/*TEST 29: When the height given is negative.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast16(base, 0, 0, -1, BMP_16_TST, destruct, blackScreen);
	Cconin();

	/*TEST 30: When x is 16px off the screen to the left.*/
	blackScreen ?
		fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast16(base, -16, 0, height, BMP_16_TST, destruct, blackScreen);
	Cconin();

	/*TEST 31: When x is equal to the screen length.*/
	blackScreen ?
		fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast16(base, SCRN_LEN, 0, height, BMP_16_TST, destruct, blackScreen);
	Cconin();

	/*TEST 32: When x is greater than the screen length.*/
	blackScreen ?
		fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast16(base, (SCRN_LEN + 1), 0, height, BMP_16_TST, 
			destruct, blackScreen);
	Cconin();

	/*TEST 33: When y is 16px upwards off the screen.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast16(base, 0, -16, height, BMP_16_TST, destruct, blackScreen);
	Cconin();

	/*TEST 34: When y is equal to the screen height.*/
	blackScreen ?
		fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast16(base, 0, SCRN_HEIGHT, height, BMP_16_TST, destruct,
		blackScreen);
	Cconin();

	/*TEST 35: When y is greater than the screen height.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast16(base, 0, (SCRN_HEIGHT + 1), height, BMP_16_TST, destruct,
		blackScreen);
	Cconin();
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

	const UINT8 *BMP8_HIGH_TST = (UINT8 *)BMP_HIGH_TST;

	/*TEST 1: When both x and y are at their minimum visible position 
	on screen.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, 0, 0, height, BMP_8_TST, destruct, blackScreen);
	Cconin();

	/*TEST 2: When x is set to a value corresponding to the middle of 
	the screen.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, SCRN_MID_X, 0, height, BMP_8_TST, destruct, blackScreen);
	Cconin();

	/*TEST 3: When x is set to the maximum value it can be without getting 
	the image cropped.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, RAST8_MAX_VIS_X, 0, height, BMP_8_TST, destruct,
		blackScreen);
	Cconin();

	/*TEST 4: When y is set to a value corresponding to the middle of 
	the screen.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, 0, SCRN_MID_Y, height, BMP_8_TST, destruct, blackScreen);
	Cconin();

	/*TEST 5: When x and y are set to a value corresponding to the middle 
	of the screen.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, SCRN_MID_X, SCRN_MID_Y, height, BMP_8_TST, destruct,
		blackScreen);
	Cconin();

	/*TEST 6: When y is set to the maximum value it can be without getting 
	the image cropped.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, 0, (SCRN_HEIGHT - 8), height, BMP_8_TST, destruct,
		blackScreen);
	Cconin();

	/*TEST 7: When x and y are set to their maximum values they can have 
	without getting the image cropped.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, RAST8_MAX_VIS_X, (SCRN_HEIGHT - 8), height, BMP_8_TST,
		destruct, blackScreen);
	Cconin();

	/*TEST 8: When x is set to a value such that the center of the image 
	is contained in the horizontal center of the screen.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, RAST8_MID_VIS_X, 0, height, BMP_8_TST, destruct,
		blackScreen);
	Cconin();

	/*TEST 9: When y is set to a value such that the center of the image 
	is contained in the vertical center of the screen.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, 0, ((SCRN_HEIGHT / 2) - 4), height, BMP_8_TST, destruct,
		blackScreen);
	Cconin();

	/*TEST 10: When x and y are set to values such that the center of the 
	image is in the center of the screen.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, RAST8_MID_VIS_X, ((SCRN_HEIGHT / 2) - 4), height,
		BMP_8_TST, destruct, blackScreen);
	Cconin();

	/*TEST 11: When x is set to a value such that the image is cropped by 
	1px from the left.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, -1, 0, height, BMP_8_TST, destruct, blackScreen);
	Cconin();

	/*TEST 12: When x is set to a value such that half of the image is 
	cropped from the left.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, -4, 0, height, BMP_8_TST, destruct, blackScreen);
	Cconin();

	/*TEST 13: When x is set to a value such that only the rightmost column 
	constituting the image is on screen.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, RAST8_MIN_X, 0, height, BMP_8_TST, destruct, blackScreen);
	Cconin();

	/*TEST 14: When y is set to a value such that the image is cropped by 
	1px from the top.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, 0, -1, height, BMP_8_TST, destruct, blackScreen);
	Cconin();

	/*TEST 15: When y is set to a value such that the top half of the image 
	is cropped off.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, 0, -4, height, BMP_8_TST, destruct, blackScreen);
	Cconin();

	/*TEST 16: When y is set to a value such that only the bottommost row 
	constituting the image is on screen.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, 0, -7, height, BMP_8_TST, destruct, blackScreen);
	Cconin();

	/*TEST 17: When x is set to a value such that the image is cropped by 
	1px from the right.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, RAST8_MAX_VIS_X + 1, 0, height, BMP_8_TST, destruct,
		blackScreen);
	Cconin();

	/*TEST 18: When x is set to a value such that half of the image is 
	cropped from the right.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, (SCRN_LEN - 4), 0, height, BMP_8_TST, destruct, 
			blackScreen);
	Cconin();

	/*TEST 19: When x is set to a value such that only the leftmost column 
	constituting the image is on screen.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, SCRN_MAX_X, 0, height, BMP_8_TST, destruct, blackScreen);
	Cconin();

	/*TEST 20: When y is set to a value such that the image is cropped by 
	1px from the bottom.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, 0, (SCRN_HEIGHT - 8), height, BMP_8_TST, destruct,
		blackScreen);
	Cconin();

	/*TEST 21: When y is set to a value such that the bottom half of the 
	image is cropped off.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, 0, (SCRN_HEIGHT - 4), height, BMP_8_TST, 
			destruct, blackScreen);
	Cconin();

	/*TEST 22: When y is set to a value such that only the topmost row 
	constituting the image is on screen.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, 0, SCRN_MAX_Y, height, BMP_8_TST, destruct, blackScreen);
	Cconin();

	/*TEST 23: When the height is set to its minimum possible value.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, 0, 0, 1, BMP8_HIGH_TST, destruct, blackScreen);
	Cconin();

	/*TEST 24: When the height is set to half of the screen’s height.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, 0, 0, (SCRN_HEIGHT / 2), BMP8_HIGH_TST, destruct,
		blackScreen);
	Cconin();

	/*TEST 25: When the height given is just below the maximum height 
	of the screen.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, 0, 0, (SCRN_HEIGHT - 1), BMP8_HIGH_TST, destruct,
		blackScreen);
	Cconin();

	/*TEST 26: When the height given is the maximum height of the screen.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, 0, 0, SCRN_HEIGHT, BMP8_HIGH_TST, destruct, blackScreen);
	Cconin();

	/*TEST 27: When the height given is greater than the maximum height 
	of the screen.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, 0, 0, (SCRN_HEIGHT + 1), BMP8_HIGH_TST, destruct,
		blackScreen);
	Cconin();

	/*TEST 28: When the height given is zero.*/
	blackScreen ?
		fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, 0, 0, 0, BMP_8_TST, destruct, blackScreen);
	Cconin();

	/*TEST 29: When the height given is negative.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, 0, 0, -1, BMP_8_TST, destruct, blackScreen);
	Cconin();

	/*TEST 30: When x is 8px off the screen to the left.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, -8, 0, height, BMP_8_TST, destruct, blackScreen);
	Cconin();

	/*TEST 31: When x is equal to the screen length.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, SCRN_LEN, 0, height, BMP_8_TST, destruct, blackScreen);
	Cconin();

	/*TEST 32: When x is greater than the screen length.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, (SCRN_LEN + 1), 0, height, BMP_8_TST, destruct,
		blackScreen);
	Cconin();

	/*TEST 33: When y is 8px upwards off the screen.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, 0, -8, height, BMP_8_TST, destruct, blackScreen);
	Cconin();

	/*TEST 34: When y is equal to the screen height.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, 0, SCRN_HEIGHT, height, BMP_8_TST, destruct, blackScreen);
	Cconin();

	/*TEST 35: When y is greater than the screen height.*/
	blackScreen ? fill_scrn(base_32) : clr_scrn(base_32);
	plot_rast8(base, 0, (SCRN_HEIGHT + 1), height, BMP_8_TST, destruct,
		blackScreen);
	Cconin();
}

/**
 * @brief A function that tests rect_area().
 * @details The screen will be cleared before every test. Enter has to be
 * pressed after every test. Dots will be printed 32px horizontally apart
 * to ensure properly function operation.
 * 
 * @param base The location in memory of start of frame buffer.
 */
void tst_rect_area(UINT32 *base)
{
	const int LEN_TST_DEFAULT = 32;
	const int HEIGHT_TST_DEFAULT = 32;

	/*TEST 1: When x and y are at their minimum valid values.*/
	clr_scrn((UINT32 *)base);
	gridDots((UINT32 *)base);
	rect_area(base, 0, LEN_TST_DEFAULT, 0, HEIGHT_TST_DEFAULT);
	Cconin();

	/*TEST 2: When x is at its middle possible value.*/
	clr_scrn((UINT32 *)base);
	gridDots((UINT32 *)base);
	rect_area(base, SCRN_MID_X, LEN_TST_DEFAULT, 0,
		HEIGHT_TST_DEFAULT);
	Cconin();

	/*TEST 3: When x is at its maximum value where the shape is still
	visible.*/
	clr_scrn((UINT32 *)base);
	gridDots((UINT32 *)base);
	rect_area(base, RAST32_MAX_VIS_X, LEN_TST_DEFAULT, 0,
		HEIGHT_TST_DEFAULT);
	Cconin();

	/*TEST 4: When y is at its middle possible value.*/
	clr_scrn((UINT32 *)base);
	gridDots((UINT32 *)base);
	rect_area(base, 0, LEN_TST_DEFAULT, SCRN_MID_Y,
		HEIGHT_TST_DEFAULT);
	Cconin();

	/*TEST 5: When y is at its maximum value where the shape is still fully on
	screen.*/
	clr_scrn((UINT32 *)base);
	gridDots((UINT32 *)base);
	rect_area(base, 0, LEN_TST_DEFAULT, 368, HEIGHT_TST_DEFAULT);
	Cconin();

	/*TEST 6: When x is set to a value such that the middle of the plotted
	area is in the center of the screen.*/
	clr_scrn((UINT32 *)base);
	gridDots((UINT32 *)base);
	rect_area(base, RAST32_MID_VIS_X, LEN_TST_DEFAULT, 0,
		HEIGHT_TST_DEFAULT);
	Cconin();

	/*TEST 7: When y is set to a value such that the middle of the plotted
	area is in the center of the screen.*/
	clr_scrn((UINT32 *)base);
	gridDots((UINT32 *)base);
	rect_area(base, 0, LEN_TST_DEFAULT, 184, HEIGHT_TST_DEFAULT);
	Cconin();

	/*TEST 8: When x and y are set to the value such that the middle of the
	plotted area is in the center of the screen.*/
	clr_scrn((UINT32 *)base);
	gridDots((UINT32 *)base);
	rect_area(base, RAST32_MID_VIS_X, LEN_TST_DEFAULT, 184,
		HEIGHT_TST_DEFAULT);
	Cconin();

	/*TEST 9: When x and y are set to their maximum possible value.*/
	clr_scrn((UINT32 *)base);
	gridDots((UINT32 *)base);
	rect_area(base, SCRN_MAX_X, LEN_TST_DEFAULT, SCRN_MAX_Y,
		HEIGHT_TST_DEFAULT);
	Cconin();

	/*TEST 10: When height and length are at their minimum values.*/
	clr_scrn((UINT32 *)base);
	gridDots((UINT32 *)base);
	rect_area(base, 0, 1, 0, 1);
	Cconin();

	/*TEST 11: When height and length are equal to the screen size.*/
	clr_scrn((UINT32 *)base);
	gridDots((UINT32 *)base);
	rect_area(base, 0, SCRN_LEN, 0, SCRN_HEIGHT);
	Cconin();

	/*TEST 12: When height and length are greater than the screen size.*/
	clr_scrn((UINT32 *)base);
	gridDots((UINT32 *)base);
	rect_area(base, 0, SCRN_LEN + 1, 0, SCRN_HEIGHT + 1);
	Cconin();

	/*TEST 13: When height and length are different values.*/
	clr_scrn((UINT32 *)base);
	gridDots((UINT32 *)base);
	rect_area(base, 0, 16, 0, HEIGHT_TST_DEFAULT);
	Cconin();
}

/**
 * @brief A function that tests clr_area().
 * @details The screen will be filled before every test. Enter has to be
 * pressed after every test. Dots will be printed 32px horizontally apart
 * to ensure properly function operation.
 * 
 * @param base The location in memory of start of frame buffer.
 */
void tst_clr_area(UINT32 *base)
{
	const int LEN_TST_DEFAULT = 32;
	const int HEIGHT_TST_DEFAULT = 32;

	/*TEST 1: When x and y are at their minimum valid values.*/
	fill_scrn((UINT32 *)base);
	gridDots((UINT32 *)base);
	clr_area(base, 0, LEN_TST_DEFAULT, 0, HEIGHT_TST_DEFAULT);
	Cconin();

	/*TEST 2: When x is at its middle possible value.*/
	fill_scrn((UINT32 *)base);
	gridDots((UINT32 *)base);
	clr_area(base, SCRN_MID_X, LEN_TST_DEFAULT, 0, HEIGHT_TST_DEFAULT);
	Cconin();

	/*TEST 3: When x is at its maximum value where the shape is still
	visible.*/
	fill_scrn((UINT32 *)base);
	gridDots((UINT32 *)base);
	clr_area(base, RAST32_MAX_VIS_X, LEN_TST_DEFAULT, 0,
		HEIGHT_TST_DEFAULT);
	Cconin();

	/*TEST 4: When y is at its middle possible value.*/
	fill_scrn((UINT32 *)base);
	gridDots((UINT32 *)base);
	clr_area(base, 0, LEN_TST_DEFAULT, SCRN_MID_Y, HEIGHT_TST_DEFAULT);
	Cconin();

	/*TEST 5: When y is at its maximum value where the shape is still fully on
	screen.*/
	fill_scrn((UINT32 *)base);
	gridDots((UINT32 *)base);
	clr_area(base, 0, LEN_TST_DEFAULT, 368, HEIGHT_TST_DEFAULT);
	Cconin();

	/*TEST 6: When x is set to a value such that the middle of the plotted
	area is in the center of the screen.*/
	fill_scrn((UINT32 *)base);
	gridDots((UINT32 *)base);
	clr_area(base, RAST32_MID_VIS_X, LEN_TST_DEFAULT, 0,
		HEIGHT_TST_DEFAULT);
	Cconin();

	/*TEST 7: When y is set to a value such that the middle of the plotted
	area is in the center of the screen.*/
	fill_scrn((UINT32 *)base);
	gridDots((UINT32 *)base);
	clr_area(base, 0, LEN_TST_DEFAULT, 184, HEIGHT_TST_DEFAULT);
	Cconin();

	/*TEST 8: When x and y are set to the value such that the middle of the
	plotted area is in the center of the screen.*/
	fill_scrn((UINT32 *)base);
	gridDots((UINT32 *)base);
	clr_area(base, RAST32_MID_VIS_X, LEN_TST_DEFAULT, 184,
		HEIGHT_TST_DEFAULT);
	Cconin();

	/*TEST 9: When x and y are set to their maximum possible value.*/
	fill_scrn((UINT32 *)base);
	gridDots((UINT32 *)base);
	clr_area(base, SCRN_MAX_X, LEN_TST_DEFAULT, SCRN_MAX_Y,
		HEIGHT_TST_DEFAULT);
	Cconin();

	/*TEST 10: When height and length are at their minimum values.*/
	fill_scrn((UINT32 *)base);
	gridDots((UINT32 *)base);
	clr_area(base, 0, 1, 0, 1);
	Cconin();

	/*TEST 11: When height and length are equal to the screen size.*/
	fill_scrn((UINT32 *)base);
	gridDots((UINT32 *)base);
	clr_area(base, 0, SCRN_LEN, 0, SCRN_HEIGHT);
	Cconin();

	/*TEST 12: When height and length are greater than the screen size.*/
	fill_scrn((UINT32 *)base);
	gridDots((UINT32 *)base);
	clr_area(base, 0, SCRN_LEN + 1, 0, SCRN_HEIGHT + 1);
	Cconin();

	/*TEST 13: When height and length are different values.*/
	fill_scrn((UINT32 *)base);
	gridDots((UINT32 *)base);
	clr_area(base, 0, 16, 0, HEIGHT_TST_DEFAULT);
	Cconin();
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