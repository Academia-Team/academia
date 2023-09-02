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
	M_NORTH       =  2,
	M_UP          =  2,
	M_SOUTH       = -2,
	M_DOWN        = -2,
	M_NONE        =  0,
	M_EAST        =  1,
	M_RIGHT       =  1,
	M_WEST        = -1,
	M_LEFT        = -1,

	M_NORTHEAST   =  3,
	M_SOUTHEAST   = -3,
	M_TOPRIGHT    =  3,
	M_BOTTOMRIGHT = -3,

	M_NORTHWEST   =  4,
	M_SOUTHWEST   = -4,
	M_TOPLEFT     =  4,
	M_BOTTOMLEFT  = -4
} Direction;

/**
 * @brief The maximum number of characters returned by getDirName().
 */
#define MAX_DIR_NAME_LEN 11

/**
 * @brief A type of string guaranteed to be able to hold the string returned by
 * getDirName().
 */
typedef char DirName[MAX_DIR_NAME_LEN + 1];

/**
 * @brief The maximum number of characters returned by getOrientName().
 */
#define MAX_ORIENT_NAME_LEN MAX_DIR_NAME_LEN

/**
 * @brief A type of string guaranteed to be able to hold the string returned by
 * getOrientName().
 */
typedef DirName OrientName;


/**
 * @brief Gets the name corresponding to the given body relative direction
 * (UP, DOWN, LEFT, RIGHT).
 * 
 * @param dirValue The direction to get the name of.
 * @return The name of the direction as a string or "NONE" if no direction is
 * set, or "UNKNOWN" if the given value is not recognized.
 */
#define getBodyRelDir(dirValue) \
	(dirValue == M_UP ? "UP" : \
		(dirValue == M_DOWN ? "DOWN" : \
			(dirValue == M_LEFT ? "LEFT" : \
				(dirValue == M_RIGHT ? "RIGHT" : \
					(dirValue == M_TOPLEFT ? "TOPLEFT" : \
						(dirValue == M_TOPRIGHT ? "TOPRIGHT" : \
							(dirValue == M_BOTTOMLEFT ? "BOTTOMLEFT" : \
								(dirValue == M_BOTTOMRIGHT ? "BOTTOMRIGHT" : \
									(dirValue == M_NONE ? "NONE" : "UNKNOWN") \
								) \
							) \
						) \
					) \
				) \
			) \
		) \
	)

/**
 * @brief Gets the name corresponding to the given compass direction
 * (NORTH, SOUTH, WEST, EAST).
 * 
 * @param dirValue The direction to get the name of.
 * @return The name of the direction as a string or "NONE" if no direction is
 * set, or "UNKNOWN" if the given value is not recognized.
 */
#define getCompassDir(dirValue) \
	(dirValue == M_NORTH ? "NORTH" : \
		(dirValue == M_SOUTH ? "SOUTH" : \
			(dirValue == M_WEST ? "WEST" : \
				(dirValue == M_EAST ? "EAST" : \
					(dirValue == M_NORTHWEST ? "NORTHWEST" : \
						(dirValue == M_NORTHEAST ? "NORTHEAST" : \
							(dirValue == M_SOUTHWEST ? "SOUTHWEST" : \
								(dirValue == M_SOUTHEAST ? "SOUTHEAST" : \
									(dirValue == M_NONE ? "NONE" : "UNKNOWN") \
								) \
							) \
						) \
					) \
				) \
			) \
		) \
	)

/**
 * @brief Gets the name corresponding to the given body relative direction
 * (UP, DOWN, LEFT, RIGHT).
 * 
 * @param dirValue The direction to get the name of.
 * @return The name of the direction as a string or "NONE" if no direction is
 * set, or "UNKNOWN" if the given value is not recognized.
 */
#define getDirName(dirValue) getBodyRelDir(dirValue)

