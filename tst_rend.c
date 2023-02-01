/**
 * @file tst_rend.c
 * @author Academia Team
 * @brief It is designed to test the functionality of all renderer
 * functions.
 * 
 * @copyright Copyright Academia Team 2023
 */

#include <limits.h>
#include <osbind.h>

#include "raster.h"
#include "renderer.h"
#include "test.h"

#define DEFAULT_NUM_LIVES 0
#define LOSE_ONE_LIFE 1
#define LOSE_TWO_LIVES 2
#define LOST_THREE_LIVES 3

#define DEFAULT_PLAYER_ORIENTATION SYMMETRIC
#define ORIENT_NORTH NORTH
#define ORIENT_WEST WEST
#define ORIENT_SOUTH SOUTH
#define ORIENT_EAST EAST

#define ONE_PLAYER 1
#define TWO_PLAYER 2

typedef enum
{
	BLACK_ON_WHITE_SCRN,
	WHITE_ON_BLACK_SCRN
} RenderOpts;

void testLabelRend(UINT16* base, RenderOpts color);
void testLivesRend(UINT16* base, int numLivesLost);
void testScoreRend(UINT16* base, UINT32 scoreVal);
void testPlayerRend(UINT32* base, Orientation orientation);
void testCellRend(UINT32* base, CellType cellType, CollectVal collectable);
void testRowRend(UINT32* base, CellType rowType);
void testHazardRend(UINT32* base, HazType hazard, Orientation horzOrient);
void quickCellRend(UINT32* base, int x, int y, CellType cellType,
				   CollectVal collectable);
void quickHazRend(UINT32* base, int x, int y, HazType hazard,
				  Orientation horzOrient);
void testHazOnCell(UINT32* base, HazType hazard, Orientation horzOrient,
				   CellType cellType, CollectVal collectable);
void testPlyrOnCell(UINT32* base, Orientation orientation, CellType cellType,
					CollectVal collectable);
void testWorldRend(UINT32* base, int numPlayers);
void testPlayAreaRend(UINT32* base, int numPlayers);

