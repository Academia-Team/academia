/**
 * @file model.h
 * @author Academia Team
 * @brief Contains functions to handle all game world model data.
 * 
 * @copyright Copyright Academia Team 2023
 */

#ifndef MODEL_H
#define MODEL_H

#include "bool.h"
#include "types.h"

/**
 * @brief The last x pixel coordinate occupied by the left border. 
 */
#define LEFT_BORDER 15

/**
 * @brief The first x pixel coordinate occupied by the right border.
 */
#define RIGHT_BORDER 624

/**
 * @brief The first y pixel coordinate occupied by the bottom border.
 */
#define BOTTOM_BORDER 384

/**
 * @brief The height of the bottom border.
 */
#define BOTTOM_BORDER_HEIGHT 16

/**
 * @brief The width of the side borders.
 */
#define SIDE_BORDER_WIDTH 16

/**
 * @brief The height of the top border containing the scores and lives (in
 * pixels for a single player game).
 */
#define TOP_BORDER_HEIGHT_1P 32

/**
 * @brief The height of the top border containing the scores and lives (in
 * pixels for a two player game).
 * 
 */
#define TOP_BORDER_HEIGHT_2P 64

/**
 * @brief The maximum number of rows that can exist in the world.
 */
#define MAX_ROWS 11

/**
 * @brief The maximum number of cells that can exist in the world.
 */
#define MAX_CELLS 19

#define MIN_CELL_X 16
#define MAX_CELL_X 592

/**
 * @brief The largest valid index in an array of cells. 
 */
#define MAX_CELLS_INDEX 18

#define MAX_POSSIBLE_SCORE 4294967200UL

#define ROW_HEIGHT 32

#define MAX_ROW_Y 352

#define CELL_LEN    32
#define CELL_HEIGHT 32

#define NUM_SAFE_ROWS 3

#define MAX_CARS 5
#define MAX_TRAINS 2
#define MAX_FEATHERS 2
#define MAX_A_COLLECTABLES 1
#define MAX_B_COLLECTABLES 2
#define MAX_C_COLLECTABLES 3
#define MAX_COLLECTABLES_IN_ROW 6
#define MAX_HAZARD_IN_ROW 5
#define MAX_HEDGES 3
#define MAX_SPIKES 3

#define PLAYER_START_X 304
#define PLAYER_START_Y 288

#define SCORE_START_X_2P 128
#define SCORE_START_X_1P 16
#define SCORE_LABEL_X SCORE_START_X
#define SCORE_TEXT_X  240

#define SCORE_START_Y_1P 8
#define SCORE_LABEL_Y_1P (SCORE_START_Y_1P + 1)
#define SCORE_TEXT_Y_1P  SCORE_START_Y_1P

#define SCORE_START_Y_2P 39
#define SCORE_LABEL_Y_2P (SCORE_START_Y_2P + 1)
#define SCORE_TEXT_Y_2P  SCORE_START_Y_2P

/**
 * @brief The number of seconds the player is immune after colliding with a
 * hazard.
 */
#define SECONDS_OF_IMMUNITY 2

#define LIVES_START_X 495
#define LIVES_LABEL_X LIVES_START_X
#define LIVES_TEXT_X 607

#define LIVES_START_Y_1P 8
#define LIVES_LABEL_Y_1P (SCORE_START_Y_1P + 1)
#define LIVES_TEXT_Y_1P  SCORE_START_Y_1P

#define LIVES_START_Y_2P 39
#define LIVES_LABEL_Y_2P (SCORE_START_Y_2P + 1)
#define LIVES_TEXT_Y_2P  SCORE_START_Y_2P

#define PLAYER_ROW_ADV_SCORE 100

/**
 * @brief Distance between the start Score label and the text itself.
 */
#define SCORE_X_TEXT_DIST 112

/**
 * @brief Distance between the start Lives label and the text itself.
 */
#define LIVES_X_TEXT_DIST 112

/**
 * @brief The y coordinate of a player such that a world shift will happen if
 * the player attempts to move forwards.
 */
#define WSHIFT_Y_BOUNDARY 288

/**
 * @brief The maximum number of characters that can be in a label.
 */
#define MAX_LABEL_LEN 20


#define MAX_OBSTACLE_IN_ROW 6

#define START_LIVES 3
#define NUM_ROW_TYPES 3
#define NUM_CELL_TYPES 5

/**
 * @brief The highest value constant corresponding to a cell type that can
 * constitute a row.
 */
#define MAX_ROW_CELL_TYPE TRACK_CELL

#define MIN_VIS_X_CAR MIN_CELL_X
#define MIN_VIS_X_FEATHERS MIN_CELL_X
#define MIN_VIS_X_TRAIN -48

typedef enum
{
	GRASS_CELL = 0,
	ROAD_CELL  = 1,
	TRACK_CELL = 2,
	SPIKE_CELL = 3,
	HEDGE_CELL = 4
} CellType;

typedef enum
{
	NO_COLLECT = 0,
	A_COLLECT_VAL = 500,
	B_COLLECT_VAL =  200,
	C_COLLECT_VAL = 100
} CollectVal;

