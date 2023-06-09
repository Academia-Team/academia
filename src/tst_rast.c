/**
 * @file tst_rast.c
 * @author Academia Team
 * @brief It is designed to test the functionality of all raster
 * functions.
 * 
 * @copyright Copyright Academia Team 2023
 */

#include <osbind.h>
#include "raster.h"
#include "scrn.h"
#include "test.h"
#include "tst_bmp.h"

#define CLEAR_ON  TRUE
#define CLEAR_OFF FALSE

#define DESTRUCT_ON  TRUE
#define DESTRUCT_OFF FALSE

#define BLACK_SCREEN_ON  TRUE
#define BLACK_SCREEN_OFF FALSE

void tst_plot_px(UINT8 *base);
void tst_hline(UINT32 *base);
void tst_plot_rast32(UINT32 *base, BOOL destruct, BOOL blackScreen);
void tst_plot_rast16(UINT16 *base, BOOL destruct, BOOL blackScreen);
void tst_plot_rast8(UINT8 *base, BOOL destruct, BOOL blackScreen);
void tst_rect_area(UINT32 *base);
void tst_clr_area(UINT32 *base);

void gridDots(UINT32 *base);

int main()
{
	UINT32 *base = (UINT32 *)Physbase();
	off_curs();

	run_test(tst_rect_area(base));
	run_test(tst_clr_area(base));

	run_test(tst_plot_px((UINT8 *)base));
	run_test(tst_hline(base));

	run_test(tst_plot_rast32(base, DESTRUCT_OFF, BLACK_SCREEN_OFF));
	run_test(tst_plot_rast32(base, DESTRUCT_ON, BLACK_SCREEN_OFF));
	run_test(tst_plot_rast32(base, DESTRUCT_ON, BLACK_SCREEN_ON));
	run_test(tst_plot_rast32(base, DESTRUCT_OFF, BLACK_SCREEN_ON));

	run_test(tst_plot_rast16((UINT16 *)base, DESTRUCT_OFF, BLACK_SCREEN_OFF));
	run_test(tst_plot_rast16((UINT16 *)base, DESTRUCT_ON, BLACK_SCREEN_OFF));
	run_test(tst_plot_rast16((UINT16 *)base, DESTRUCT_ON, BLACK_SCREEN_ON));
	run_test(tst_plot_rast16((UINT16 *)base, DESTRUCT_OFF, BLACK_SCREEN_ON));

	run_test(tst_plot_rast8((UINT8 *)base, DESTRUCT_OFF, BLACK_SCREEN_OFF));
	run_test(tst_plot_rast8((UINT8 *)base, DESTRUCT_ON, BLACK_SCREEN_OFF));
	run_test(tst_plot_rast8((UINT8 *)base, DESTRUCT_ON, BLACK_SCREEN_ON));
	run_test(tst_plot_rast8((UINT8 *)base, DESTRUCT_OFF, BLACK_SCREEN_ON));

	clr_scrn(base);
	on_curs();

	return 0;
}

/**
 * @brief A function that tests plot_px().
 * @details The screen will be cleared before every test. Enter has to be
 * pressed after every test.
 * 
 * @param base The location in memory to plot at.
 */
void tst_plot_px(UINT8 *base)
{
	/*TEST 1: When x and y are both at their minimum value (zero).*/
	clr_scrn((UINT32 *)base);
	plot_px(base, 0, 0);
	Cconin();

	/*TEST 2: When x is at its middle value and y is at its minimum value.*/
	clr_scrn((UINT32 *)base);
	plot_px(base, SCRN_MID_X, 0);
	Cconin();

	/*TEST 3: When x is at its maximum and y is at its minimum value.*/
	clr_scrn((UINT32 *)base);
	plot_px(base, SCRN_MAX_X, 0);
	Cconin();

	/*TEST 4: When x is at its minimum value and y is at its middle value.*/
	clr_scrn((UINT32 *)base);
	plot_px(base, 0, SCRN_MID_Y);
	Cconin();

	/* TEST 5: When x is at its minimum and y is at its maximum.*/
	clr_scrn((UINT32 *)base);
	plot_px(base, 0, SCRN_MAX_Y);
	Cconin();

	/*TEST 6: When x and y are both at their maximum value.*/
	clr_scrn((UINT32 *)base);
	plot_px(base, SCRN_MAX_X, SCRN_MAX_Y);
	Cconin();

	/*TEST 7: A white pixel should be plotted when there is a black
	background.*/
	fill_scrn((UINT32 *)base);
	plot_px(base, SCRN_MID_X, SCRN_MID_Y);
	Cconin();

	/*TEST 8: Nothing should be plotted when x is negative.*/
	clr_scrn((UINT32 *)base);
	plot_px(base, -1, 0);
	Cconin();

	/*TEST 9: Nothing should be plotted when x is equal to the SCRN_LEN.*/
	clr_scrn((UINT32 *)base);
	plot_px(base, SCRN_LEN, 0);
	Cconin();

	/*TEST 10: Nothing should be plotted when x is greater than the SCRN_LEN*/
	clr_scrn((UINT32 *)base);
	plot_px(base, SCRN_LEN + 1, 0);
	Cconin();

	/*TEST 11: Nothing should be plotted when y is negative.*/
	clr_scrn((UINT32 *)base);
	plot_px(base, 0, -1);
	Cconin();

	/*TEST 12: Nothing should be plotted when y is equal to the SCRN_HEIGHT.*/
	clr_scrn((UINT32 *)base);
	plot_px(base, 0, SCRN_HEIGHT);
	Cconin();

	/*TEST 13: Nothing should be plotted when y is greater than the
	SCRN_HEIGHT.*/
	clr_scrn((UINT32 *)base);
	plot_px(base, 0, SCRN_HEIGHT + 1);
	Cconin();
}

