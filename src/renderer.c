/**
 * @file renderer.c
 * @author Academia Team
 * @brief Contains functions to render everything in the model.
 * 
 * @copyright Copyright Academia Team 2023
 */

#include <stdlib.h>
#include <string.h>

#include "bitmaps.h"
#include "bool.h"
#include "font16.h"
#include "model.h"
#include "move.h"
#include "raster.h"
#include "renderer.h"
#include "types.h"

#define MAX_NUM_DIGITS_IN_SCORE UINT32_MAX_DIGITS

void clrPlayAreaSect(UINT32 *base, int numPlayers, int x, int length,
					 int y, int height);
void renderCar(UINT32 *base, int x, int y, Direction orientation);
void renderFeathers(UINT32 *base, int x, int y, Direction orientation);
void renderTrain(UINT32 *base, int x, int y);

void renderUpdate(UINT32* base, const World* const world)
{
	int index;
	for(index = world->bottom; index != world->top;
		 index = (index + 1) % world->usableRows)
	{
		renderHazards(base, &world->rows[index]);
	}
	renderHazards(base, &world->rows[world->top]);
	renderPlayers(base, world);
}

void renderPlayArea(UINT32* base, const World* const world)
{
	Label youLabel;
	Label otherLabel;
	
	fill_scrn(base);
	renderWorld(base, world);
	renderUpdate(base, world);

	if (world->numPlayers == 2)
	{
		initLabel(&youLabel, 16, 8,"YOU:");
		initLabel(&otherLabel, 16, 40,"OTHER:");
		renderLabel((UINT16 *)base, &youLabel, TRUE);
		renderLabel((UINT16 *)base, &otherLabel, TRUE);
	}
}

void renderWorld(UINT32* base, const World* const world)
{
	int index;

	fill_scrn(base);

	for (index = world->bottom;
		 index != world->top;
		 index = (index + 1) % world->usableRows)
	{
		renderRow(base, &world->rows[index]);
	}
	renderRow(base, &world->rows[world->top]);
}

void renderRow(UINT32* base, const Row* const row)
{
	int index;

	for (index = 0; index < MAX_CELLS; index++)
	{
		renderCell(base, &row->cells[index], row->y);
	}
}

void renderCell(UINT32* base, const Cell* const cell, int y)
{
	UINT32 cellBitmap[CELL_HEIGHT];
	UINT32 collectableBitmap[COLLECTABLE_HEIGHT];

	switch(cell->cellType)
	{
		case GRASS_CELL:
			getGrassBitmap(cellBitmap);
			break;
		case HEDGE_CELL:
			getHedgeBitmap(cellBitmap);
			break;
		case ROAD_CELL:
			getRoadBitmap(cellBitmap);
			break;
		case SPIKE_CELL:
			getSpikeBitmap(cellBitmap);
			break;
		case TRACK_CELL:
			getTrackBitmap(cellBitmap);
			break;
		default:
			memset(cellBitmap, 0, UINT32_BYTES * CELL_HEIGHT);
	}

	plot_rast32(base, cell->x, y, CELL_HEIGHT, cellBitmap, TRUE, FALSE);
	
	switch(cell->collectableValue)
	{
		case A_COLLECT_VAL:
			getACollectBitmap(collectableBitmap);
			break;
		case B_COLLECT_VAL:
			getBCollectBitmap(collectableBitmap);
			break;
		case C_COLLECT_VAL:
			getCCollectBitmap(collectableBitmap);
			break;
		default:
			memset(collectableBitmap, 0, UINT32_BYTES * COLLECTABLE_HEIGHT);
	}

	plot_rast32(base, cell->x, y, COLLECTABLE_HEIGHT, collectableBitmap,
				FALSE, FALSE);
}

void renderHazards(UINT32* base, const Row* const row)
{
	const Hazard *hazard;

	int index;

	for (index = 0; index < row->hazardCount; index++)
	{
		hazard = &row->hazards[index];
		switch(hazard->hazardType)
		{
			case CAR_HAZ:
				renderCar(base, hazard->x, row->y, hazard->orientation);
				break;
			case FEATHERS_HAZ:
				renderFeathers(base, hazard->x, row->y, hazard->orientation);
				break;
			case TRAIN_HAZ:
				renderTrain(base, hazard->x, row->y);
				break;
			case NO_HAZ:
				break;
		}
	}
}

/**
 * @brief Renders a car at the given x and y position in the area of memory
 * pointed to by base.
 * @details Nothing will be rendered if the orientation is not horizontal.
 * 
 * @param base The location in memory to plot at.
 * @param x The x pixel location (starting at zero) to start rendering the car.
 * @param y The y pixel location (starting at zero) to start rendering the car.
 * @param orientation The horizontal orientation of the car.
 */
