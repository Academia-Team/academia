/**
 * @file bitmaps.h
 * @author Academia Team
 * @brief Provides access to various game images.
 * 
 * @copyright Copyright Academia Team 2023
 */

#ifndef BITMAPS_H
#define BITMAPS_H

#include "move.h"
#include "types.h"

#define NUM_BLOCKY_SIZES 3
#define BLOCKY8_HEIGHT 8
#define BLOCKY16_HEIGHT 16
#define BLOCKY32_HEIGHT 32

#define CAR_HEIGHT 32
#define CAR_LEN 32

/**
 * @brief The offset from which the car actually appears (as opposed to the
 * background around the car).
 */
#define CAR_Y_OFFSET 8

/**
 * @brief The height of the car that doesn't include any vertical whitespace.
 */
#define CAR_SMALLEST_HEIGHT 16

#define COLLECTABLE_HEIGHT 32
#define COLLECTABLE_LEN 32

#define FEATHERS_HEIGHT 32
#define FEATHERS_LEN 32

#define GAME_OVER_HEIGHT     66
#define NUM_GAME_OVER_PARTS  15
#define GAME_OVER_PART_LEN 32

#define GRASS_CELL_HEIGHT 32
#define GRASS_CELL_LEN 32

#define HEDGE_CELL_HEIGHT 32
#define HEDGE_CELL_LEN 32

#define ROAD_CELL_HEIGHT 32
#define ROAD_CELL_LEN 32

#define TITLE_HEIGHT     122
#define NUM_TITLE_PARTS   19
#define TITLE_PART_LEN  32

#define SPIKE_CELL_HEIGHT 32
#define SPIKE_CELL_LEN 32

#define TRACK_CELL_HEIGHT 32
#define TRACK_CELL_LEN 32

#define TRAIN_HEIGHT 32
#define TRAIN_PART_LEN 32

/**
 * @brief The height of the train that doesn't include any vertical whitespace.
 */
#define TRAIN_SMALLEST_HEIGHT 30

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
#define CURSOR_LEN 16

#define PLAYER_HEIGHT 32
#define PLAYER_LEN 32

#define NUM_ORIENTATIONS 4
#define NUM_HORZ_ORIENTATIONS 2

/**
 * @brief Returns an array representing a square with a face.
 * @details A copy of the array will also be returned in dest unless dest is
 * NULL or the size is invalid.
 * 
 * @param size The length and height of the bitmap desired (in pixels). Only 8,
 * 16, and 32 are valid.
 * @param dest The location in memory to copy the bitmap to. Can be NULL.
 * @return The address of the bitmap representing the square. Will be NULL if
 * the size is invalid.
 */
const void *getBlockyBitmap(int size, void *dest);

/**
 * @brief Returns an array of UINT32 resembling a car.
 * @details A copy of the array will also be returned in dest unless dest is
 * NULL.
 * 
 * @param orientation The orientation of the car desired (M_EAST/M_WEST).
 * @param dest The location in memory to copy the bitmap to. Can be NULL.
 * @return The address of UINT32 values representing the car. Will be NULL if
 * the orientation is invalid.
 */
const UINT32 *getCarBitmap(Direction orientation, UINT32 *dest);

/**
 * @brief Returns an array of UINT32 resembling a letter grade A in a circle.
 * @details A copy of the array will also be returned in dest unless dest is
 * NULL.
 * 
 * @param dest The location in memory to copy the bitmap to. Can be NULL.
 * @return The address of UINT32 values representing the A in a circle.
 */
const UINT32 *getACollectBitmap(UINT32 *dest);

/**
 * @brief Returns an array of UINT32 resembling a letter grade B in a circle.
 * @details A copy of the array will also be returned in dest unless dest is
 * NULL.
 * 
 * @param dest The location in memory to copy the bitmap to. Can be NULL.
 * @return The address of UINT32 values representing the B in a circle.
 */
const UINT32 *getBCollectBitmap(UINT32 *dest);

/**
 * @brief Returns an array of UINT32 resembling a letter grade C in a circle.
 * @details A copy of the array will also be returned in dest unless dest is
 * NULL.
 * 
 * @param dest The location in memory to copy the bitmap to. Can be NULL.
 * @return The address of UINT32 values representing the C in a circle.
 */
const UINT32 *getCCollectBitmap(UINT32 *dest);

/**
 * @brief Returns an array of UINT32 resembling a bird (Mr. Feathers).
 * @details A copy of the array will also be returned in dest unless dest is
 * NULL.
 * 
 * @param orientation The orientation of the car desired (M_EAST/M_WEST).
 * @param dest The location in memory to copy the bitmap to. Can be NULL.
 * @return The address of UINT32 values representing Mr. Feathers. Will be NULL
 * if the orientation is invalid.
 */
const UINT32 *getFeathersBitmap(Direction orientation, UINT32 *dest);