int main()
{
	UINT32* base32 = (UINT32 *)Physbase();
	UINT16* base16 = (UINT16 *)base32;

	off_curs();

	run_test(testLabelRend(base16, BLACK_ON_WHITE_SCRN));
	run_test(testLabelRend(base16, WHITE_ON_BLACK_SCRN));

	run_test(testLivesRend(base16, DEFAULT_NUM_LIVES));
	run_test(testLivesRend(base16, LOSE_ONE_LIFE));
	run_test(testLivesRend(base16, LOSE_TWO_LIVES));
	run_test(testLivesRend(base16, LOST_THREE_LIVES));

	run_test(testScoreRend(base16, 0));
	run_test(testScoreRend(base16, PLAYER_ROW_ADV_SCORE));
	run_test(testScoreRend(base16, C_COLLECT_VAL));
	run_test(testScoreRend(base16, B_COLLECT_VAL));
	run_test(testScoreRend(base16, A_COLLECT_VAL));
	run_test(testScoreRend(base16, INT_MAX));
	run_test(testScoreRend(base16, LONG_MAX));
	run_test(testScoreRend(base16, ULONG_MAX));

	run_test(testPlayerRend(base32, DEFAULT_PLAYER_ORIENTATION));
	run_test(testPlayerRend(base32, NORTH));
	run_test(testPlayerRend(base32, WEST));
	run_test(testPlayerRend(base32, SOUTH));
	run_test(testPlayerRend(base32, EAST));

	run_test(testCellRend(base32, GRASS_CELL, NO_COLLECT));
	run_test(testCellRend(base32, GRASS_CELL, A_COLLECT_VAL));
	run_test(testCellRend(base32, GRASS_CELL, B_COLLECT_VAL));
	run_test(testCellRend(base32, GRASS_CELL, C_COLLECT_VAL));

	run_test(testCellRend(base32, ROAD_CELL, NO_COLLECT));
	run_test(testCellRend(base32, ROAD_CELL, A_COLLECT_VAL));
	run_test(testCellRend(base32, ROAD_CELL, B_COLLECT_VAL));
	run_test(testCellRend(base32, ROAD_CELL, C_COLLECT_VAL));

	run_test(testCellRend(base32, TRACK_CELL, NO_COLLECT));
	run_test(testCellRend(base32, TRACK_CELL, A_COLLECT_VAL));
	run_test(testCellRend(base32, TRACK_CELL, B_COLLECT_VAL));
	run_test(testCellRend(base32, TRACK_CELL, C_COLLECT_VAL));

	run_test(testCellRend(base32, SPIKE_CELL, NO_COLLECT));
	run_test(testCellRend(base32, SPIKE_CELL, A_COLLECT_VAL));
	run_test(testCellRend(base32, SPIKE_CELL, B_COLLECT_VAL));
	run_test(testCellRend(base32, SPIKE_CELL, C_COLLECT_VAL));

	run_test(testCellRend(base32, HEDGE_CELL, NO_COLLECT));

	run_test(testRowRend(base32, GRASS_CELL));
	run_test(testRowRend(base32, ROAD_CELL));
	run_test(testRowRend(base32, TRACK_CELL));

	run_test(testHazardRend(base32, FEATHERS_HAZ, EAST));
	run_test(testHazardRend(base32, FEATHERS_HAZ, WEST));

	run_test(testHazardRend(base32, TRAIN_HAZ, EAST));
	run_test(testHazardRend(base32, TRAIN_HAZ, WEST));

	run_test(testHazardRend(base32, CAR_HAZ, EAST));
	run_test(testHazardRend(base32, CAR_HAZ, WEST));

	run_test(testHazOnCell(base32, FEATHERS_HAZ, EAST, GRASS_CELL, NO_COLLECT));
	run_test(testHazOnCell(base32, FEATHERS_HAZ, EAST, GRASS_CELL,
						   A_COLLECT_VAL));
	run_test(testHazOnCell(base32, FEATHERS_HAZ, EAST, GRASS_CELL,
						   B_COLLECT_VAL));
	run_test(testHazOnCell(base32, FEATHERS_HAZ, EAST, GRASS_CELL,
						   C_COLLECT_VAL));
	
	run_test(testHazOnCell(base32, FEATHERS_HAZ, WEST, GRASS_CELL, NO_COLLECT));
	run_test(testHazOnCell(base32, FEATHERS_HAZ, WEST, GRASS_CELL,
						   A_COLLECT_VAL));
	run_test(testHazOnCell(base32, FEATHERS_HAZ, WEST, GRASS_CELL,
						   B_COLLECT_VAL));
	run_test(testHazOnCell(base32, FEATHERS_HAZ, WEST, GRASS_CELL,
						   C_COLLECT_VAL));

	run_test(testHazOnCell(base32, TRAIN_HAZ, EAST, TRACK_CELL, NO_COLLECT));
	run_test(testHazOnCell(base32, TRAIN_HAZ, EAST, TRACK_CELL, A_COLLECT_VAL));
	run_test(testHazOnCell(base32, TRAIN_HAZ, EAST, TRACK_CELL, B_COLLECT_VAL));
	run_test(testHazOnCell(base32, TRAIN_HAZ, EAST, TRACK_CELL, C_COLLECT_VAL));
	
	run_test(testHazOnCell(base32, TRAIN_HAZ, WEST, TRACK_CELL, NO_COLLECT));
	run_test(testHazOnCell(base32, TRAIN_HAZ, WEST, TRACK_CELL, A_COLLECT_VAL));
	run_test(testHazOnCell(base32, TRAIN_HAZ, WEST, TRACK_CELL, B_COLLECT_VAL));
	run_test(testHazOnCell(base32, TRAIN_HAZ, WEST, TRACK_CELL, C_COLLECT_VAL));

	run_test(testHazOnCell(base32, CAR_HAZ, EAST, ROAD_CELL, NO_COLLECT));
	run_test(testHazOnCell(base32, CAR_HAZ, EAST, ROAD_CELL, A_COLLECT_VAL));
	run_test(testHazOnCell(base32, CAR_HAZ, EAST, ROAD_CELL, B_COLLECT_VAL));
	run_test(testHazOnCell(base32, CAR_HAZ, EAST, ROAD_CELL, C_COLLECT_VAL));
	
	run_test(testHazOnCell(base32, CAR_HAZ, WEST, ROAD_CELL, NO_COLLECT));
	run_test(testHazOnCell(base32, CAR_HAZ, WEST, ROAD_CELL, A_COLLECT_VAL));
	run_test(testHazOnCell(base32, CAR_HAZ, WEST, ROAD_CELL, B_COLLECT_VAL));
	run_test(testHazOnCell(base32, CAR_HAZ, WEST, ROAD_CELL, C_COLLECT_VAL));

	run_test(testPlyrOnCell(base32, DEFAULT_PLAYER_ORIENTATION, GRASS_CELL,
							NO_COLLECT));
	run_test(testPlyrOnCell(base32, DEFAULT_PLAYER_ORIENTATION, GRASS_CELL,
							A_COLLECT_VAL));
	run_test(testPlyrOnCell(base32, DEFAULT_PLAYER_ORIENTATION, GRASS_CELL,
							B_COLLECT_VAL));
	run_test(testPlyrOnCell(base32, DEFAULT_PLAYER_ORIENTATION, GRASS_CELL,
							C_COLLECT_VAL));

	run_test(testPlyrOnCell(base32, NORTH, GRASS_CELL, NO_COLLECT));
	run_test(testPlyrOnCell(base32, NORTH, GRASS_CELL, A_COLLECT_VAL));
	run_test(testPlyrOnCell(base32, NORTH, GRASS_CELL, B_COLLECT_VAL));
	run_test(testPlyrOnCell(base32, NORTH, GRASS_CELL, C_COLLECT_VAL));

	run_test(testPlyrOnCell(base32, WEST, GRASS_CELL, NO_COLLECT));
	run_test(testPlyrOnCell(base32, WEST, GRASS_CELL, A_COLLECT_VAL));
	run_test(testPlyrOnCell(base32, WEST, GRASS_CELL, B_COLLECT_VAL));
	run_test(testPlyrOnCell(base32, WEST, GRASS_CELL, C_COLLECT_VAL));

	run_test(testPlyrOnCell(base32, SOUTH, GRASS_CELL, NO_COLLECT));
	run_test(testPlyrOnCell(base32, SOUTH, GRASS_CELL, A_COLLECT_VAL));
	run_test(testPlyrOnCell(base32, SOUTH, GRASS_CELL, B_COLLECT_VAL));
	run_test(testPlyrOnCell(base32, SOUTH, GRASS_CELL, C_COLLECT_VAL));

	run_test(testPlyrOnCell(base32, EAST, GRASS_CELL, NO_COLLECT));
	run_test(testPlyrOnCell(base32, EAST, GRASS_CELL, A_COLLECT_VAL));
	run_test(testPlyrOnCell(base32, EAST, GRASS_CELL, B_COLLECT_VAL));
	run_test(testPlyrOnCell(base32, EAST, GRASS_CELL, C_COLLECT_VAL));

	run_test(testWorldRend(base32, ONE_PLAYER));
	run_test(testWorldRend(base32, TWO_PLAYER));

	run_test(testPlayAreaRend(base32, ONE_PLAYER));
	run_test(testPlayAreaRend(base32, TWO_PLAYER));

	on_curs();
	return 0;
}