void renderCar(UINT32 *base, int x, int y, Direction orientation)
{
	UINT32 carBitmap[CAR_HEIGHT];

	clrPlayAreaSect(base, 1, x, CAR_LEN, y + CAR_Y_OFFSET, CAR_SMALLEST_HEIGHT);

	if (getCarBitmap(orientation, carBitmap) != NULL)
	{
		plot_rast32(base, x, y, CAR_HEIGHT, carBitmap, FALSE, FALSE);
	}
}

/**
 * @brief Renders a Mr. Feathers at the given x and y position in the area of
 * memory pointed to by base.
 * @details Nothing will be rendered if the orientation is not horizontal.
 * 
 * @param base The location in memory to plot at.
 * @param x The x pixel location (starting at zero) to start rendering
 * Mr. Feathers.
 * @param y The y pixel location (starting at zero) to start rendering
 * Mr. Feathers.
 * @param orientation The horizontal orientation of Mr. Feathers.
 */
void renderFeathers(UINT32 *base, int x, int y, Direction orientation)
{
	UINT32 feathersBitmap[FEATHERS_HEIGHT];

	if (getFeathersBitmap(orientation, feathersBitmap) != NULL)
	{
		plot_rast32(base, x, y, FEATHERS_HEIGHT, feathersBitmap, FALSE, FALSE);
	}
}

/**
 * @brief Renders a train at the given x and y position in the area of memory
 * pointed to by base.
 * 
 * @param base The location in memory to plot at.
 * @param x The x pixel location (starting at zero) to start rendering the
 * train.
 * @param y The y pixel location (starting at zero) to start rendering the
 * train.
 */
void renderTrain(UINT32 *base, int x, int y)
{
	UINT32 trainBitmap[TRAIN_HEIGHT];

	clrPlayAreaSect(base, 1, x + TRAIN_X_OFFSET, TRAIN_LEN, y + TRAIN_Y_OFFSET,
					TRAIN_SMALLEST_HEIGHT);

	for(; getTrainBitmap(trainBitmap) != NULL; x += CELL_LEN)
	{
		if (x <= MAX_CELL_X && x >= MIN_CELL_X)
		{
			plot_rast32(base, x, y, TRAIN_HEIGHT, trainBitmap, FALSE, FALSE);
		}
	}
}

void renderPlayers(UINT32* base, const World* const world)
{
	renderMainPlayer(base, &world->mainPlayer);
	renderScore((UINT16 *)base, &world->mainPlayer.score);
	renderLives((UINT16 *)base, &world->mainPlayer.lives);

	if (world->numPlayers == 2)
	{
		renderScore((UINT16 *)base, &world->otherPlayer.score);
		renderLives((UINT16 *)base, &world->otherPlayer.lives);
	}
}

void renderMainPlayer(UINT32* base, const Player* const player)
{
	UINT32 playerAlpha[PLAYER_HEIGHT];
	UINT32 playerBitmap[PLAYER_HEIGHT];

	if (getPlayerAlpha(player->orientation, playerAlpha) == NULL ||
		getPlayerBitmap(player->orientation, playerBitmap) == NULL)
	{
		memset(playerAlpha, 0, UINT32_BYTES * PLAYER_HEIGHT);
		memset(playerBitmap, 0, UINT32_BYTES * PLAYER_HEIGHT);
	}

	plot_alpha(base, player->x, player->y, PLAYER_HEIGHT, playerAlpha);
	plot_rast32(base, player->x, player->y, PLAYER_HEIGHT, playerBitmap, FALSE,
				FALSE);
}

void renderLabel(UINT16* base, const Label* const label, BOOL blackScreen)
{
	const UINT16 *currFont16Char;

	int index;
	int x;

	for (index = 0, x = 0; label->text[index] != '\0'; 
		 index++, x += LABEL_FONT_WIDTH)
	{
		currFont16Char = getFont16Char(label->text[index], NULL);
		plot_rast16(base, label->x + x, label->y, LABEL_FONT_HEIGHT,
					currFont16Char, TRUE, blackScreen);
	}
}

/**
 * @brief Renders a InfoBar to the screen.
 * @details Every character stored in the infoBar are rendered as 16x16
 * character sprites. Each string stored within the object is horizontally
 * centered on the screen at the object's provided y pixel position.
 * 
 * @param base The location in memory to plot at.
 * @param infoBar The infoBar that is to be rendered to the screen.
 * @param blackScrn Indicates whether the InfoBar will be rendered on a black
 * or white area.
 */