/**
 * @brief Returns an array of UINT32 resembling the "Game Over" text.
 * @details A copy of the array will also be returned in dest unless dest is
 * NULL. The bitmap is split up into multiple pieces. This function will keep
 * on getting the next piece until there are no more pieces to given, in which
 * case it will return NULL. It will then repeat with the first part of the
 * bitmap.
 * 
 * @param dest The location in memory to copy the bitmap to. Can be NULL.
 * @return The address of UINT32 values representing the "Game Over" text.
 * Will be NULL if all the parts of the bitmap have been exhausted.
 */
const UINT32 *getGameOverBitmap(UINT32 *dest);

/**
 * @brief Returns an array of UINT32 resembling grass.
 * @details A copy of the array will also be returned in dest unless dest is
 * NULL.
 * 
 * @param dest The location in memory to copy the bitmap to. Can be NULL.
 * @return The address of UINT32 values representing the grass cell.
 */
const UINT32 *getGrassBitmap(UINT32 *dest);

/**
 * @brief Returns an array of UINT32 resembling hedge.
 * @details A copy of the array will also be returned in dest unless dest is
 * NULL.
 * 
 * @param dest The location in memory to copy the bitmap to. Can be NULL.
 * @return The address of UINT32 values representing the hedge cell.
 */
const UINT32 *getHedgeBitmap(UINT32 *dest);

/**
 * @brief Returns an array of UINT16 resembling a bird (Mr. Feathers).
 * @details A copy of the array will also be returned in dest unless dest is
 * NULL.
 * 
 * @param dest The location in memory to copy the bitmap to. Can be NULL.
 * @return The address of UINT16 values representing Mr. Feathers.
 */
const UINT16 *getMouseCursor(UINT16 *dest);

/**
 * @brief Returns an array of UINT32 resembling the alpha mask for a player.
 * @details A copy of the array will also be returned in dest unless dest is
 * NULL.
 * 
 * @param orientation The orientation of the player desired
 * (M_EAST, M_WEST, M_NORTH, M_SOUTH).
 * @param dest The location in memory to copy the bitmap to. Can be NULL.
 * @return The address of UINT32 values representing the player alpha mask.
 * Will be NULL if the orientation is invalid.
 */
const UINT32 *getPlayerAlpha(Direction orientation, UINT32 *dest);

/**
 * @brief Returns an array of UINT32 resembling the player.
 * @details A copy of the array will also be returned in dest unless dest is
 * NULL.
 * 
 * @param orientation The orientation of the player desired
 * (M_EAST, M_WEST, M_NORTH, M_SOUTH).
 * @param dest The location in memory to copy the bitmap to. Can be NULL.
 * @return The address of UINT32 values representing the player.
 * Will be NULL if the orientation is invalid.
 */
const UINT32 *getPlayerBitmap(Direction orientation, UINT32 *dest);

/**
 * @brief Returns an array of UINT32 resembling road.
 * @details A copy of the array will also be returned in dest unless dest is
 * NULL.
 * 
 * @param dest The location in memory to copy the bitmap to. Can be NULL.
 * @return The address of UINT32 values representing the road cell.
 */
const UINT32 *getRoadBitmap(UINT32 *dest);

/**
 * @brief Returns an array of UINT32 resembling spike.
 * @details A copy of the array will also be returned in dest unless dest is
 * NULL.
 * 
 * @param dest The location in memory to copy the bitmap to. Can be NULL.
 * @return The address of UINT32 values representing the spike cell.
 */
const UINT32 *getSpikeBitmap(UINT32 *dest);

/**
 * @brief Returns an array of UINT32 resembling the title text.
 * @details A copy of the array will also be returned in dest unless dest is
 * NULL. The bitmap is split up into multiple pieces. This function will keep
 * on getting the next piece until there are no more pieces to given, in which
 * case it will return NULL. It will then repeat with the first part of the
 * bitmap.
 * 
 * @param dest The location in memory to copy the bitmap to. Can be NULL.
 * @return The address of UINT32 values representing the title text. Will be
 * NULL if all the parts of the bitmap have been exhausted.
 */
const UINT32 *getTitleBitmap(UINT32 *dest);

/**
 * @brief Returns an array of UINT32 resembling a train track.
 * @details A copy of the array will also be returned in dest unless dest is
 * NULL.
 * 
 * @param dest The location in memory to copy the bitmap to. Can be NULL.
 * @return The address of UINT32 values representing the track cell.
 */
const UINT32 *getTrackBitmap(UINT32 *dest);

/**
 * @brief Returns an array of UINT32 resembling a train.
 * @details A copy of the array will also be returned in dest unless dest is
 * NULL. The bitmap is split up into multiple pieces. This function will keep
 * on getting the next piece until there are no more pieces to given, in which
 * case it will return NULL. It will then repeat with the first part of the
 * bitmap.
 * 
 * @param dest The location in memory to copy the bitmap to. Can be NULL.
 * @return The address of UINT32 values representing a train. Will be NULL if
 * all the parts of the bitmap have been exhausted.
 */
const UINT32 *getTrainBitmap(UINT32 *dest);

#endif