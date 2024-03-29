/**
 * @file tst_shp.c
 * @author Academia Team
 * @brief It is designed to test the functionality of plotting shapes to the
 * screen.
 * 
 * @copyright Copyright Academia Team 2023
 */

#include "bool.h"
#include "raster.h"
#include "scrn.h"
#include "test.h"
#include "tst_hndl.h"
#include "tst_rast.h"
#include "types.h"

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

void regHlineTests(void);
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

void regRectAreaTests(void);
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

void regClrAreaTests(void);
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

int main(int argc, char **argv)
{
	regPlotPxTests(BLACK_SCREEN_OFF);
	regPlotPxTests(BLACK_SCREEN_ON);

	regHlineTests();
	regRectAreaTests();
	regClrAreaTests();

	handleTests();

	return 0;
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
void regHlineTests(void)
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
 * @brief Handle the registration of all tests related to the rect_area()
 * function.
 */
void regRectAreaTests(void)
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
void regClrAreaTests(void)
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