void renderInfoBar(UINT16* base, InfoBar* const infoBar, BOOL blackScrn)
{
	const int INFO_BAR_LINES = infoBar->numLabels *
							   (FONT16_HEIGHT + infoBar->spacingBetweenLabels) -
							   infoBar->spacingBetweenLabels;
	int counter;
	int index;

	if (infoBar->needsUpdate)
	{
		if (blackScrn)
		{
			for (counter = infoBar->y; counter < infoBar->y + INFO_BAR_LINES;
				counter++)
			{
				hline((UINT32 *)base, 0, SCRN_MAX_X, counter);
			}
		}
		else
		{
			clr_area((UINT32 *)base, 0, SCRN_LEN, infoBar->y, INFO_BAR_LINES);
		}

		for (index = 0; index < infoBar->numLabels; index++)
		{
			renderLabel(base, &infoBar->labels[index], blackScrn);
		}

		infoBar->needsUpdate = FALSE;
	}
}

void renderScore(UINT16* base, Score* const score)
{
	UINT32 value = score->value;
	int index = MAX_NUM_DIGITS_IN_SCORE - 1;
	int digits[MAX_NUM_DIGITS_IN_SCORE];
	int x;

	if (!score->labelRendered)
	{
		renderLabel((UINT16 *)base, &score->label, TRUE);
		score->labelRendered = TRUE;
	}

	do
	{
		digits[index--] = value % 10ul;
		value /= 10;
	} while (value != 0);

	for(x = 0, index += 1; index < MAX_NUM_DIGITS_IN_SCORE;
		index++, x += LABEL_FONT_WIDTH)
	{
		plot_rast16(base, score->x + x, score->y, LABEL_FONT_HEIGHT,
					getFont16Digit(digits[index], NULL), TRUE, TRUE);
	}
}

void renderLives(UINT16* base, Lives* const lives)
{
	if (!lives->labelRendered)
	{
		renderLabel((UINT16 *)base, &lives->label, TRUE);
		lives->labelRendered = TRUE;
	}
	plot_rast16(base, lives->x, lives->y, LABEL_FONT_HEIGHT,
				getFont16Digit(lives->value, NULL), TRUE, TRUE);
}

/**
 * @brief Renders a button to the screen.
 * 
 * @param base The location in memory to plot at.
 * @param button The Button that is to be rendered to the screen.
 * @param blackScreen When set to true indicates that button is being rendered 
 * on top of a black background.
 */
void renderButton(UINT32* base, Button* button, BOOL blackScreen)
{
	const int BORDER_WIDTH  = 3;
	const int BORDER_HEIGHT = 3;

	if (blackScreen)
	{
		if (button->selected == TRUE)
		{
			clr_area(base, button->x, button->width, button->y, button->height);
			rect_area(base, button->x + BORDER_WIDTH,
					  button->width - (BORDER_WIDTH * 2),
					  button->y + BORDER_HEIGHT,
					  button->height - (BORDER_HEIGHT * 2));
			renderLabel((UINT16 *)base, &button->label, blackScreen);
		}
		else
		{
			clr_area(base, button->x, button->width, button->y, button->height);
			renderLabel((UINT16 *)base, &button->label, !blackScreen);
		}
	}
	else
	{
		if (button->selected == TRUE)
		{
			rect_area(base, button->x, button->width, button->y, button->height);
			clr_area(base, button->x + BORDER_WIDTH,
					 button->width - (BORDER_WIDTH * 2),
					 button->y + BORDER_HEIGHT,
					 button->height - (BORDER_HEIGHT * 2));
			renderLabel((UINT16 *)base, &button->label, blackScreen);
		}
		else
		{
			rect_area(base, button->x, button->width, button->y, button->height);	
			renderLabel((UINT16 *)base, &button->label, !blackScreen);
		}
	}
}

void renderTitle(UINT32* base, int x, int y)
{
	UINT32 titleBitmap[TITLE_HEIGHT];

	for (; getTitleBitmap(titleBitmap) != NULL; x += TITLE_PART_LEN)
	{
		plot_rast32(base, x, y, TITLE_HEIGHT, titleBitmap, TRUE, FALSE);
	}
}

void renderGameOver(UINT32* base, int x, int y)
{
	UINT32 goverBitmap[GAME_OVER_HEIGHT];

	for (; getGameOverBitmap(goverBitmap) != NULL; x += GAME_OVER_PART_LEN)
	{
		plot_rast32(base, x, y, GAME_OVER_HEIGHT, goverBitmap, FALSE, TRUE);
	}
}

