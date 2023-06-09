/**
 * @file events.c
 * @author Academia Team
 * @brief Contains functions to handle all asynchronous, synchronous, and 
 * condition based events.
 * 
 * @copyright Copyright Academia Team 2023
 */

#include <osbind.h>

#include "effects.h"
#include "events.h"
#include "ints.h"
#include "model.h"

int handleHazardCollision(World* world, Player* player)
{
	int immunityTime = -1;
	if (chkHazardCollision(world, player->x, player->y) &&
		!world->mainPlayer.immune)
	{
		lostLife(&world->mainPlayer);
		if (isPlayerAlive(*player))
		{
			play_pain();
		}
		immunityTime = SECONDS_OF_IMMUNITY;
	}

	return immunityTime;
}

void repopulateWorld(World* world)
{
	int index;
	int startIndex = world->bottom;

	if (world->numWorldShifts < NUM_SAFE_ROWS)
	{
		startIndex = (startIndex + NUM_SAFE_ROWS - world->numWorldShifts) %
					 world->usableRows;
	}

	for (index = startIndex; index != world->top;
		 index = (index + 1) % world->usableRows)
	{
		addHazard(&world->rows[index]);
	}

	addHazard(&world->rows[world->top]);
	world->copyCells = TRUE;
}

void updateCar(World* world)
{
	int index;
	for (index = world->bottom; index != world->top;
		 index = (index + 1) % world->usableRows)
	{
		if (world->rows[index].cellType == ROAD_CELL)
		{
			moveHazard(&world->rows[index]);
			removeHazard(&world->rows[index]);
			world->copyCells = TRUE;
		}
	}

	if (world->rows[index].cellType == ROAD_CELL)
	{
		moveHazard(&world->rows[world->top]);
		removeHazard(&world->rows[world->top]);
		world->copyCells = TRUE;
	}
}

void updateFeathers(World* world)
{
	int index;
	for (index = world->bottom; index != world->top;
		 index = (index + 1) % world->usableRows)
	{
		if (world->rows[index].cellType == GRASS_CELL)
		{
			moveHazard(&world->rows[index]);
			removeHazard(&world->rows[index]);
			world->copyCells = TRUE;
		}
	}

	if (world->rows[index].cellType == GRASS_CELL)
	{
		moveHazard(&world->rows[world->top]);
		removeHazard(&world->rows[world->top]);
		world->copyCells = TRUE;
	}
}

void updateTrain(World* world)
{
	int index;
	for (index = world->bottom; index != world->top;
		 index = (index + 1) % world->usableRows)
	{
		if (world->rows[index].cellType == TRACK_CELL)
		{
			moveHazard(&world->rows[index]);
			removeHazard(&world->rows[index]);
			world->copyCells = TRUE;
		}
	}

	if (world->rows[index].cellType == TRACK_CELL)
	{
		moveHazard(&world->rows[world->top]);
		removeHazard(&world->rows[world->top]);
		world->copyCells = TRUE;
	}
}

void addHazard(Row* row)
{
	int startingX;

	if (row->cellType == GRASS_CELL && row->hazardCount < MAX_FEATHERS)
	{
		if (probPlaceHazard(FEATHERS_HAZ))
		{
			startingX = (row->horzDirection == LEFT ?
						 MAX_CELL_X : MIN_VIS_X_FEATHERS);
			
			row->hazards[row->hazardCount].hazardType = FEATHERS_HAZ;
			row->hazards[row->hazardCount++].x        = startingX;
		}
	}
	else if (row->cellType == TRACK_CELL && row->hazardCount < MAX_TRAINS)
	{
		if (probPlaceHazard(TRAIN_HAZ))
		{
			startingX = (row->horzDirection == LEFT ?
						 MAX_CELL_X : MIN_VIS_X_TRAIN);

			row->hazards[row->hazardCount].hazardType = TRAIN_HAZ;
			row->hazards[row->hazardCount++].x        = startingX;
			play_train();
		}
	}
	else if (row->cellType == ROAD_CELL && row->hazardCount < MAX_CARS)
	{
		if (probPlaceHazard(CAR_HAZ))
		{
			startingX = (row->horzDirection == LEFT ?
						 MAX_CELL_X : MIN_VIS_X_CAR);

			row->hazards[row->hazardCount].hazardType = CAR_HAZ;
			row->hazards[row->hazardCount++].x        = startingX;
		}
	}
}

BOOL chkBorderCollision(int x, int y)
{
	return (x <= LEFT_BORDER || x >= RIGHT_BORDER || y >= BOTTOM_BORDER);
}

void handleCollectableCollision(World* world, Player* player)
{
	int row;
	int column;
	CollectVal collectableValue;

	coordToIndex(world, &row, &column, player->x, player->y);
	collectableValue = world->rows[row].cells[column].collectableValue;

	if (collectableValue != NO_COLLECT)
	{
		updateScore(collectableValue, &player->score);
		switch(collectableValue)
		{
			case A_COLLECT_VAL:
				world->aCount--;
				break;
			case B_COLLECT_VAL:
				world->bCount--;
				break;
			case C_COLLECT_VAL:
				world->cCount--;
				break;
		}
		world->rows[row].cells[column].collectableValue = NO_COLLECT;
		world->renderCells = TRUE;
		play_collect();
	}
}

