/**
 * @file bitmaps.h
 * @author Academia Team
 * @brief Provides access to various game images.
 * 
 * @copyright Copyright Academia Team 2023
 */

#ifndef BITMAPS_H
#define BITMAPS_H

#include "types.h"
#include "model.h" /*For some constants*/

#define CAR_HEIGHT 16
#define CAR_LEN 32

/**
 * @brief The offset from which the car actually appears (as opposed to the
 * background around the car).
 */
#define CAR_Y_OFFSET 8

#define COLLECTABLE_HEIGHT 32
#define NUM_COLLECTABLES 3

#define GAME_OVER_HEIGHT     93
#define NUM_GAME_OVER_PARTS  15
#define GAME_OVER_PART_WIDTH 32

#define HAZARD_HEIGHT 32
#define NUM_HORZ_ORIENTATIONS 2

#define TITLE_HEIGHT     132
#define NUM_TITLE_PARTS   18
#define TITLE_PART_WIDTH  32

#define TRAIN_HEIGHT 30
#define NUM_TRAIN_PARTS 3
#define TRAIN_LEN 85

/**
 * @brief The offset from which the train actually appears horizontally (as
 * opposed to the background around the train).
 */
#define TRAIN_X_OFFSET 7

/**
 * @brief The offset from which the train actually appears vertically (as
 * opposed to the background around the train).
 */
#define TRAIN_Y_OFFSET 1


#define CURSOR_HEIGHT 16
#define PLAYER_HEIGHT 32
#define NUM_PLAYER_ALPHA_MASKS 3
#define NUM_ORIENTATIONS 4

extern const UINT32 carBitmap[][HAZARD_HEIGHT];
extern const UINT32 cellBitmap[][CELL_HEIGHT];
extern const UINT32 collectableBitmap[][COLLECTABLE_HEIGHT];
extern const UINT32 feathersBitmap[][HAZARD_HEIGHT];
extern const UINT32 gameOverBitmap[][GAME_OVER_HEIGHT];
extern const UINT16 mouseCursor[CURSOR_HEIGHT];
extern const UINT32 playerAlpha[][PLAYER_HEIGHT];
extern const UINT32 playerBitmap[][PLAYER_HEIGHT];
extern const UINT32 titleBitmap[][TITLE_HEIGHT];
extern const UINT32 trainBitmap[][HAZARD_HEIGHT];

#endif