/**
 * @brief Gets the name corresponding to the given orientation
 * (NORTH, SOUTH, WEST, EAST).
 * 
 * @param orientValue The orientation to get the name of.
 * @return The name of the orientation as a string or "NONE" if no orientation
 * is set, or "UNKNOWN" if the given value is not recognized.
 */
#define getOrientName(orientValue) getCompassDir(orientValue)

/**
 * @brief The direction that has the highest value in the Direction enum.
 */
#define MOVE_MAX_DIR M_NORTHWEST

/**
 * @brief The direction that has the smallest value in the Direction enum.
 */
#define MOVE_MIN_DIR M_SOUTHWEST

/**
 * @brief Maximum number of items that can be placed in a MoveQueue without the
 * queue overflowing.
 */
#define MAX_ITEMS_IN_MOVE_QUEUE 256

/**
 * @brief Returns TRUE if the two directions given are opposites; FALSE
 * otherwise.
 */
#define isDirOpposite(dir1, dir2) \
	(((dir1) != (dir2)) && (abs(dir1) == abs(dir2)))

/**
 * @brief Returns TRUE if the given direction is diagonal; FALSE otherwise.
 */
#define isDirDiagonal(dir) \
	((dir) == M_NORTHEAST || (dir) == M_NORTHWEST || (dir) == M_SOUTHEAST || \
	 (dir) == M_SOUTHWEST)

/**
 * @brief A object that stores information about movement in an
 * environment-defined time frame.
 */
typedef struct
{
	Direction dir;
	Direction orient;
} MoveFrame;

/**
 * @brief A object that stores information about multiple movements over time.
 */
typedef struct
{
	MoveFrame data[MAX_ITEMS_IN_MOVE_QUEUE];
	UINT8     placeIndex;
	UINT8     index;
} MoveQueue;

/**
 * @brief Initializes a MoveQueue.
 * 
 * @param queue The MoveQueue to initialize.
 */
void initMoveQueue(MoveQueue *queue);

/**
 * @brief Clears all information stored in a MoveQueue.
 * 
 * @param queue The MoveQueue to reset.
 */
#define resetMoveQueue(queue) initMoveQueue(queue)

/**
 * @brief Returns if the given queue contains any movement information.
 * 
 * @param queue The queue to check if it is empty.
 * @return Returns TRUE if the queue is empty; FALSE otherwise.
 */
BOOL isMoveQueueEmpty(const MoveQueue * const queue);

/**
 * @brief Get the direction specified in the given MoveFrame.
 * 
 * @param moveFrame The MoveFrame to get the direction from.
 * @return The direction specified in the MoveFrame.
 */
Direction getMoveDir(const MoveFrame * const moveFrame);

/**
 * @brief Get the orientation specified in the given MoveFrame.
 * 
 * @param moveFrame The MoveFrame to get the orientation from.
 * @return The orientation specified in the MoveFrame.
 */
Direction getMoveOrient(const MoveFrame * const moveFrame);

/**
 * @brief Enqueues the given movement information into the MoveQueue.
 * @details If the queue is NULL, nothing will be enqueued.
 * 
 * @param queue The queue to enqueue into.
 * @param dir The direction of movement.
 * @param orient The way the moving target is oriented.
 */
void enqueueMoveFrame(MoveQueue *queue, Direction dir, Direction orient);

/**
 * @brief Removes a MoveFrame from the given MoveQueue and returns it.
 * @details If the dest or queue is NULL, nothing will be dequeued.
 * 
 * @param dest The MoveFrame to place the information from the MoveQueue.
 * @param queue The MoveQueue to dequeue the movement information from.
 */
void dequeueMoveFrame(MoveFrame *dest, MoveQueue *queue);

/**
 * @brief Returns a MoveFrame without dequeuing the relevant information from
 * the MoveQueue.
 * @details If the queue is NULL, the resultant information stored in the
 * destination is undefined.
 * 
 * @param dest The MoveFrame to place the information from the MoveQueue.
 * @param queue The queue to get the movement information from.
 */
void peekAtMoveFrame(MoveFrame *dest, const MoveQueue * const queue);

#endif