/**
 * @brief A function that tests hline().
 * @details The screen will be cleared before every test. Enter has to be
 * pressed after every test.
 * 
 * @param base The location in memory to plot at.
 */
void tst_hline(UINT32 *base)
{
	int counter; /* Used for stress test. */

	/*TEST 1: When y is at its minimum value (zero).*/
	clr_scrn(base);
	hline(base, 0, 31, 0);
	Cconin();

	/*TEST 2: When y is at its middle value.*/
	clr_scrn(base);
	hline(base, 0, 31, SCRN_MID_Y);
	Cconin();

	/*TEST 3: When y is at its maximum (on screen) value.*/
	clr_scrn(base);
	hline(base, 0, 31, SCRN_MAX_Y);
	Cconin();

	/*TEST 4: When the line is long-aligned and x1 > x2.*/
	clr_scrn(base);
	hline(base, 31, 0, 0);
	Cconin();

	/*TEST 5: When the line is word-aligned and x1 < x2.*/
	clr_scrn(base);
	hline(base, 0, 15, 0);
	Cconin();

	/*TEST 6: When the line is word-aligned and x1 < x2.*/
	clr_scrn(base);
	hline(base, 15, 0, 0);
	Cconin();

	/*TEST 7: When the line is byte-aligned and x1 < x2.*/
	clr_scrn(base);
	hline(base, 0, 7, 0);
	Cconin();

	/*TEST 8: When the line is byte-aligned and x1 < x2.*/
	clr_scrn(base);
	hline(base, 7, 0, 0);
	Cconin();

	/*TEST 9: When the line is not byte-aligned and x1 < x2.*/
	clr_scrn(base);
	hline(base, 0, 6, 0);
	Cconin();

	/*TEST 10: When the line is not byte-aligned and x1 < x2.*/
	clr_scrn(base);
	hline(base, 6, 0, 0);
	Cconin();

	/*TEST 11: When x1 and x2 in same long-word*/
	clr_scrn(base);
	hline(base, 3, 28, 0);
	Cconin();

	/*TEST 12: When x1 and x2 need shifting no middle segments*/
	clr_scrn(base);
	hline(base, 28, 35, 0);
	Cconin();

	/*TEST 13: When x1 and x2 are at their minimum visible value.*/
	clr_scrn(base);
	hline(base, 0, 0, 0);
	Cconin();

	/*TEST 14: When x1 and x2 are at their middle visible value.*/
	clr_scrn(base);
	hline(base, SCRN_MID_X, SCRN_MID_X, 0);
	Cconin();

	/*TEST 15: When x1 and x2 are at their maximum visible value.*/
	clr_scrn(base);
	hline(base, SCRN_MAX_X, SCRN_MAX_X, 0);
	Cconin();

	/*TEST 16: When x1 is off the screen to the left and x2 is barely on the
	screen.*/
	clr_scrn(base);
	hline(base, -1, 0, 0);
	Cconin();

	/*TEST 17: When x1 is barely on the screen and x2 is off the screen to the
	right.*/
	clr_scrn(base);
	hline(base, SCRN_MAX_X, SCRN_LEN, 0);
	Cconin();

	/*TEST 18: When x1 and x2 are at their minimum and maximum visable value
	on the screen respectively.*/
	clr_scrn(base);
	hline(base, 0, SCRN_MAX_X, SCRN_MAX_Y);
	Cconin();

	/*TEST 19: When x1 and x2 are off the screen to the left and right
	respectively.*/
	clr_scrn(base);
	hline(base, -1, SCRN_LEN, SCRN_MAX_Y);
	Cconin();

	/*TEST 20: Stress test.*/
	clr_scrn(base);
	for(counter = -1; counter < SCRN_HEIGHT; counter++)
	{
		hline(base, counter, SCRN_MAX_X - counter, counter);
	}
	Cconin();

	/*TEST 21: When y is negative, nothing should be plotted.*/
	clr_scrn(base);
	hline(base, 0, 31, -1);
	Cconin();

	/*TEST 22: When y is equal to the SCRN_HEIGHT, nothing should be
	plotted.*/
	clr_scrn(base);
	hline(base, 0, 31, SCRN_HEIGHT);
	Cconin();

	/*TEST 23: When y is greater than SCRN_HEIGHT, nothing should be
	plotted.*/
	clr_scrn(base);
	hline(base, 0, 31, SCRN_HEIGHT + 1);
	Cconin();

	/*TEST 24: When x1 and x2 are off the screen to the left and x1 < x2,
	nothing should be plotted.*/
	clr_scrn(base);
	hline(base, -94, -31, SCRN_MAX_Y);
	Cconin();

	/*TEST 25: When x1 and x2 are off the screen to the left and x1 = x2,
	nothing should be plotted.*/
	clr_scrn(base);
	hline(base, -1, -1, SCRN_MAX_Y);
	Cconin();

	/*TEST 26: When x1 and x2 are off the screen to the left and x1 > x2,
	nothing should be plotted.*/
	clr_scrn(base);
	hline(base, -31, -94, SCRN_MAX_Y);
	Cconin();

	/*TEST 27: When x1 and x2 are off the screen to the right and x1 < x2,
	nothing should be plotted.*/
	clr_scrn(base);
	hline(base, 671, 703, 0);
	Cconin();

	/*TEST 28: When x1 and x2 are off the screen to the right and x1 = x2,
	nothing should be plotted.*/
	clr_scrn(base);
	hline(base, SCRN_LEN, SCRN_LEN, 0);
	Cconin();

	/*TEST 29: When x1 and x2 are off the screen to the right and x1 > x2,
	nothing should be plotted.*/
	clr_scrn(base);
	hline(base, 703, 671, 0);
	Cconin();
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