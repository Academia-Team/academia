/**
 * @file tst_bmp.c
 * @author Academia Team
 * @brief It is designed to test the functionality of plotting raster images to
 * the screen.
 * 
 * @copyright Copyright Academia Team 2023
 */

#include <string.h>

#include "bitmaps.h"
#include "bool.h"
#include "raster.h"
#include "scrn.h"
#include "test.h"
#include "tst_hndl.h"
#include "tst_rast.h"
#include "types.h"

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

void regRast8Tests(BOOL blackScreen, BOOL destructive);
void t1Rast8(ArgList *args);
void t2Rast8(ArgList *args);
void t3Rast8(ArgList *args);
void t4Rast8(ArgList *args);
void t5Rast8(ArgList *args);
void t6Rast8(ArgList *args);
void t7Rast8(ArgList *args);
void t8Rast8(ArgList *args);
void t9Rast8(ArgList *args);
void t10Rast8(ArgList *args);
void t11Rast8(ArgList *args);
void t12Rast8(ArgList *args);
void t13Rast8(ArgList *args);
void t14Rast8(ArgList *args);
void t15Rast8(ArgList *args);
void t16Rast8(ArgList *args);
void t17Rast8(ArgList *args);
void t18Rast8(ArgList *args);
void t19Rast8(ArgList *args);
void t20Rast8(ArgList *args);
void t21Rast8(ArgList *args);
void t22Rast8(ArgList *args);
void t23Rast8(ArgList *args);
void t24Rast8(ArgList *args);
void t25Rast8(ArgList *args);
void t26Rast8(ArgList *args);
void t27Rast8(ArgList *args);
void t28Rast8(ArgList *args);
void t29Rast8(ArgList *args);
void t30Rast8(ArgList *args);
void t31Rast8(ArgList *args);
void t32Rast8(ArgList *args);
void t33Rast8(ArgList *args);
void t34Rast8(ArgList *args);
void t35Rast8(ArgList *args);