/**
 * @brief Renders the label "LABEL" at the middle of the screen on the selected 
 * color of the screen. 1 = Black screen therefore white text will be printed, 
 * while 0 = white screen therefore black text will be printed.
 * 
 * @param base The location in memory to plot at.
 * @param color The color of the screen that is being printed to. 
 */
void testLabelRend(UINT16* base, RenderOpts color)
{
	Label label;
	initLabel(&label, (SCRN_LEN / 2) - 41, (SCRN_HEIGHT / 2) - 41, "LABEL");

	if (color == WHITE_ON_BLACK_SCRN)
	{
		fill_scrn((UINT32*) base);
		renderLabel(base, &label);
	}
	else
	{
		renderLabel(base, &label);
	}
	Cconin();
}

/**
 * @brief Renders the amount of lives at a position that is at the right-center
 * portion of the screen.
 * @details If numLivesLost is 0 then the player has all of their lives and max
 * lives will be rendered, if it is 1 then the lives will render max lives - 1,
 * etc.
 * 
 * @param base The location in memory to plot at.
 * @param numLivesLost The number of lost lives to print.
 */
void testLivesRend(UINT16* base, int numLivesLost)
{
	Lives lives;
	fill_scrn((UINT32*) base);
	initLives(495, 8, &lives);
	lives.value -= numLivesLost;

	renderLives(base, &lives);	
	Cconin();
}