void renderCursor(UINT16* base, int x, int y)
{
	UINT16 mouseCursor[CURSOR_HEIGHT];

	if (getMouseCursor(mouseCursor) != NULL)
	{
		plot_rast16(base, x, y, CURSOR_HEIGHT, mouseCursor, FALSE, TRUE);
	}
}

void renderMenu(UINT32* base, Menu* menu)
{
	int index;

	if (!menu->borderRendered)
	{
		if (menu->blackScreen)
		{
			fill_scrn(base);
			clr_area(base, 0, menu->borderWidth, 0, menu->borderHeight);
		}
		else
		{
			fill_scrn(base);
			clr_area(base, menu->borderWidth, SCRN_LEN - menu->borderWidth * 2,
					menu->borderHeight, SCRN_HEIGHT - menu->borderHeight * 2);
		}

		menu->borderRendered = TRUE;
	}

	if (menu->buttonSel == -1 && menu->oldButtonSel == -1)
	{
		for (index = 0; index < menu->buttonFillLevel; index++)
		{
			renderButton(base, &menu->buttons[index], menu->blackScreen);
		}
	}
	else if (menu->buttonSel != menu->oldButtonSel)
	{
		if (menu->buttonSel != -1)
		{
			renderButton(base, &menu->buttons[menu->buttonSel],
						 menu->blackScreen);
		}

		if (menu->oldButtonSel != -1)
		{
			renderButton(base, &menu->buttons[menu->oldButtonSel],
						 menu->blackScreen);
		}
	}

	for (index = 0; index < menu->infobarFillLevel; index++)
	{
		/*
		InfoBar should be distinct from rest of menu. Hence, why InfoBar will be
		rendered with a black background when the rest of the menu is white and
		vice-versa.
		*/
		renderInfoBar((UINT16 *)base, &menu->infoBars[index],
					  !menu->blackScreen);
	}
}

/**
 * @brief Clears a rectangular area within the bounds of the play area.
 * @details The rectangular area's top-left corner will be defined by the given
 * x and y pixel coordinates. x and y may intersect the left and top borders
 * respectively, in which case, an area will be cleared as long as the length
 * and height are big enough. The length and height cannot be less than zero.
 * However, the length and width can be bigger than the length and height of the
 * play area. In the former case, the entire length of the play area will be
 * cleared, while in the latter case, the entire height of the play area will be
 * cleared. If both exceed the play area size, then the entire play area will be
 * cleared.
 * 
 * @param base The location in memory to plot at.
 * @param numPlayers The number of players in the world.
 * @param x The left-most column to start clearing the rectangular area (in
 * pixels starting at zero).
 * @param length The number of rows that should make up the rectangular area.
 * Must be one or greater.
 * @param y The top-most row to start clearing the rectangular area (in pixels
 * starting at zero).
 * @param height The number of columns that should make up the rectangular area.
 * Must be one or greater.
 */
void clrPlayAreaSect(UINT32 *base, int numPlayers, int x, int length,
					 int y, int height)
{
	const int CUR_BORDER_HEIGHT = getTopBorderHeight(numPlayers);
	const int FINAL_X = x + length - 1;
	const int FINAL_Y = y + height - 1;
	const int PLAY_AREA_LEN = RIGHT_BORDER - LEFT_BORDER + 1;
	const int PLAY_AREA_HEIGHT = BOTTOM_BORDER - CUR_BORDER_HEIGHT;

	if (x < RIGHT_BORDER && y < BOTTOM_BORDER && length > 0 && height > 0)
	{
		if (x < SIDE_BORDER_WIDTH)
		{
			if (x < 0)
			{
				length -= SIDE_BORDER_WIDTH + abs(x);
			}
			else
			{
				length -= SIDE_BORDER_WIDTH - x;
			}
			x = SIDE_BORDER_WIDTH;
		}

		if (FINAL_X >= RIGHT_BORDER)
		{
			length -= FINAL_X - RIGHT_BORDER + 1;
		}

		if (y < CUR_BORDER_HEIGHT)
		{
			if (y < 0)
			{
				height -= CUR_BORDER_HEIGHT + abs(y);
			}
			else
			{
				height -= CUR_BORDER_HEIGHT - y;
			}
			y = CUR_BORDER_HEIGHT;
		}

		if (FINAL_Y >= BOTTOM_BORDER)
		{
			height -= FINAL_Y - BOTTOM_BORDER + 1;
		}

		if (length > PLAY_AREA_LEN)
		{
			length = PLAY_AREA_LEN;
		}

		if (height > PLAY_AREA_HEIGHT)
		{
			height = PLAY_AREA_HEIGHT;
		}

		clr_area(base, x, length, y, height);
	}
}