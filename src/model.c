/**
 * @file model.c
 * @author Academia Team
 * @brief Contains functions to handle all game world model data.
 * 
 * @copyright Copyright Academia Team 2023
 */

#include <stdlib.h>
#include <string.h>

#include "bool.h"
#include "model.h"
#include "move.h"
#include "num_util.h"
#include "scrn.h"
#include "types.h"

#define MAX_INFO_BAR_Y (SCRN_MAX_Y - (INFO_BAR_FONT_HEIGHT - 1))

/**
 * @brief Randomly chooses between LEFT and RIGHT.
 */
#define randHorzDir() ((random(1) == 0) ? M_LEFT : M_RIGHT)

/**
 * @brief Initializes a row with grass cells and no hazards.
 * 
 * @param row The row to initialize.
 * @param rowY The y coordinate of the row to initialize.
 */
#define initSafeRow(row, rowY) prepRow(row, rowY, GRASS_CELL, M_NONE)

BOOL probPlaceHazard(HazType hazard);

void initButton(Button* button, int x, int y, int height, int width,
				LabelStr text);

int addInfoBar(Menu* menu, int y, int spacing)
{
	int ID = -1;

	if (menu->infobarFillLevel < MAX_NUM_INFOBAR && y >= 0 &&
		y <= MAX_INFO_BAR_Y && spacing >= 0 && spacing < SCRN_HEIGHT)
	{
		ID = menu->infobarFillLevel++;
		
		menu->infoBars[ID].y = y;
		menu->infoBars[ID].spacingBetweenLabels = spacing;
		menu->infoBars[ID].numLabels = 0;
		menu->infoBars[ID].needsUpdate = TRUE;
	}

	return ID;
}

void addInfoText(Menu* menu, int ID, char* string)
{
	const int NEW_X = horzCentreScrn(string, INFO_BAR_FONT_WIDTH);

	int newY;
	int prevY;
	int endY;
	int textIdx;

	if (ID >= 0 && ID < menu->infobarFillLevel)
	{
		textIdx = menu->infoBars[ID].numLabels;
		newY = menu->infoBars[ID].y;

		if (menu->infoBars[ID].numLabels > 0)
		{
			prevY = menu->infoBars[ID].labels[textIdx - 1].y;

			newY = prevY + INFO_BAR_FONT_HEIGHT +
				   menu->infoBars[ID].spacingBetweenLabels;
		}

		endY = newY + INFO_BAR_FONT_HEIGHT - 1;

		if (textIdx < MAX_INFO_LABELS && endY <= SCRN_MAX_Y)
		{
			initLabel(&menu->infoBars[ID].labels[textIdx], NEW_X, newY, string);

			menu->infoBars[ID].needsUpdate = TRUE;
			menu->infoBars[ID].numLabels++;
		}
	}
}

void removeInfoText(Menu* menu, int ID, int index)
{
	InfoBar* const infoBar = &menu->infoBars[ID];

	int replaceIndex;

	if (index >= 0 && index < infoBar->numLabels)
	{
		for (replaceIndex = index; replaceIndex < infoBar->numLabels - 1;
			 replaceIndex++)
		{
			infoBar->labels[replaceIndex] = infoBar->labels[replaceIndex + 1];
		}

		infoBar->numLabels--;
		infoBar->needsUpdate = TRUE;
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
	row->horzDirection = (dir != M_LEFT && dir != M_RIGHT ? M_RIGHT : dir);
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
			row->hazards[index].orientation = M_NONE;
		}
		else
		{
			row->hazards[index].orientation = (row->horzDirection == M_LEFT ?
										 	   M_WEST : M_EAST);
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
	scoreBox->labelRendered = FALSE;
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

void copyScore(Score* dest, const Score* const src)
{
	dest->value = src->value;
}

SINT32 cmpScore(const Score* const s1, const Score* const s2)
{
	SINT32 scoreVal1 = (s1->value > SINT32_MAX ? SINT32_MAX : s1->value);
	SINT32 scoreVal2 = (s2->value > SINT32_MAX ? SINT32_MAX : s2->value);

	return scoreVal1 - scoreVal2;
}

void initLives (int x, int y, Lives* lifeBox)
{
	lifeBox->value = START_LIVES;
	lifeBox->x = x + LIVES_X_TEXT_DIST;
	lifeBox->y = y;

	initLabel(&lifeBox->label, x, y + 1, "LIVES:");
	lifeBox->labelRendered = FALSE;
}

void initLabel(Label* label, int x, int y, const char* text)
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
	player->orientation = M_SOUTH;
	initMoveQueue(&player->moveQueue);

	player->immune = FALSE;
	player->alive  = TRUE;
}

BOOL playerMayMove(const Player * const player)
{
	return (!isMoveQueueEmpty(&player->moveQueue));
}

void getPlayerNextMove(const Player * const player, MoveFrame *nextMovement)
{
	if (nextMovement != NULL)
	{
		peekAtMoveFrame(nextMovement, &player->moveQueue);
	}
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

int addButton(Menu* menu, int x, int y, int height, int width, LabelStr text)
{
	int returnVal = -1;

	if (menu->buttonFillLevel < MAX_NUM_MENU_BUTTON)
	{
		returnVal = menu->buttonFillLevel;
		initButton(&menu->buttons[menu->buttonFillLevel++], x, y, height, width,
				   text);
	}

	return returnVal;
}

/**
 * @brief Initializes a Button with the given coordinates, size, and string.
 * @details The x, y coordinate is the top left corner of the button. Height 
 * grows downwards and width grows rightwards. Text will be centered on the 
 * button.
 * 
 * @param button A pointer to the Button object to initialize.
 * @param x The x coordinate of the Button (in pixels).
 * @param y The y coordinate of the Button (in pixels). 
 * @param height The height of the Button (in pixels).
 * @param width The width of the Button (in pixels).
 * @param text The text that should be a part of the Button.
 */
void initButton(Button* button, int x, int y, int height, int width,
				LabelStr text)
{
	int textX;
	int textY;

	button->x = x;
	button->y = y;
	button->height = height;
	button->width = width;

	/* Center the label vertically and horizontally on the button. */
	textX = x + ((width / 2 - 1) - ((strlen(text) / 2) * INFO_BAR_FONT_WIDTH));
	textY = y + ((height / 2 - 1) - ((INFO_BAR_FONT_HEIGHT >> 1) - 1));
	initLabel(&button->label, textX, textY, text);

	button->selected = FALSE;
}

void initMenu(Menu* menu, BOOL blackScreen, int borderWidth, int borderHeight)
{
	menu->buttonFillLevel = 0;
	menu->oldButtonSel = menu->buttonSel = menu->futureButtonSel = NO_BTN_SEL;
	menu->infobarFillLevel = 0;

	menu->blackScreen    = blackScreen;
	menu->borderWidth    = (borderWidth < 0 ? 0 : borderWidth);
	menu->borderHeight   = (borderHeight < 0 ? 0 : borderHeight);
	menu->initialRender = FALSE;
}