/**
 * @brief Renders the Score at a position that is at the left-center portion of
 * the screen.
 * 
 * @param base The location in memory to plot at.
 * @param scoreVal The score that is to be rendered on screen.
 */
void testScoreRend(UINT16* base, UINT32 scoreVal)
{
	Score score;
	fill_scrn((UINT32*) base);
	initScore(16, 8, &score);
	updateScore(scoreVal, &score);

	renderScore(base, &score);
	Cconin();
}

/**
 * @brief Draws a Player at the pixel coordinates (304,288) with the given
 * orientation.
 * 
 * @param base The location in memory to plot at.
 * @param orientation The orientation to draw the Player in. Defaults to SOUTH
 * if an invalid orientation is given.
 */
void testPlayerRend(UINT32* base, Orientation orientation)
{
	Player tstPlayer;

	initPlayer(&tstPlayer, 1);

	if (orientation == NORTH || orientation == SOUTH ||
		orientation == EAST  || orientation == WEST)
	{
		tstPlayer.orientation = orientation;
	}

	renderMainPlayer(base, &tstPlayer);
	Cconin();
}

/**
 * @brief Renders a cell of given cellType with a given collectable in the
 * middle of the screen.
 * 
 * @param base The location in memory to plot at.
 * @param cellType The type of cell to render.
 * @param collectable The type of collectable to render.
 */
void testCellRend(UINT32* base, CellType cellType, CollectVal collectable)
{
	quickCellRend(base, RAST32_MID_VIS_X, SCRN_MID_Y, cellType, collectable);
	Cconin();
}

/**
 * @brief Render a row in the middle of the screen with the given rowType.
 * 
 * @param base The location in memory to plot at.
 * @param rowType The type of row to plot on screen.
 */
void testRowRend(UINT32* base, CellType rowType)
{
	Row tstRow;

	prepRow(&tstRow, SCRN_MID_Y, rowType, RIGHT);
	renderRow(base, &tstRow);
	Cconin();
}

/**
 * @brief Plots a hazard with the given orientation in the middle of the screen.
 * 
 * @param base The location in memory to plot at.
 * @param hazard The hazard to draw. Defaults to Mr. Feathers if an invalid
 * hazard is given.
 * @param horzOrient The orientation to draw the hazard in. Defaults to WEST
 * if an invalid orientation is given.
 */
void testHazardRend(UINT32* base, HazType hazard, Orientation horzOrient)
{
	quickHazRend(base, RAST32_MID_VIS_X, SCRN_MID_Y, hazard, horzOrient);
	Cconin();
}

/**
 * @brief Renders a cell at the given position with the given cellType and
 * collectable in the middle of the screen.
 * @note The word quick in its name refers to the ease the function can be
 * called, not about the actually speed of the function.
 * 
 * @param base The location in memory to plot at.
 * @param x The horizontal pixel position to place the cell at (starting at
 * zero).
 * @param y The vertical pixel position to place the cell at (starting at zero).
 * @param cellType The type of cell to render.
 * @param collectable The type of collectable to render.
 */
void quickCellRend(UINT32* base, int x, int y, CellType cellType,
				   CollectVal collectable)
{
	Cell tstCell;

	initCell(&tstCell, x, cellType);
	tstCell.collectableValue = collectable;

	renderCell(base, &tstCell, y);
}

/**
 * @brief Plots a hazard with the given orientation in the middle of the screen.
 * @note The word quick in its name refers to the ease the function can be
 * called, not about the actually speed of the function.
 * 
 * @param base The location in memory to plot at.
 * @param x The horizontal pixel position to place the cell at (starting at
 * zero).
 * @param y The vertical pixel position to place the cell at (starting at zero).
 * @param hazard The hazard to draw. Defaults to Mr. Feathers if an invalid
 * hazard is given.
 * @param horzOrient The orientation to draw the hazard in. Defaults to WEST
 * if an invalid orientation is given.
 */
