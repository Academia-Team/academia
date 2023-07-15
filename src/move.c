/**
 * @file move.c
 * @author Academia Team
 * @brief Provides constants and functions useful for managing object movement.
 * 
 * @copyright Copyright Academia Team 2023
 */

#include <stddef.h>

#include "move.h"

void initMoveQueue(MoveQueue *queue)
{
	int index;
	
	if (queue != NULL)
	{
		queue->placeIndex = queue->index = 0;

		for (index = 0; index < MAX_ITEMS_IN_MOVE_QUEUE; index++)
		{
			queue->data[index].dir = queue->data[index].orient = M_NONE;
		}
	}
}

Direction getMoveDir(const MoveFrame * const moveFrame)
{
	Direction direction = M_NONE;

	if (moveFrame != NULL)
	{
		direction = moveFrame->dir;
	}
	return direction;
}

Direction getMoveOrient(const MoveFrame * const moveFrame)
{
	Direction orientation = M_NONE;

	if (moveFrame != NULL)
	{
		orientation = moveFrame->orient;
	}

	return orientation;
}

void enqueueMoveFrame(MoveQueue *queue, Direction dir, Direction orient)
{
	if (queue != NULL)
	{
		queue->data[queue->placeIndex].dir = dir;
		queue->data[queue->placeIndex++].orient = orient;
	}
}

void dequeueMoveFrame(MoveFrame *dest, MoveQueue *queue)
{
	if (dest != NULL && queue != NULL)
	{
		peekAtMoveFrame(dest, queue);

		if (queue->index < queue->placeIndex)
		{
			queue->data[queue->index].dir = M_NONE;
			queue->data[queue->index++].orient = M_NONE;
		}
	}
}

void peekAtMoveFrame(MoveFrame *dest, MoveQueue *queue)
{
	if (dest != NULL && queue != NULL)
	{
		if (queue->index >= queue->placeIndex)
		{
			dest->dir = dest->orient = M_NONE;
		}
		else
		{
			dest->dir = queue->data[queue->index].dir;
			dest->orient = queue->data[queue->index].orient;
		}
	}
}