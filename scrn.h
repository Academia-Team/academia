/**
 * @file scrn.h
 * @author Academia Team
 * @brief Contains convenience macros corresponding to the size and the
 * different positions on the Atari ST's screen.
 * 
 * @copyright Copyright Academia Team 2023
 */

#ifndef SCRN_H
#define SCRN_H

/**
 * @brief The horizontal length of the Atari ST's monochrome screen (in pixels).
 */
#define SCRN_LEN 640

/**
 * @brief The height of the Atari ST's monochrome screen (in pixels).
 */
#define SCRN_HEIGHT 400

/**
 * @brief The number of pixels in an Atari ST's monochrome screen.
 */
#define SCRN_SIZE 256000

/**
 * @brief The number of bytes in an Atari ST's monochrome screen.
 */
#define SCRN_BYTES 32000

/**
 * @brief The number of words in an Atari ST's monochrome screen.
 */
#define SCRN_WORDS 16000

/**
 * @brief The number of longs in an Atari ST's monochrome screen.
 */
#define SCRN_LONGS 8000


/**
 * @brief The horizontal length of the Atari ST's monochrome screen (in 8-bit
 * bytes).
 */
#define SCRN_LEN_BYTES 80

/**
 * @brief The horizontal length of the Atari ST's monochrome screen (in 16-bit
 * words).
 */
#define SCRN_LEN_WORDS 40

/**
 * @brief The horizontal length of the Atari ST's monochrome screen (in 32-bit
 * long words).
 */
#define SCRN_LEN_LONG 20


/**
 * @brief The maximum value for the x coordinate (in pixels) such that any point
 * plotted in that x coordinate and a valid y coordinate will be visible on the
 * Atari ST's monochrome screen.
 */
#define SCRN_MAX_X 639

/**
 * @brief The maximum value for the y coordinate (in pixels) such that any point
 * plotted in that y coordinate and a valid x coordinate will be visible on the
 * Atari ST's monochrome screen.
 */
#define SCRN_MAX_Y 399


/**
 * @brief The value for the x coordinate (in pixels) that corresponds to the
 * middle point on the Atari ST's monochrome screen.
 */
#define SCRN_MID_X 319

/**
 * @brief The value for the y coordinate (in pixels) that corresponds to the
 * middle point on the Atari ST's monochrome screen.
 */
#define SCRN_MID_Y 199

/**
 * @brief Changes the given x value so that it fits within the boundaries of the
 * screen.
 * @param fitxVal The given x value.
 */
#define fitXToScrn(fitxVal) \
	if (fitxVal < 0) \
	{\
		fitxVal = 0;\
	}\
	\
	if (fitxVal >= SCRN_LEN) \
	{\
		fitxVal = SCRN_MAX_X;\
	}

#endif