/**
 * @file tst_bmp.h
 * @author Academia Team
 * @brief Provides some B&W bitmaps that are designed to be useful for testing.
 * 
 * @copyright Copyright Academia Team 2023
 */

#ifndef TST_BMP_H
#define TST_BMP_H

#include "types.h"
#include "scrn.h"

#define BMP_8_TST_HEIGHT    8
#define BMP_16_TST_HEIGHT   16
#define BMP_32_TST_HEIGHT   32
#define BMP_HIGH_TST_HEIGHT SCRN_HEIGHT

/**
 * @brief Provides a black and white 8x8 pixels test image.
 */
extern const UINT8 BMP_8_TST[BMP_8_TST_HEIGHT];

/**
 * @brief Provides a black and white 16x16 pixels test image.
 */
extern const UINT16 BMP_16_TST[BMP_16_TST_HEIGHT];

/**
 * @brief Provides and black and white 32x32 pixels test image.
 */
extern const UINT32 BMP_32_TST[BMP_32_TST_HEIGHT];

/**
 * @brief Provides a black 32 pixels long image that takes up the entire height
 * of the Atari ST's monochrome screen.
 */
extern const UINT32 BMP_HIGH_TST[BMP_HIGH_TST_HEIGHT];

#endif
