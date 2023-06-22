/**
 * @file renderer.c
 * @author Academia Team
 * @brief Contains functions to render the entire play area of the game. 
 * @details The play area includes the border, score box, lives box, and the
 * game world with all its inhabitants and cells.
 * 
 * @copyright Copyright Academia Team 2023
 */

#include <stdlib.h>

#include "bitmaps.h"
#include "bool.h"
#include "font16.h"
#include "model.h"
#include "raster.h"
#include "renderer.h"
#include "types.h"

void clrPlayAreaSect(UINT32 *base, int numPlayers, int x, int length,
					 int y, int height);

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
	renderLabel((UINT16 *)base, &world->mainPlayer.score.label, TRUE);
	renderLabel((UINT16 *)base, &world->mainPlayer.lives.label, TRUE);

	if (world->numPlayers == 2)
	{
		initLabel(&youLabel, 16, 8,"YOU:");
		initLabel(&otherLabel, 16, 40,"OTHER:");
		renderLabel((UINT16 *)base, &youLabel, TRUE);
		renderLabel((UINT16 *)base, &otherLabel, TRUE);
		renderLabel((UINT16 *)base, &world->otherPlayer.score.label, TRUE);
		renderLabel((UINT16 *)base, &world->otherPlayer.lives.label, TRUE);
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
	plot_rast32(base, cell->x, y, CELL_HEIGHT, cellBitmap[cell->cellType], TRUE,
				FALSE);
	
	switch(cell->collectableValue)
	{
		case A_COLLECT_VAL:
			plot_rast32(base, cell->x, y, COLLECTABLE_HEIGHT,
						collectableBitmap[0], FALSE, FALSE);
			break;
		case B_COLLECT_VAL:
			plot_rast32(base, cell->x, y, COLLECTABLE_HEIGHT,
						collectableBitmap[1], FALSE, FALSE);
			break;
		case C_COLLECT_VAL:
			plot_rast32(base, cell->x, y, COLLECTABLE_HEIGHT,
						collectableBitmap[2], FALSE, FALSE);
			break;
	}
}

void renderHazards(UINT32* base, const Row* const row)
{
	int index;
	int trainPart;
	int trainX;

	for (index = 0; index < row->hazardCount; index++)
	{
		switch(row->hazards[index].hazardType)
		{
			case CAR_HAZ:
				clrPlayAreaSect(base, 1, row->hazards[index].x, CAR_LEN,
						 		row->y + CAR_Y_OFFSET, CAR_HEIGHT);
				
				plot_rast32
				(
					base, row->hazards[index].x, row->y, HAZARD_HEIGHT,
					carBitmap
					[
						(row->hazards[index].orientation == WEST ? 0 : 1)
					], FALSE, FALSE
				);
				break;
			case FEATHERS_HAZ:
				plot_rast32
				(
					base, row->hazards[index].x, row->y, HAZARD_HEIGHT,
					feathersBitmap
					[
						(row->hazards[index].orientation == WEST ? 0 : 1)
					], FALSE, FALSE
				);
				break;
			case TRAIN_HAZ:
				clrPlayAreaSect
				(
					base, 1, row->hazards[index].x + TRAIN_X_OFFSET,
					TRAIN_LEN, row->y + TRAIN_Y_OFFSET, TRAIN_HEIGHT
				);

				for
				(
					trainPart = 0, trainX = row->hazards[index].x;
					trainPart < NUM_TRAIN_PARTS;
					trainX += CELL_LEN, trainPart++
				)
				{
					if (trainX <= MAX_CELL_X && trainX >= MIN_CELL_X)
					{
						plot_rast32
						(
							base, trainX, row->y, HAZARD_HEIGHT,
							trainBitmap[trainPart], FALSE, FALSE
						);
					}
				}
				break;
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
	switch(player->orientation)
	{
		case NORTH:
			plot_alpha(base, player->x, player->y, PLAYER_HEIGHT, 
					   playerAlpha[0]);
			plot_rast32
			(
				base, player->x, player->y, PLAYER_HEIGHT, playerBitmap[0],
				FALSE, FALSE
			);
			break;
		case WEST:
			plot_alpha(base, player->x, player->y, PLAYER_HEIGHT, 
					   playerAlpha[1]);
			plot_rast32
			(
				base, player->x, player->y, PLAYER_HEIGHT, playerBitmap[1],
				FALSE, FALSE
			);
			break;
		case SOUTH:
			plot_alpha(base, player->x, player->y, PLAYER_HEIGHT, 
					   playerAlpha[0]);
			plot_rast32
			(
				base, player->x, player->y, PLAYER_HEIGHT, playerBitmap[2],
				FALSE, FALSE
			);
			break;
		case EAST:
			plot_alpha(base, player->x, player->y, PLAYER_HEIGHT, 
					   playerAlpha[2]);
			plot_rast32
			(
				base, player->x, player->y, PLAYER_HEIGHT, playerBitmap[3],
				FALSE, FALSE
			);
			break;
	}
}

void renderLabel(UINT16* base, const Label* const label, BOOL blackScreen)
{
	const int LABEL_HEIGHT = 16;
	const int LABEL_WIDTH = 16;

	int index;
	int x;
	int charToPrint = 0;

	for (index = 0, x = 0; label->text[index] != '\0'; 
		 index++, (x += LABEL_WIDTH))
	{
		charToPrint = getFont16PrintableChar(label->text[index]);
		plot_rast16(base, (label->x + x), label->y, LABEL_HEIGHT,
					&font16[charToPrint], TRUE, blackScreen);
	}
}

void renderInfoBar(UINT16* base, const InfoBar* const infoBar)
{
	int index;

	for (index = 0; index < infoBar->numLabels; index++)
	{
		renderLabel(base, &infoBar->labels[index], TRUE);
	}
}

void renderScore(UINT16* base, const Score* const score)
{
	const int LABEL_HEIGHT = 16;
	const int LABEL_WIDTH = 16;
	const int MAX_DIGIT_INDEX = 9;

	UINT32 value = score->value;
	int index = MAX_DIGIT_INDEX;
	int digits[10];
	int x;

	do
	{
		digits[index] = getFont16Digit(value % 10UL);
		value /= 10;
		index--;
	} while (value != 0);

	index++;
	for(x = 0; index <= MAX_DIGIT_INDEX; index++, (x += LABEL_WIDTH))
	{
		plot_rast16(base, (score->x + x), score->y, LABEL_HEIGHT,
					&font16[digits[index]], TRUE, TRUE);
	}
}

void renderLives(UINT16* base, const Lives* const lives)
{
	const int LABEL_HEIGHT = 16;

	int fontIndex = getFont16Digit(lives->value);
	
	plot_rast16(base, lives->x, lives->y, LABEL_HEIGHT,
				&font16[fontIndex], TRUE, TRUE);
}

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
	int index;

	for (index = 0; index < NUM_TITLE_PARTS; index++)
	{
		plot_rast32(base, x, y, TITLE_HEIGHT, titleBitmap[index], TRUE, FALSE);
		x += TITLE_PART_WIDTH;
	}
}

void renderGameOver(UINT32* base, int x, int y)
{
	int index;

	for (index = 0; index < NUM_GAME_OVER_PARTS; index++)
	{
		plot_rast32(base, x, y, GAME_OVER_HEIGHT, gameOverBitmap[index], FALSE,
					TRUE);
		x += GAME_OVER_PART_WIDTH;
	}
}

void renderCursor(UINT16* base, int x, int y)
{
	plot_rast16(base, x, y, CURSOR_HEIGHT, mouseCursor, FALSE, TRUE);
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