typedef enum
{
	NO_HAZ = 0,
	FEATHERS_HAZ = 1,
	TRAIN_HAZ = 2,
	CAR_HAZ = 3
} HazType;

typedef enum
{
	UP     =  2,
	DOWN   = -2,
	NO_DIR =  0,
	RIGHT  =  1,
	LEFT   = -1
} Direction;

typedef enum
{
	NORTH     =  2,
	SOUTH     = -2,
	SYMMETRIC =  0,
	EAST      =  1,
	WEST      = -1
} Orientation;

typedef char LabelStr[MAX_LABEL_LEN + 1];

typedef struct
{
	int x;
	int y;
	LabelStr text;
} Label;

typedef struct
{
	int    x;
	int    y;
	Label  label;
	UINT32 value;
} Score;

typedef struct
{
	int x;
	int y;
	Label label;
	int value;
} Lives;

typedef struct
{
	int x;
	int y;
	int height;
	int width;
	Label label;
	BOOL selected;
} Button;

typedef struct
{
	int x;
	HazType hazardType;
	Orientation orientation;
} Hazard;

typedef struct
{
	int        x;
	CellType   cellType;
	CollectVal collectableValue;
} Cell;

typedef struct
{
	int       y;
	Direction horzDirection;
	int       hazardCount;
	int       hedgeCount;
	int       spikeCount;
	CellType  cellType;
	Cell      cells[MAX_CELLS];
	Hazard    hazards[MAX_HAZARD_IN_ROW];
} Row;

typedef struct
{
	int x;
	int y;
	Orientation orientation;

	int destX;
	int destY;

	Lives lives;
	Score score;

	BOOL immune;
	BOOL alive;
} Player;

typedef struct
{
	Lives lives;
	Score score;
	BOOL  alive;
} CorePlayer;

typedef struct
{
	int  usableRows;
	Row  rows[MAX_ROWS];
	int  top;
	int  bottom;
	int  numWorldShifts;
	BOOL shiftWorld;
	BOOL copyCells;
	BOOL renderCells;

	int aCount;
	int bCount;
	int cCount;

	Player     mainPlayer;
	CorePlayer otherPlayer;
	int        numPlayers;
} World;

/**
 * @brief Gets the height of the top border of the screen (in pixels).
 * @param numPlayers The number of players who are playing a game.
 * @return The integral height of the upper border of the screen.
 */
#define getTopBorderHeight(numPlayers) \
	(numPlayers == 1 ? TOP_BORDER_HEIGHT_1P : TOP_BORDER_HEIGHT_2P)

/**
 * @brief Places the coordinates of the label into the provided x and y
 * variables.
 * @param label The label object to get the coordinates of.
 * @param x The variable which will hold the x coordinate of the label (in
 * pixels).
 * @param y The variable which will hold the y coordinate of the label (in
 * pixels).
 */
#define getLabelPos(label, x, y) \
	x = (label).x; \
	y = (Label).y

/**
 * @brief Sets the coordinates of a label using the provided x and y
 * variables.
 * @param label The Label object to set.
 * @param x The x coordinate to use with the label (in pixels).
 * @param y The y coordinate to use with the label (in pixels).
 */
#define setLabelPos(label, x, y) \
	(label).x = x; \
	(label).y = y

/**
 * @brief Returns the string from the given label.
 * @param The Label object to get the string from.
 * @return The text held by the label.
 */
#define getLabelString(label) \
	(label).text

/**
 * @brief Determines whether a given player is alive or not.
 * @param playerObj A superset of a CorePlayer object to check.
 * @return A BOOL of TRUE if the given player is alive; false otherwise.
 */
#define isPlayerAlive(playerObj) \
	(playerObj).alive

/**
 * @brief Determines whether a player is currently moving or not.
 * @param worldObj The World which contains the player.
 * @param playerObj The Player object which may be moving.
 * @return A BOOL of TRUE if the given player is moving; false otherwise.
 */
#define isPlayerMoving(worldObj, playerObj) \
	((playerObj).x != (playerObj).destX || \
	(playerObj).y != (playerObj).destY  || \
	(worldObj).shiftWorld)

/**
 * @brief Toggles immunity for a given Player object.
 * @param playerObj The Player object to toggle immunity for.
 */
#define toggleImmunity(playerObj) \
	(playerObj).immune = !((playerObj).immune)

/**
 * @brief Generates an integral random number between 0 and rangeMax, inclusive.
 * 
 * @param rangeMax The max limit on the random number generator.
 * @return An integral number between 0 and rangeMax, inclusive.
 */
int random(int rangeMax);

/**
 * @brief Initializes a CorePlayer object.
 * 
 * @param player A pointer to the CorePlayer object to be initialized.
 * @param numPlayers The amount of players in the game.
 */
void initCorePlayer(CorePlayer* player, int numPlayers);

/**
 * @brief Initializes a Player object.
 * 
 * @param player A pointer to the Player object to be initialized.
 * @param numPlayers The amount of players in the game.
 */
