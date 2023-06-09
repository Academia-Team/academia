/**
 * @file model.c
 * @author Academia Team
 * @brief Contains functions to handle all game world model data.
 * 
 * @copyright Copyright Academia Team 2023
 */

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "bool.h"
#include "events.h"
#include "font16.h"
#include "model.h"
#include "scrn.h"
#include "types.h"

/**
 * @brief Randomly chooses between LEFT and RIGHT.
 */
#define randHorzDir() ((random(1) == 0) ? LEFT : RIGHT)

/**
 * @brief Initializes a row with grass cells and no hazards.
 * 
 * @param row The row to initialize.
 * @param rowY The y coordinate of the row to initialize.
 */
#define initSafeRow(row, rowY) prepRow(row, rowY, GRASS_CELL, RIGHT)

BOOL probPlaceHazard(HazType hazard);

int random(int rangeMax)
{
	int value;

	do
	{
		value = rand();
	} while (value == 0);
	
	return (value % (rangeMax + 1));
}

void initInfoBar(InfoBar* infoBar, int y, int spacing, int numLabels, ...)
{
	const int FINAL_Y = y + (numLabels * (FONT16_HEIGHT + spacing) -
						spacing - 1);

	va_list argList;
	int     index;

	infoBar->numLabels = 0;
	
	if (numLabels > 0 && numLabels <= MAX_INFO_LABELS &&
		y >= 0 && y <= SCRN_MAX_Y && FINAL_Y <= SCRN_MAX_Y)
	{
		infoBar->y = y;
		infoBar->spacingBetweenLabels = spacing;
		va_start(argList, numLabels);

		for (index = 0; index < numLabels; index++)
		{
			addInfoText(infoBar, va_arg(argList, char *));
		}
	}

	va_end(argList);
}

void addInfoText(InfoBar* infoBar, char* string)
{
	const int NEW_X = SCRN_MID_X - ((strlen(string) * FONT16_WIDTH) >> 1);
	const int NEW_Y = (infoBar->numLabels == 0 ? infoBar->y :
					   infoBar->labels[infoBar->numLabels - 1].y +
					   FONT16_HEIGHT + infoBar->spacingBetweenLabels);
	const int END_Y = NEW_Y + FONT16_HEIGHT - 1;

	if (infoBar->numLabels < MAX_INFO_LABELS - 1 && END_Y <= SCRN_MAX_Y)
	{
		initLabel(&infoBar->labels[infoBar->numLabels++],
				  (NEW_X < 0 ? 0 : NEW_X), NEW_Y, string);
	}
}

void removeInfoText(InfoBar* infoBar, int index)
{
	int replaceIndex;

	if (index >= 0 && index < infoBar->numLabels)
	{
		for (replaceIndex = index; replaceIndex < infoBar->numLabels - 1;
			 replaceIndex++)
		{
			infoBar->labels[replaceIndex] = infoBar->labels[replaceIndex + 1];
		}

		infoBar->numLabels--;
	}
}

void initWorld (World* world, int numPlayers)
{
	const int MAX_PLAYERS   = 2;
	const int MIN_PLAYERS   = 1;

	int index;
	int rowY;

	if (numPlayers >= MIN_PLAYERS && numPlayers <= MAX_PLAYERS)
	{
		world->usableRows = MAX_ROWS - numPlayers + 1;
		world->numPlayers = numPlayers;

		world->top            = world->usableRows - 1;
		world->bottom         = 0;
		world->numWorldShifts = 0;
		world->shiftWorld     = FALSE;
		world->copyCells      = FALSE;
		world->renderCells    = FALSE;

		world->aCount = 0;
		world->bCount = 0;
		world->cCount = 0;

		initPlayer(&(world->mainPlayer), numPlayers);
		initCorePlayer(&(world->otherPlayer), numPlayers);

		rowY = MAX_ROW_Y;

		for(index = 0; index < NUM_SAFE_ROWS; index++, rowY -= CELL_HEIGHT)
		{
			initSafeRow(&world->rows[index], rowY);
		}

		for(; index < world->usableRows; index++, rowY -= CELL_HEIGHT)
		{
			initRow(world, &(world->rows[index]), rowY);
		}
	}
}

void initRow(World* world, Row* row, int rowY)
{
	prepRow(row, rowY, random(MAX_ROW_CELL_TYPE), randHorzDir());
	initObstacle(row);
	initCollectable(world, row);
	initHazard(row);
}