void quickHazRend(UINT32* base, int x, int y, HazType hazard,
				  Orientation horzOrient)
{
	Row tstRow;

	prepRow(&tstRow, SCRN_MID_Y, GRASS_CELL, RIGHT);

	if (hazard == CAR_HAZ || hazard == FEATHERS_HAZ || hazard == TRAIN_HAZ)
	{
		tstRow.hazards[tstRow.hazardCount++].hazardType = hazard;
	}
	else
	{
		tstRow.hazards[tstRow.hazardCount++].hazardType = FEATHERS_HAZ;
	}

	if (horzOrient == NORTH || horzOrient == SOUTH || horzOrient == EAST ||
		horzOrient == WEST)
	{
		tstRow.hazards[0].orientation = horzOrient;
	}
	else
	{
		tstRow.hazards[0].orientation = WEST;
	}

	tstRow.hazards[0].x = RAST32_MID_VIS_X;

	renderHazards(base, &tstRow);
}

/**
 * @brief Plots a cell with a hazard in the middle of a white screen with the
 * given properties.
 * @details For the train, since it is longer, it plots three of the
 * cells instead.
 * 
 * @param base The location in memory to plot at.
 * @param hazard The hazard to draw. Defaults to Mr. Feathers if an invalid
 * hazard is given.
 * @param horzOrient The orientation to draw the hazard in. Defaults to WEST
 * if an invalid orientation is given.
 * @param cellType The type of cell to render.
 * @param collectable The type of collectable to render.
 */
void testHazOnCell(UINT32* base, HazType hazard, Orientation horzOrient,
				   CellType cellType, CollectVal collectable)
{
	clr_scrn(base);

	quickCellRend(base, RAST32_MID_VIS_X, SCRN_MID_Y, cellType, collectable);

	if (hazard == TRAIN_HAZ)
	{
		quickCellRend(base, RAST32_MID_VIS_X + CELL_LEN, SCRN_MID_Y, cellType,
					  collectable);
		quickCellRend(base, RAST32_MID_VIS_X + CELL_LEN * 2, SCRN_MID_Y,
					  cellType, collectable);
	}

	quickHazRend(base, RAST32_MID_VIS_X, SCRN_MID_Y, hazard, horzOrient);
	Cconin();
}

/**
 * @brief Plots a cell with a player in the middle of a white screen with the
 * given properties.
 * 
 * @param base The location in memory to plot at.
 * @param orientation The orientation to draw the player in. Defaults to SOUTH
 * if an invalid orientation is given.
 * @param cellType The type of cell to render.
 * @param collectable The type of collectable to render.
 */
void testPlyrOnCell(UINT32* base, Orientation orientation, CellType cellType,
					CollectVal collectable)
{
	Player tstPlayer;

	initPlayer(&tstPlayer, 1);
	clr_scrn(base);

	quickCellRend(base, RAST32_MID_VIS_X, SCRN_MID_Y, cellType, collectable);

	if (orientation == NORTH || orientation == SOUTH ||
		orientation == EAST  || orientation == WEST)
	{
		tstPlayer.orientation = orientation;
	}

	tstPlayer.x = RAST32_MID_VIS_X;
	tstPlayer.y = SCRN_MID_Y;

	renderMainPlayer(base, &tstPlayer);
	Cconin();
}

/**
 * @brief Renders the state of a test world without player or scores.
 * 
 * @param base The location in memory to plot at.
 * @param numPlayers The number of players in the world starting at 1.
 */
void testWorldRend(UINT32* base, int numPlayers)
{
	World tstWorld;

	initWorld(&tstWorld, numPlayers);
	renderWorld(base, &tstWorld);
	Cconin();
}

/**
 * @brief Renders the state of a test world with player and scores.
 * 
 * @param base The location of memory to plot at.
 * @param numPlayers The number of players in the world starting at 1.
 */
void testPlayAreaRend(UINT32* base, int numPlayers)
{
	World tstWorld;

	initWorld(&tstWorld, numPlayers);
	renderPlayArea(base, &tstWorld);
	Cconin();
}