void initPlayer(Player* player, int numPlayers);

/**
 * @brief Removes a life from the given player and sets immunity.
 * @details If the player has lost all their lives, they will be marked
 * as being dead.
 * 
 * @param player A pointer to the Player object which will lose a life.
 */
void lostLife (Player* player);

/**
 * @brief Initializes a World object.
 * @details The way the World is initialized depends on how many players will be
 * used in the world.
 * 
 * Currently, only one or two players are supported. Any number of player that
 * are given outside the supported range will result in nothing being
 * initialized.
 * 
 * @param world The World object to be initialized.
 * @param numPlayers The number of players that will exist in the world.
 */
void initWorld (World* world, int numPlayers);

/**
 * @brief Initializes a Row with randomly generated values.
 * @details The row direction and row type will be randomly selected. Obstacles,
 * hazards, and collectables will also be generated depending on probability.
 * Row type will be decided between grass, road, and track.
 * 
 * @param world The world where the Row came from.
 * @param row The Row to initialize.
 * @param rowY The y coordinate for the Row.
 */
void initRow(World* world, Row* row, int rowY);

/**
 * @brief Initializes a cell with the given cellType and x coordinate.
 * @details Every cell has a random chance of containing a collectable.
 * 
 * @param cell The cell to initialize.
 * @param x The x coordinate for the cell.
 * @param cellType The type of cell to set.
 */
void initCell(Cell* cell, int x, CellType cellType);

/**
 * @brief Adds obstacles to a newly created row.
 * @details While in theory, obstacles could be placed for any type row, in
 * practice, only rows made up of grass tiles get obstacles. Obstacles include
 * both hedges and spikes.
 * 
 * @param row The row to add obstacles to.
 */
void initObstacle(Row* row);

/**
 * @brief Adds collectables to a newly created row.
 * @details Whether a collectable is added or not depends on probability and
 * how many collectables currently exist anywhere in the world.
 * 
 * @param world The World containing the Row.
 * @param row The Row to add collectables to.
 */
void initCollectable(World* world, Row* row);

/**
 * @brief Randomly generates hazards for a new row.
 * 
 * @param row The row for which it will randomly generate hazards for.
 */
void initHazard(Row* row);

/**
 * @brief Initializes the number of lives.
 * @param x The horizontal position (starting at zero pixels) where the number
 * of lives will be displayed.
 * @param y The vertical position (starting at zero pixels) where the number of
 * lives will be displayed.
 * @param lifeBox The Lives object which will be initialized.
 */
void initLives (int x, int y, Lives* lifeBox);

/**
 * @brief Initializes the score.
 * @param x The horizontal position (starting at zero pixels) where the score
 * will be displayed.
 * @param y The vertical position (starting at zero pixels) where the score will
 * be displayed.
 * @param scoreBox The Score object which will be initialized.
 */
void initScore (int x, int y, Score* scoreBox);

/**
 * @brief Initializes a label with the given coordinates and string.
 * 
 * @param label A pointer to the Label object to initialize.
 * @param x The x coordinate of the label (in pixels).
 * @param y The y coordinate of the label (in pixels).
 * @param text The text that should be a part of the label.
 */
void initLabel(Label* label, int x, int y, LabelStr text);

/**
 * @brief Increments the score by a given amount.
 * @param value The value that is added to the score.
 * @param scoreBox The Score object which will have its value incremented.
 */
void updateScore (UINT32 value, Score* scoreBox);

/**
 * @brief Returns true if a hazard can theoretically be placed based off of
 * probability.
 * 
 * @param hazard The hazard to run the random number generator for. If it is not
 * a valid hazard, it will return FALSE.
 * @return A boolean value that is TRUE when a hazard can be placed and FALSE
 * otherwise.
 */
BOOL probPlaceHazard(HazType hazard);

/**
 * @brief Prepares a given row for use by setting it to default and provided
 * values.
 * 
 * @param row The row to prepare.
 * @param rowY The y coordinate of the row.
 * @param rowType The type of cells the row should contain.
 * @param dir The horizontal direction that all hazards should go on the row.
 * Will default to RIGHT if no valid direction is given.
 */
void prepRow(Row* row, int rowY, CellType rowType, Direction dir);

/**
 * @brief Removes a life from the given player and sets immunity.
 * @details If the player has lost all their lives, they will be marked
 * as being dead.
 * 
 * @param player A pointer to the CorePlayer object which will lose a life.
 */
void lostCoreLife (CorePlayer* player);

/**
 * @brief Get the indicies of an object in the given x,y position.
 * @details The values calculated compensate for the space taken up by the
 * border surrounding the screen.
 * 
 * @param world The World object where the object exists.
 * @param row The desired row. Returned by reference.
 * @param column The desired column. Returned by reference.
 * @param x The horizontal coordinate of the object on the screen.
 * @param y The vertical coordinate of the object on the screen.
 */
void coordToIndex(const World* const world, int* row, int* column, int x, int y);

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
initButton(Button* button, int x, int y, int height, int width, LabelStr text);

#endif