void prepRow(Row* row, int rowY, CellType rowType, Direction dir)
{
	int cellX;
	int index;

	row->hazardCount   = 0;
	row->hedgeCount    = 0;
	row->spikeCount    = 0;
	row->horzDirection = (dir != LEFT && dir != RIGHT ? RIGHT : dir);
	row->cellType      = rowType;
	row->y             = rowY;

	for(index = 0, cellX = MIN_CELL_X; index < MAX_CELLS; index++,
		cellX += CELL_LEN)
	{
		initCell(&(row->cells[index]), cellX, rowType);
	}
}

void initCell(Cell* cell, int x, CellType cellType)
{
	cell->cellType = cellType;
	cell->collectableValue = NO_COLLECT;
	cell->x = x;
}

void initObstacle(Row* row)
{
	const int HEDGE_PROB = 6;
	const int SPIKE_PROB = 6;

	int index;

	if (row->cellType == GRASS_CELL)
	{
		for (index = 0; index < MAX_CELLS; index++)
		{
			if (row->hedgeCount < MAX_HEDGES &&
				random(HEDGE_PROB - 1) == 0)
			{
				row->cells[index].cellType = HEDGE_CELL;
				row->hedgeCount++;
			}
			else if (row->spikeCount < MAX_SPIKES &&
					 random(SPIKE_PROB - 1) == 0)
			{
				row->cells[index].cellType = SPIKE_CELL;
				row->spikeCount++;
			}
		}
	}
}

void initCollectable(World* world, Row* row)
{
	const int A_PROB = 40;
	const int B_PROB = 30;
	const int C_PROB = 20;

	int  cellPos;
	int  prob;
	BOOL spawnedCollectable = FALSE;

	for (cellPos = 0; ((cellPos < MAX_CELLS)&&(!spawnedCollectable)); cellPos++)
	{
		if (row->cells[cellPos].cellType != HEDGE_CELL)
		{
			if (world->aCount < MAX_A_COLLECTABLES)
			{
				prob = random(A_PROB - 1);

				if (prob == 0)
				{
					row->cells[cellPos].collectableValue = A_COLLECT_VAL;
					world->aCount++;
					spawnedCollectable = TRUE;
				}
			}

			if (!spawnedCollectable && world->bCount < MAX_B_COLLECTABLES)
			{
				prob = random(B_PROB - 1);

				if (prob == 0)
				{
					row->cells[cellPos].collectableValue = B_COLLECT_VAL;
					world->bCount++;
					spawnedCollectable = TRUE;
				}
			}

			if (!spawnedCollectable && world->cCount < MAX_C_COLLECTABLES)
			{
				prob = random(C_PROB - 1);

				if (prob == 0)
				{
					row->cells[cellPos].collectableValue = C_COLLECT_VAL;
					world->cCount++;
					spawnedCollectable = TRUE;
				}
			}
		}
	}
}

void initHazard(Row* row)
{
	int     index;
	int     placementLimit;
	int     hazX = MIN_CELL_X;
	HazType hazard = NO_HAZ;

	if (row->cellType == GRASS_CELL)
	{
		hazard         = FEATHERS_HAZ;
		placementLimit = MAX_FEATHERS;
	}
	else if (row->cellType == TRACK_CELL)
	{
		hazard         = TRAIN_HAZ;
		placementLimit = MAX_TRAINS;
	}
	else if (row->cellType == ROAD_CELL)
	{
		hazard         = CAR_HAZ;
		placementLimit = MAX_CARS;
	}
	else
	{
		hazard         = NO_HAZ;
		placementLimit = 0;
	}

	for (index = 0; index < MAX_HAZARD_IN_ROW; index++)
	{
		row->hazards[index].hazardType = NO_HAZ;
		if (hazard == TRAIN_HAZ)
		{
			row->hazards[index].orientation = SYMMETRIC;
		}
		else
		{
			row->hazards[index].orientation = (row->horzDirection == LEFT ?
										 	   WEST : EAST);
		}
	}
	
	index = 0;
	while (index < placementLimit && hazX <= MAX_CELL_X)
	{
		if (probPlaceHazard(hazard))
		{
			row->hazards[index].x          = hazX;
			row->hazards[index].hazardType = hazard;
			row->hazardCount++;
			index++;
		}

		hazX += CELL_LEN;
	}
}