BOOL chkHazardCollision(const World* const world, int x, int y)
{
	BOOL   hasHaz;
	int    row;
	int    column;
	int    index;
	Hazard currentHaz;

	coordToIndex(world, &row, &column, x, y);
	hasHaz = (world->rows[row].cells[column].cellType == SPIKE_CELL);

	for (index = 0; !hasHaz && index < world->rows[row].hazardCount; index++)
	{
		currentHaz = world->rows[row].hazards[index];
		hasHaz = (currentHaz.hazardType != NO_HAZ && currentHaz.x == x);
	}

	return hasHaz;
}

BOOL chkHedgeCollision(const World* const world, int x, int y)
{
	int column;
	int row;

	coordToIndex(world, &row, &column, x, y);

	return (world->rows[row].cells[column].cellType == HEDGE_CELL);
}

void moveHazard(Row* row)
{
	int index;

	for(index = 0; index < row->hazardCount; index++)
	{
		row->hazards[index].x += (row->horzDirection == RIGHT ?
								  CELL_LEN : -CELL_LEN);
	}
}

void movePlayer(World* world, Player* player)
{
	if (isPlayerAlive(*player))
	{
		if (world->shiftWorld)
		{
			shiftWorld(world);
			if (world->numWorldShifts + 1 >= 0)
			{
				world->numWorldShifts++;
			}

			updateScore(PLAYER_ROW_ADV_SCORE, &player->score);
			world->shiftWorld = FALSE;
			play_walk();
		}
		else
		{
			if (player->y != player->destY)
			{
				player->y += (player->y > player->destY ? -CELL_LEN : CELL_LEN);
				world->copyCells = TRUE;
				play_walk();
			}
			else if (player->x != player->destX)
			{
				player->x += (player->x > player->destX ? -CELL_LEN : CELL_LEN);
				world->copyCells = TRUE;
				play_walk();
			}
		}
	}
}

void removeHazard(Row* row)
{
	int endingX;
	int index;
	int reorderIndex;

	switch(row->cellType)
	{
		case GRASS_CELL:
			endingX = (row->horzDirection == LEFT ?
					   MIN_VIS_X_FEATHERS - CELL_LEN : MAX_CELL_X + CELL_LEN);
			break;
		case ROAD_CELL:
			endingX = (row->horzDirection == LEFT ?
					   MIN_VIS_X_CAR - CELL_LEN : MAX_CELL_X + CELL_LEN);
			break;
		case TRACK_CELL:
			endingX = (row->horzDirection == LEFT ?
					   MIN_VIS_X_TRAIN - CELL_LEN : MAX_CELL_X + CELL_LEN);
			break;
		default:
			endingX = (row->horzDirection == LEFT ?
					   MIN_CELL_X - CELL_LEN : MAX_CELL_X + CELL_LEN);
	}

	for (index = row->hazardCount - 1; index >= 0; index--)
	{
		if (row->hazards[index].x == endingX)
		{
			for (reorderIndex = index;
				 reorderIndex < row->hazardCount - 1;
				 reorderIndex++)
			{
				row->hazards[reorderIndex] = row->hazards[reorderIndex + 1];
			}
			row->hazardCount--;
		}
	}
}

void setPlayerDir(World* world, Player* player, Direction dir)
{
	BOOL dirValid = TRUE;
	int  desiredX = player->x;
	int  desiredY = player->y;

	UINT32 oldSsp = Super(0);
	int    oldIpl = set_ipl(MASK_ALL_INTERRUPTS);
	Super(oldSsp);


	if (isPlayerAlive(*player) && !isPlayerMoving(*world, *player))
	{
		switch(dir)
		{
			case UP:
				player->orientation = NORTH;
				desiredY = player->y - ROW_HEIGHT;
				break;
			case DOWN:
				player->orientation = SOUTH;
				desiredY = player->y + ROW_HEIGHT;
				break;
			case RIGHT:
				player->orientation = EAST;
				desiredX = player->x + CELL_LEN;
				break;
			case LEFT:
				player->orientation = WEST;
				desiredX = player->x - CELL_LEN;
				break;
			default:
				dirValid = FALSE;
		}

		if (dirValid)
		{
			if (!chkBorderCollision(desiredX, desiredY) &&
				!chkHedgeCollision(world, desiredX, desiredY))
			{
				if (dir == UP && player->y == WSHIFT_Y_BOUNDARY)
				{
					world->shiftWorld = TRUE;
				}
				else
				{
					player->destX = desiredX;
					player->destY = desiredY;
				}
			}
		}
	}

	oldSsp = Super(0);
	set_ipl(oldIpl);
	Super(oldSsp);
}

void shiftWorld(World* world)
{
	int index;
	int rowY;
	int cell;
	int collectableValue;

	for(cell = 0; cell < MAX_CELLS; cell++)
	{
		collectableValue = world->rows[world->bottom].cells[cell].collectableValue;
		switch(collectableValue)
			{
				case A_COLLECT_VAL:
					world->aCount--;
					break;
				case B_COLLECT_VAL:
					world->bCount--;
					break;
				case C_COLLECT_VAL:
					world->cCount--;
					break;
			}
	}

	world->top = world->bottom;
	world->bottom = (world->bottom + 1) % world->usableRows;

	for (index = world->bottom, rowY = MAX_ROW_Y;
		 index != world->top;
		 index = (index + 1) % world->usableRows, rowY -= ROW_HEIGHT)
	{
		world->rows[index].y = rowY;
	}

	initRow(world, &(world->rows[world->top]),
			getTopBorderHeight(world->numPlayers));

	world->renderCells = TRUE;
}

void handleInvalidKeyPress()
{
	UINT32 oldSsp  = Super(0);
	int    origIpl = set_ipl(MASK_ALL_INTERRUPTS);

	play_beep();

	set_ipl(origIpl);
	Super(oldSsp);
}