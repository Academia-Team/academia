/**
 * @file move.h
 * @author Academia Team
 * @brief Provides constants and functions useful for managing object movement.
 * 
 * @copyright Copyright Academia Team 2023
 */

#ifndef MOVE_H
#define MOVE_H

#include <stdlib.h>

#include "bool.h"
#include "types.h"

/**
 * @brief Provides both compass and body relative directions that can be used
 * interchangeably.
 */
typedef enum
{
	M_NORTH =  2,
	M_UP    =  2,
	M_SOUTH = -2,
	M_DOWN  = -2,
	M_NONE  =  0,
	M_EAST  =  1,
	M_RIGHT =  1,
	M_WEST  = -1,
	M_LEFT  = -1
} Direction;

/**
 * @brief The direction that has the highest value in the Direction enum.
 */
#define MOVE_MAX_DIR M_NORTH

/**
 * @brief The direction that has the smallest value in the Direction enum.
 */
#define MOVE_MIN_DIR M_SOUTH

#define MAX_ITEMS_IN_MOVE_QUEUE 256

#define isDirOpposite(dir1, dir2) \
	(((dir1) != (dir2)) && (abs(dir1) == abs(dir2)))

typedef struct
{
	Direction dir;
	Direction orient;
} MoveFrame;

typedef struct
{
	MoveFrame data[MAX_ITEMS_IN_MOVE_QUEUE];
	UINT8     placeIndex;
	UINT8     index;
} MoveQueue;

void initMoveQueue(MoveQueue *queue);

#define resetMoveQueue(queue) initMoveQueue(queue)

BOOL isMoveQueueEmpty(MoveQueue *queue);

Direction getMoveDir(const MoveFrame * const moveFrame);

Direction getMoveOrient(const MoveFrame * const moveFrame);

void enqueueMoveFrame(MoveQueue *queue, Direction dir, Direction orient);

void dequeueMoveFrame(MoveFrame *dest, MoveQueue *queue);

void peekAtMoveFrame(MoveFrame *dest, MoveQueue *queue);

#endif