/**
 * @brief Calculates if a hazard could be placed or not.
 * @details This calculation is done independently of any limits placed on how
 * many hazards can exist at a time.
 * 
 * @param hazard The desired hazard to place into the world.
 * @return TRUE if the hazard can be placed; false otherwise.
 */
BOOL probPlaceHazard(HazType hazard)
{
	const int CAR_PROB      = 5;
	const int TRAIN_PROB    = 10;
	const int FEATHERS_PROB = 10;

	BOOL probToPlaceHaz;

	if (hazard == CAR_HAZ)
	{
		probToPlaceHaz = (random(CAR_PROB - 1) == 0);
	}
	else if (hazard == TRAIN_HAZ)
	{
		probToPlaceHaz = (random(TRAIN_PROB - 1) == 0);
	}
	else if (hazard == FEATHERS_HAZ)
	{
		probToPlaceHaz = (random(FEATHERS_PROB - 1) == 0);
	}
	else
	{
		probToPlaceHaz = FALSE;
	}

	return probToPlaceHaz;
}

void initScore (int x, int y, Score* scoreBox)
{
	scoreBox->value = 0;
	scoreBox->x = x + SCORE_X_TEXT_DIST;
	scoreBox->y = y;

	initLabel(&scoreBox->label, x, y + 1, "SCORE:");
}

void updateScore (UINT32 value, Score* scoreBox)
{
	UINT32 newScore;

	newScore = scoreBox->value + value;

	if (newScore < scoreBox->value || newScore < value)
	{
		scoreBox->value = UINT32_MAX;
	}
	else
	{
		scoreBox->value = newScore;
	}
}

void initLives (int x, int y, Lives* lifeBox)
{
	lifeBox->value = START_LIVES;
	lifeBox->x = x + LIVES_X_TEXT_DIST;
	lifeBox->y = y;

	initLabel(&lifeBox->label, x, y + 1, "LIVES:");
}

void initLabel(Label* label, int x, int y, LabelStr text)
{
	label->x = x;
	label->y = y;
	memcpy(label->text, text, MAX_LABEL_LEN + 1);
}

void initCorePlayer(CorePlayer* player, int numPlayers)
{
	if (numPlayers == 2)
	{
		initScore(SCORE_START_X_2P, SCORE_START_Y_2P, &player->score);
		initLives(LIVES_START_X, LIVES_START_Y_2P, &player->lives);
		player->alive  = TRUE;
	}
}

void initPlayer(Player* player, int numPlayers)
{
	if (numPlayers == 1)
	{
		initScore(SCORE_START_X_1P, SCORE_START_Y_1P, &player->score);
		initLives(LIVES_START_X, LIVES_START_Y_1P, &player->lives);
	}
	else
	{
		initScore(SCORE_START_X_2P, SCORE_START_Y_1P, &player->score);
		initLives(LIVES_START_X, LIVES_START_Y_1P, &player->lives);
	}

	player->x = PLAYER_START_X;
	player->y = PLAYER_START_Y;

	player->destX = player->x;
	player->destY = player->y;
	player->orientation = SOUTH;

	player->immune = FALSE;
	player->alive  = TRUE;
}

void lostLife (Player* player)
{
	if (!player->immune && player->alive)
	{
		if(player->lives.value > 1)
		{
			player->lives.value--;
			toggleImmunity(*player);
		}
		else
		{
			player->lives.value = 0;
			player->alive = FALSE;
		}
	}
}

void lostCoreLife (CorePlayer* player)
{
	if (isPlayerAlive(*player))
	{
		if(player->lives.value != 1)
		{
			player->lives.value--;
		}
		else
		{
			player->lives.value = 0;
			player->alive = FALSE;
		}
	}
}

void coordToIndex(const World* const world, int* row, int* column, int x, int y)
{
	*column = ((x - SIDE_BORDER_WIDTH) >> DIV_SHIFT_BY_32);
	*row = (world->bottom + ((SCRN_HEIGHT - (y + 1)) / 32) - 1) %
		   world->usableRows;
}

void initButton(Button* button, int x, int y, int height, int width,
				LabelStr text)
{
	int textX;
	int textY;

	button->x = x;
	button->y = y;
	button->height = height;
	button->width = width;

	textX = x + ((width / 2 - 1) - ((strlen(text) / 2) * FONT16_WIDTH));
	textY = y + ((height / 2 - 1) - ((FONT16_HEIGHT >> 1) - 1));
	initLabel(&button->label, textX, textY, text);

	button->selected = FALSE;
}