int main(int argc, char **argv)
{
	regRast32Tests(BLACK_SCREEN_OFF, DESTRUCT_OFF);
	regRast32Tests(BLACK_SCREEN_OFF, DESTRUCT_ON);
	regRast32Tests(BLACK_SCREEN_ON, DESTRUCT_OFF);
	regRast32Tests(BLACK_SCREEN_ON, DESTRUCT_ON);

	regRast16Tests(BLACK_SCREEN_OFF, DESTRUCT_OFF);
	regRast16Tests(BLACK_SCREEN_OFF, DESTRUCT_ON);
	regRast16Tests(BLACK_SCREEN_ON, DESTRUCT_OFF);
	regRast16Tests(BLACK_SCREEN_ON, DESTRUCT_ON);

	regRast8Tests(BLACK_SCREEN_OFF, DESTRUCT_OFF);
	regRast8Tests(BLACK_SCREEN_OFF, DESTRUCT_ON);
	regRast8Tests(BLACK_SCREEN_ON, DESTRUCT_OFF);
	regRast8Tests(BLACK_SCREEN_ON, DESTRUCT_ON);

	handleTests();

	return 0;
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
 * @brief Handle the registration of all tests related to the plot_rast8()
 * function.
 * 
 * @param blackScreen Whether the tests registered should utilize a blank white
 * or black screen.
 * @param destructive Whether the tests registered should destroy any existing
 * imagery on the surface or not.
 */
void regRast8Tests(BOOL blackScreen, BOOL destructive)
{
	TestSuiteID suiteID;

	if (blackScreen)
	{
		if (destructive)
		{
			suiteID = registerTestSuite("Tests plotting 8px wide bitmaps destructively on a black surface.",
										rastTstBlack);
		}
		else
		{
			suiteID = registerTestSuite("Tests plotting 8px wide bitmaps non-destructively on a black surface.",
										rastTstBlackPerserve);
		}
	}
	else
	{
		if (destructive)
		{
			suiteID = registerTestSuite("Tests plotting 8px wide bitmaps destructively on a white surface.",
										rastTstWhite);
		}
		else
		{
			suiteID = registerTestSuite("Tests plotting 8px wide bitmaps non-destructively on a white surface.",
										rastTstWhitePerserve);
		}
	}

	registerTestCase(suiteID, "When both x and y are at their minimum value (zero).",
					 NULL, t1Rast8);

	registerTestCase(suiteID, "When x is set to a value corresponding to the middle of the screen.",
					 NULL, t2Rast8);

	registerTestCase(suiteID, "When x is set to the maximum value it can be without getting the image cropped.",
					 NULL, t3Rast8);

	registerTestCase(suiteID, "When y is set to a value corresponding to the middle of the screen.",
					 NULL, t4Rast8);

	registerTestCase(suiteID, "When x and y are set to a value corresponding to the middle of the screen.",
					 NULL, t5Rast8);

	registerTestCase(suiteID, "When y is set to the maximum value it can be without getting the image cropped.",
					 NULL, t6Rast8);
	
	registerTestCase(suiteID, "When x and y are set to their maximum values they can have without getting the image cropped.",
					 NULL, t7Rast8);

	registerTestCase(suiteID, "When x is set to a value such that the center of the image is at the horizontal center of the screen.",
					 NULL, t8Rast8);

	registerTestCase(suiteID, "When y is set to a value such that the center of the image is at the vertical center of the screen.",
					 NULL, t9Rast8);

	registerTestCase(suiteID, "When x and y are set to values such that the center of the image is in the center of the screen.",
					 NULL, t10Rast8);

	registerTestCase(suiteID, "When x is set to a value such that the image is cropped by 1px from the left.",
					 NULL, t11Rast8);

	registerTestCase(suiteID, "When x is set to a value such that half of the image is cropped from the left.",
					 NULL, t12Rast8);
	
	registerTestCase(suiteID, "When x is set to a value such that only the rightmost column constituting the image is on screen.",
					 NULL, t13Rast8);

	registerTestCase(suiteID, "When y is set to a value such that the image is cropped by 1px from the top.",
					 NULL, t14Rast8);

	registerTestCase(suiteID, "When y is set to a value such that the top half of the image is cropped off.",
					 NULL, t15Rast8);

	registerTestCase(suiteID, "When y is set to a value such that only the bottommost row constituting the image is on screen.",
					 NULL, t16Rast8);

	registerTestCase(suiteID, "When x is set to a value such that the image is cropped by 1px from the right.",
					 NULL, t17Rast8);

	registerTestCase(suiteID, "When x is set to a value such that half of the image is cropped from the right.",
					 NULL, t18Rast8);

	registerTestCase(suiteID, "When x is set to a value such that only the leftmost column constituting the image is on screen.",
					 NULL, t19Rast8);

	registerTestCase(suiteID, "When y is set to a value such that the image is cropped by 1px from the bottom.",
					 NULL, t20Rast8);
	
	registerTestCase(suiteID, "When y is set to a value such that the bottom half of the image is cropped off.",
					 NULL, t21Rast8);

	registerTestCase(suiteID, "When y is set to a value such that only the topmost row constituting the image is on screen.",
					 NULL, t22Rast8);

	registerTestCase(suiteID, "When the height is set to its minimum possible value.",
					 NULL, t23Rast8);

	registerTestCase(suiteID, "When the height is set to half of the screen's height.",
					 NULL, t24Rast8);

	registerTestCase(suiteID, "When the height given is just below the maximum height of the screen.",
					 NULL, t25Rast8);

	registerTestCase(suiteID, "When the height given is equal to the maximum height of the screen.",
					 NULL, t26Rast8);
	
	registerTestCase(suiteID, "When the height given is greater than the maximum height of the screen.",
					 NULL, t27Rast8);

	registerTestCase(suiteID, "When the height is zero.",
					 NULL, t28Rast8);

	registerTestCase(suiteID, "When the height is negative.",
					 NULL, t29Rast8);

	registerTestCase(suiteID, "When x is 8px off the screen to the left.",
					 NULL, t30Rast8);

	registerTestCase(suiteID, "When x is equal to the screen length.",
					 NULL, t31Rast8);

	registerTestCase(suiteID, "When x is greater than the screen length.",
					 NULL, t32Rast8);

	registerTestCase(suiteID, "When y is 8px upwards off the screen.",
					 NULL, t33Rast8);

	registerTestCase(suiteID, "When y is equal to the screen height.",
					 NULL, t34Rast8);

	registerTestCase(suiteID, "When y is greater than the screen height.",
					 NULL, t35Rast8);
}

/**
 * @brief Tests plot_rast8() when both x and y are at their minimum value
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
void t1Rast8(ArgList *args)
{
	const int LEN    = 8;
	const int HEIGHT = 8;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT8 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast8((UINT8 *)getArgFromList("base", args), 0, 0, HEIGHT, img,
				destructive, blackScreen);
}

/**
 * @brief Tests plot_rast8() when x is set to a value corresponding to the
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
void t2Rast8(ArgList *args)
{
	const int LEN    = 8;
	const int HEIGHT = 8;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT8 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast8((UINT8 *)getArgFromList("base", args), SCRN_MID_X, 0, HEIGHT,
				img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast8() when x is set to the maximum value it can be
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
void t3Rast8(ArgList *args)
{
	const int LEN    = 8;
	const int HEIGHT = 8;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT8 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast8((UINT8 *)getArgFromList("base", args), RAST8_MAX_VIS_X, 0,
				HEIGHT, img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast8() when y is set to a value corresponding to the
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
void t4Rast8(ArgList *args)
{
	const int LEN    = 8;
	const int HEIGHT = 8;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT8 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast8((UINT8 *)getArgFromList("base", args), 0, SCRN_MID_Y, HEIGHT,
				img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast8() when x and y are set to a value corresponding to
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
void t5Rast8(ArgList *args)
{
	const int LEN    = 8;
	const int HEIGHT = 8;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT8 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast8((UINT8 *)getArgFromList("base", args), SCRN_MID_X, SCRN_MID_Y,
				HEIGHT, img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast8() when y is set to the maximum value it can be
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
void t6Rast8(ArgList *args)
{
	const int LEN    = 8;
	const int HEIGHT = 8;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT8 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast8((UINT8 *)getArgFromList("base", args), 0, RAST8H_MAX_VIS_Y,
				HEIGHT, img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast8() when x and y are set to their maximum values they
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
void t7Rast8(ArgList *args)
{
	const int LEN    = 8;
	const int HEIGHT = 8;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT8 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast8((UINT8 *)getArgFromList("base", args), RAST8_MAX_VIS_X,
				RAST8H_MAX_VIS_Y, HEIGHT, img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast8() when x is set to a value such that the center of
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
void t8Rast8(ArgList *args)
{
	const int LEN    = 8;
	const int HEIGHT = 8;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT8 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast8((UINT8 *)getArgFromList("base", args), RAST8_MID_VIS_X, 0,
				HEIGHT, img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast8() when y is set to a value such that the center of
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
void t9Rast8(ArgList *args)
{
	const int LEN    = 8;
	const int HEIGHT = 8;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT8 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast8((UINT8 *)getArgFromList("base", args), 0, RAST8H_MID_VIS_Y,
				HEIGHT, img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast8() when x and y are set to values such that the
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
void t10Rast8(ArgList *args)
{
	const int LEN    = 8;
	const int HEIGHT = 8;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT8 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast8((UINT8 *)getArgFromList("base", args), RAST8_MID_VIS_X,
				RAST8H_MID_VIS_Y, HEIGHT, img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast8() when x is set to a value such that the image is
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
void t11Rast8(ArgList *args)
{
	const int LEN    = 8;
	const int HEIGHT = 8;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT8 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast8((UINT8 *)getArgFromList("base", args), -1, 0, HEIGHT, img,
				destructive, blackScreen);
}

/**
 * @brief Tests plot_rast8() when x is set to a value such that half of the
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
void t12Rast8(ArgList *args)
{
	const int LEN    = 8;
	const int HEIGHT = 8;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT8 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast8((UINT8 *)getArgFromList("base", args), RAST8_LHALF_X, 0,
				HEIGHT, img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast8() when x is set to a value such that only the
 * rightmost column constituting the image is on screen.
 * @details The expected results are that a 8px sliver of the rightmost column
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
void t13Rast8(ArgList *args)
{
	const int LEN    = 8;
	const int HEIGHT = 8;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT8 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast8((UINT8 *)getArgFromList("base", args), RAST8_MIN_X, 0, HEIGHT,
				img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast8() when y is set to a value such that the image is
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
void t14Rast8(ArgList *args)
{
	const int LEN    = 8;
	const int HEIGHT = 8;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT8 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast8((UINT8 *)getArgFromList("base", args), 0, -1, HEIGHT,
				img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast8() when y is set to a value such that the top half of
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
void t15Rast8(ArgList *args)
{
	const int LEN    = 8;
	const int HEIGHT = 8;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT8 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast8((UINT8 *)getArgFromList("base", args), 0, RAST8H_THALF_Y,
				HEIGHT, img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast8() when y is set to a value such that only the
 * bottommost row constituting the image is on screen.
 * @details The expected results are that a 8px sliver of the bottommost row of
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
void t16Rast8(ArgList *args)
{
	const int LEN    = 8;
	const int HEIGHT = 8;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT8 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast8((UINT8 *)getArgFromList("base", args), 0, RAST8H_MIN_Y,
				HEIGHT, img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast8() when x is set to a value such that the image is
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
void t17Rast8(ArgList *args)
{
	const int LEN    = 8;
	const int HEIGHT = 8;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT8 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast8((UINT8 *)getArgFromList("base", args), RAST8_MAX_VIS_X + 1, 0,
				HEIGHT, img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast8() when x is set to a value such that half of the
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
void t18Rast8(ArgList *args)
{
	const int LEN    = 8;
	const int HEIGHT = 8;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT8 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast8((UINT8 *)getArgFromList("base", args), RAST8_RHALF_X, 0,
				HEIGHT, img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast8() when x is set to a value such that only the
 * leftmost column constituting the image is on screen.
 * @details The expected results are that a 8px sliver of the leftmost column
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
void t19Rast8(ArgList *args)
{
	const int LEN    = 8;
	const int HEIGHT = 8;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT8 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast8((UINT8 *)getArgFromList("base", args), SCRN_MAX_X, 0, HEIGHT,
				img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast8() when y is set to a value such that the image is
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
void t20Rast8(ArgList *args)
{
	const int LEN    = 8;
	const int HEIGHT = 8;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT8 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast8((UINT8 *)getArgFromList("base", args), 0,
				RAST8H_MAX_VIS_Y + 1, HEIGHT, img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast8() when y is set to a value such that the bottom half
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
void t21Rast8(ArgList *args)
{
	const int LEN    = 8;
	const int HEIGHT = 8;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT8 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast8((UINT8 *)getArgFromList("base", args), 0, RAST8H_BHALF_Y,
				HEIGHT, img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast8() when y is set to a value such that only the
 * topmost row constituting the image is on screen.
 * @details The expected results are that a 8px sliver of the topmost row of
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
void t22Rast8(ArgList *args)
{
	const int LEN    = 8;
	const int HEIGHT = 8;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT8 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast8((UINT8 *)getArgFromList("base", args), 0, SCRN_MAX_Y, HEIGHT,
				img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast8() when the height is set to its minimum possible
 * value.
 * @details The expected results are that a 8px sliver of the topmost row of
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
void t23Rast8(ArgList *args)
{
	const int LEN    = 8;
	const int HEIGHT = 1;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT8 img[SCRN_HEIGHT];

	memset(img, 0xFF, SCRN_HEIGHT * (LEN >> DIV_SHIFT_BY_8));

	plot_rast8((UINT8 *)getArgFromList("base", args), 0, SCRN_MAX_Y, HEIGHT,
				img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast8() when the height is set to half of the screen's
 * height.
 * @details The expected results are that a 8px image will be plotted in the
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
void t24Rast8(ArgList *args)
{
	const int LEN    = 8;
	const int HEIGHT = SCRN_HEIGHT / 2;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT8 img[SCRN_HEIGHT];

	memset(img, 0xFF, SCRN_HEIGHT * (LEN >> DIV_SHIFT_BY_8));

	plot_rast8((UINT8 *)getArgFromList("base", args), 0, SCRN_MAX_Y, HEIGHT,
				img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast8() when the height given is just below the maximum
 * height of the screen.
 * @details The expected results are that a 8px image will be plotted in the
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
void t25Rast8(ArgList *args)
{
	const int LEN    = 8;
	const int HEIGHT = SCRN_HEIGHT - 1;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT8 img[SCRN_HEIGHT];

	memset(img, 0xFF, SCRN_HEIGHT * (LEN >> DIV_SHIFT_BY_8));

	plot_rast8((UINT8 *)getArgFromList("base", args), 0, SCRN_MAX_Y, HEIGHT,
				img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast8() when the height given is equal to the maximum
 * height of the screen.
 * @details The expected results are that a 8px image will be plotted in the
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
void t26Rast8(ArgList *args)
{
	const int LEN    = 8;
	const int HEIGHT = SCRN_HEIGHT;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT8 img[SCRN_HEIGHT];

	memset(img, 0xFF, SCRN_HEIGHT * (LEN >> DIV_SHIFT_BY_8));

	plot_rast8((UINT8 *)getArgFromList("base", args), 0, SCRN_MAX_Y, HEIGHT,
				img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast8() when the height given is greater than the maximum
 * height of the screen.
 * @details The expected results are that a 8px image will be plotted in the
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
void t27Rast8(ArgList *args)
{
	const int LEN    = 8;
	const int HEIGHT = SCRN_HEIGHT + 1;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT8 img[SCRN_HEIGHT];

	memset(img, 0xFF, SCRN_HEIGHT * (LEN >> DIV_SHIFT_BY_8));

	plot_rast8((UINT8 *)getArgFromList("base", args), 0, SCRN_MAX_Y, HEIGHT,
				img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast8() when the height is zero.
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
void t28Rast8(ArgList *args)
{
	const int LEN    = 8;
	const int HEIGHT = 0;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT8 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast8((UINT8 *)getArgFromList("base", args), 0, 0, HEIGHT, img,
				destructive, blackScreen);
}

/**
 * @brief Tests plot_rast8() when the height is negative.
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
void t29Rast8(ArgList *args)
{
	const int LEN    = 8;
	const int HEIGHT = -1;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT8 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast8((UINT8 *)getArgFromList("base", args), 0, 0, HEIGHT, img,
				destructive, blackScreen);
}

/**
 * @brief Tests plot_rast8() when x is 8px off the screen to the left.
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
void t30Rast8(ArgList *args)
{
	const int LEN    = 8;
	const int HEIGHT = 8;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT8 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast8((UINT8 *)getArgFromList("base", args), -LEN, 0, HEIGHT, img,
				destructive, blackScreen);
}

/**
 * @brief Tests plot_rast8() when x is equal to the screen length.
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
void t31Rast8(ArgList *args)
{
	const int LEN    = 8;
	const int HEIGHT = 8;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT8 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast8((UINT8 *)getArgFromList("base", args), SCRN_LEN, 0, HEIGHT,
				img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast8() when x is greater than the screen length.
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
void t32Rast8(ArgList *args)
{
	const int LEN    = 8;
	const int HEIGHT = 8;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT8 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast8((UINT8 *)getArgFromList("base", args), SCRN_LEN + 1, 0, HEIGHT,
				img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast8() when y is 8px upwards off the screen.
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
void t33Rast8(ArgList *args)
{
	const int LEN    = 8;
	const int HEIGHT = 8;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT8 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast8((UINT8 *)getArgFromList("base", args), 0, -HEIGHT, HEIGHT,
				img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast8() when y is equal to the screen height.
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
void t34Rast8(ArgList *args)
{
	const int LEN    = 8;
	const int HEIGHT = 8;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT8 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast8((UINT8 *)getArgFromList("base", args), 0, SCRN_HEIGHT, HEIGHT,
				img, destructive, blackScreen);
}

/**
 * @brief Tests plot_rast8() when y is greater than the screen height.
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
void t35Rast8(ArgList *args)
{
	const int LEN    = 8;
	const int HEIGHT = 8;
	
	const BOOL blackScreen = *(BOOL *)(getArgFromList("blackScreen", args));
	const BOOL destructive = *(BOOL *)(getArgFromList("destructive", args));

	UINT8 img[SCRN_HEIGHT];

	getBlockyBitmap(LEN, img);

	plot_rast8((UINT8 *)getArgFromList("base", args), 0, SCRN_HEIGHT + 1,
				HEIGHT, img, destructive, blackScreen);
}