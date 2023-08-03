/**
 * @file tst_mdl.c
 * @author Academia Team
 * @brief Contains functions and types aimed at testing the model.
 * 
 * @copyright Copyright Academia Team 2023
 */

#include <limits.h>
#include <stdio.h>

#include "events.h"
#include "ikbdcode.h"
#include "model.h"
#include "move.h"
#include "super.h"
#include "test.h"
#include "types.h"

#define MAX_CELL_NAME_LEN 20
typedef char CellName[MAX_CELL_NAME_LEN + 1];

#define MAX_DIR_NAME_LEN 20
typedef char DirName[MAX_DIR_NAME_LEN + 1];

#define MAX_HAZ_NAME_LEN 20
typedef char HazName[MAX_HAZ_NAME_LEN + 1];

#define MAX_ORIENT_NAME_LEN 10
typedef char OrientName[MAX_ORIENT_NAME_LEN + 1];

void testScoreBox();
void testLivesBox();
void testRowGen();
char* getCellTypeName(CellType cell, char cellName[]);
char* getDirName(Direction dir, char dirName[]);
char* getHazName(HazType hazard, char hazName[]);
void testWorldShift();
void outRowInfo(const Row* const row, int id, int index);
void testHazAdd();
void outHazInfo(const Hazard* const hazard);
void testPlayerMove();
void outObjInPos(const World* const world, int x, int y);
IKBD_Scancode getKeyBlocking();
char* getOrientName(Direction orient, char orientName[]);
void outCellInfo(const Cell* const cell, int id, int index);

int main()
{
	run_test(testScoreBox());
	run_test(testLivesBox());
	run_test(testRowGen());
	run_test(testWorldShift());
	run_test(testHazAdd());
	run_test(testPlayerMove());

	return 0;
}

/**
 * @brief Confirms the position and text displayed by a score box.
 */
void testScoreBox()
{
	Score scoreBox;

	initScore(0, 0, &scoreBox);

	printf
	(
		"Score Label \"%s\": (%i, %i)\n", scoreBox.label.text,
		scoreBox.label.x, scoreBox.label.y
	);

	printf
	(
		"Score Text \"%lu\": (%i, %i)\n", scoreBox.value,
		scoreBox.x, scoreBox.y
	);

	Cconin();

	updateScore(100, &scoreBox);
	putchar('\n');
	puts("After score increment by 100:");

	printf
	(
		"Score Label \"%s\": (%i, %i)\n", scoreBox.label.text,
		scoreBox.label.x, scoreBox.label.y
	);

	printf
	(
		"Score Text \"%lu\": (%i, %i)\n", scoreBox.value,
		scoreBox.x, scoreBox.y
	);

	printf("Current Score: %lu\n", scoreBox.value);
	Cconin();

	updateScore(500, &scoreBox);
	putchar('\n');
	puts("After score increment by 500:");

	printf
	(
		"Score Label \"%s\": (%i, %i)\n", scoreBox.label.text,
		scoreBox.label.x, scoreBox.label.y
	);

	printf
	(
		"Score Text \"%lu\": (%i, %i)\n", scoreBox.value,
		scoreBox.x, scoreBox.y
	);

	printf("Current Score: %lu\n", scoreBox.value);
	Cconin();

	updateScore(INT_MAX, &scoreBox);
	putchar('\n');
	printf("After score increment by %i:\n", INT_MAX);

	printf
	(
		"Score Label \"%s\": (%i, %i)\n", scoreBox.label.text,
		scoreBox.label.x, scoreBox.label.y
	);

	printf
	(
		"Score Text \"%lu\": (%i, %i)\n", scoreBox.value,
		scoreBox.x, scoreBox.y
	);
		
	printf("Current Score: %lu\n", scoreBox.value);
	Cconin();

	putchar('\n');
	puts("Confirming that the score can never have a carry error if updated.");
	putchar('\n');
	updateScore(ULONG_MAX, &scoreBox);

	if (scoreBox.value < ULONG_MAX)
	{
		puts("The test has failed.");
		printf("The score has a value of %lu.\n", scoreBox.value);
	}
	else
	{
		puts("The test has succeeded.");
		printf("The score has a value of %lu\n", scoreBox.value);
	}

	Cconin();
}

/**
 * @brief Confirms the position and text displayed by a lives box which is
 * connected to a Player.
 */
void testLivesBox()
{
	Player     tstPlayer;
	initPlayer(&tstPlayer, 1);

	printf
	(
		"Lives Label \"%s\": (%i, %i)\n", tstPlayer.lives.label.text,
		tstPlayer.lives.label.x, tstPlayer.lives.label.y
	);

	printf
	(
		"Current Lives: %i (at %i, %i)\n",
		tstPlayer.lives.value, tstPlayer.lives.x, tstPlayer.lives.y
	);

	printf("Player Alive: %s\n\n", getBoolName(tstPlayer.alive));
	Cconin();

	while (tstPlayer.alive)
	{
		lostLife(&tstPlayer);
		toggleImmunity(tstPlayer);
		printf("After Life Loss:\n");

		printf
		(
			"Lives Label \"%s\": (%i, %i)\n", tstPlayer.lives.label.text,
			tstPlayer.lives.label.x, tstPlayer.lives.label.y
		);

		printf
		(
			"Current Lives: %i (at %i, %i)\n", tstPlayer.lives.value,
			tstPlayer.lives.x, tstPlayer.lives.y
		);

		printf("Player Alive: %s\n\n", getBoolName(tstPlayer.alive));
		Cconin();
	}
}

void testRowGen()
{
	const int MAX_CELL_INFO_ON_SCRN = 4;
	const int NUM_WORLDS = 2;

	World tstP1World;
	World tstP2World;
	World *currentWorld;

	int cellPos;
	int counter;
	int hazardIndex;
	int index;

	initWorld(&tstP1World, 1);
	initWorld(&tstP2World, 2);

	for (counter = 1, currentWorld = &tstP1World;
		 counter <= NUM_WORLDS;
		 counter++, currentWorld = &tstP2World)
	{
		printf
		(
			"%i Player World (%i rows):\n",
			currentWorld->numPlayers, currentWorld->usableRows
		);

		for (index = 0; index < currentWorld->usableRows; index++)
		{
			outRowInfo(&currentWorld->rows[index], index + 1, index);
			putchar('\n');
			Cconin();

			for (cellPos = 0; cellPos < MAX_CELLS; cellPos++)
			{
				if (cellPos > 0 && cellPos % MAX_CELL_INFO_ON_SCRN == 0)
				{
					Cconin();
				}

				outCellInfo(&currentWorld->rows[index].cells[cellPos],
							cellPos + 1, cellPos);
				putchar('\n');
			}

			putchar('\n');
			Cconin();

			for (hazardIndex = 0;
				 hazardIndex < currentWorld->rows[index].hazardCount;
				 hazardIndex++)
			{
				outHazInfo(&currentWorld->rows[index].hazards[hazardIndex]);
				putchar('\n');
			}

			if (currentWorld->rows[index].hazardCount > 0)
			{
				putchar('\n');
				Cconin();
			}
		}
	}
}

/**
 * @brief Gets the name corresponding to a particular cell type.
 * 
 * @param cell The cell to get the name of.
 * @param cellName The character array to store the result in.
 * @return char* The name of the cell type as a string.
 */
char* getCellTypeName(CellType cell, char cellName[])
{
	switch(cell)
	{
		case GRASS_CELL:
			cellName = "GRASS CELL";
			break;
		case ROAD_CELL:
			cellName = "ROAD CELL";
			break;
		case TRACK_CELL:
			cellName = "TRACK CELL";
			break;
		case SPIKE_CELL:
			cellName = "SPIKE CELL";
			break;
		case HEDGE_CELL:
			cellName = "HEDGE CELL";
			break;
		default:
			cellName = "UNKNOWN CELL";
	}

	return cellName;
}

/**
 * @brief Gets the name corresponding to a particular direction.
 * 
 * @param orient The direction to get the name of.
 * @param orientName The character array to store the result in.
 * @return char* The name of the direction as a string.
 */
char* getDirName(Direction dir, char dirName[])
{
	switch(dir)
	{
		case M_UP:
			dirName = "UP";
			break;
		case M_DOWN:
			dirName = "DOWN";
			break;
		case M_LEFT:
			dirName = "LEFT";
			break;
		case M_RIGHT:
			dirName = "RIGHT";
			break;
		case M_NONE:
			dirName = "NO DIRECTION";
			break;
		default:
			dirName = "Unknown";
	}

	return dirName;
}

/**
 * @brief Gets the name corresponding to a particular hazard.
 * 
 * @param hazard The hazard to get the name of.
 * @param hazName The character array to store the result in.
 * @return char* The name of the hazard as a string.
 */
char* getHazName(HazType hazard, char hazName[])
{
	switch(hazard)
	{
		case CAR_HAZ:
			hazName = "CAR";
			break;
		case FEATHERS_HAZ:
			hazName = "MR. FEATHERS";
			break;
		case TRAIN_HAZ:
			hazName = "TRAIN";
			break;
		case NO_HAZ:
			hazName = "NO HAZARD";
			break;
		default:
			hazName = "UNKNOWN HAZARD";
	}

	return hazName;
}

/**
 * @brief Tests the consequences of shifting all the rows off of the world for
 * both a single and double player world.
 */
void testWorldShift()
{
	World tstWorld;
	int rowCounter;
	int shiftCounter;
	int index;

	initWorld(&tstWorld, 1);

	for (shiftCounter = 0; shiftCounter <= tstWorld.usableRows; shiftCounter++)
	{
		printf("After shifting World %i time(s):\n", shiftCounter);
		printf("Bottom Index: %i\n", tstWorld.bottom);
		printf("Top Index: %i\n\n", tstWorld.top);
		
		for (index = tstWorld.bottom, rowCounter = 0;
			 rowCounter < tstWorld.usableRows;
			 index = (index + 1) % tstWorld.usableRows, rowCounter++)
		{
			outRowInfo(&tstWorld.rows[index], rowCounter + 1, index);
			putchar('\n');
			Cconin();
		}

		shiftWorld(&tstWorld);
	}
}

/**
 * @brief Outputs all information about rows to stdout.
 * 
 * @param row The row to print the information of.
 * @param id A integral identifier for the cell.
 * @param index The row's index.
 */
void outRowInfo(const Row* const row, int id, int index)
{
	CellName cellName;
	DirName  dirName;

	printf("Row %i (index %i):\n", id, index);
	printf("Cell Type: %s\n", getCellTypeName(row->cellType, cellName));
	printf("Direction: %s\n", getDirName(row->horzDirection, dirName));
	printf("Hazard Count: %i\n", row->hazardCount);
	printf("Hedge Count: %i\n", row->hedgeCount);
	printf("Spike Count: %i\n", row->spikeCount);
	printf("Y Coordinate: %i\n", row->y);
}

/**
 * @brief Prints information about hazard addition, movement, and removal over
 * 40 clock ticks.
 */
void testHazAdd()
{
	const int MAX_ITER = 40;

	Row tstRows[NUM_ROW_TYPES];

	int hazIndex;
	int rowIndex;
	int iter;

	prepRow(&tstRows[0], 0, GRASS_CELL, M_RIGHT);
	prepRow(&tstRows[1], 0, TRACK_CELL, M_LEFT);
	prepRow(&tstRows[2], 0, ROAD_CELL,  M_RIGHT);

	for (iter = 1; iter <= MAX_ITER; iter++)
	{
		printf("Number of Iterations: %i/%i\n\n", iter, MAX_ITER);
		Cconin();

		puts("Hazards after adding:");
		for (rowIndex = 0; rowIndex < NUM_ROW_TYPES; rowIndex++)
		{
			addHazard(&tstRows[rowIndex]);
			outRowInfo(&tstRows[rowIndex], rowIndex + 1, rowIndex);
			putchar('\n');

			for (hazIndex = 0; hazIndex < tstRows[rowIndex].hazardCount;
				 hazIndex++)
			{
				outHazInfo(&tstRows[rowIndex].hazards[hazIndex]);
				putchar('\n');
			}

			Cconin();
		}

		puts("Hazards after moving:");
		for (rowIndex = 0; rowIndex < NUM_ROW_TYPES; rowIndex++)
		{
			moveHazard(&tstRows[rowIndex]);
			outRowInfo(&tstRows[rowIndex], rowIndex + 1, rowIndex);
			putchar('\n');

			for (hazIndex = 0; hazIndex < tstRows[rowIndex].hazardCount;
				 hazIndex++)
			{
				outHazInfo(&tstRows[rowIndex].hazards[hazIndex]);
				putchar('\n');
			}

			Cconin();
		}

		puts("Hazards after Removing:");
		for (rowIndex = 0; rowIndex < NUM_ROW_TYPES; rowIndex++)
		{
			removeHazard(&tstRows[rowIndex]);
			outRowInfo(&tstRows[rowIndex], rowIndex + 1, rowIndex);
			putchar('\n');

			for (hazIndex = 0; hazIndex < tstRows[rowIndex].hazardCount;
				 hazIndex++)
			{
				outHazInfo(&tstRows[rowIndex].hazards[hazIndex]);
				putchar('\n');
			}

			Cconin();
		}
	}
}

/**
 * @brief Outputs all information about a hazard to stdout.
 * 
 * @param hazard The hazard to print the information of.
 */
void outHazInfo(const Hazard* const hazard)
{
	HazName    hazName;
	OrientName orientName;

	printf("Hazard: %s\n", getHazName(hazard->hazardType, hazName));
	printf("Orientation: %s\n", getOrientName(hazard->orientation, orientName));
	printf("Current X Location: %i\n", hazard->x);
}

/**
 * @brief Allows the player to move across a static World.
 * @details No hazards will be moving. Lives and score will be displayed every
 * time a key is entered. The arrow keys are supported for navigation. Entering
 * 'q' will cause the test to quit. Pressing 'r' will cause the World and Player
 * to be regenerated.
 * 
 * If a player has been hit by a hazard and immunity has been activated, every
 * subsequent valid key press will count for a second of immunity.
 */
void testPlayerMove()
{
	BOOL   keyValid;
	BOOL   quitter;
	UINT32 oldSsp;
	World  tstWorld;

	int rowIdx;
	int cellIdx;

	IKBD_Scancode keyIn;

	int secSinceDmg = -1;

	initWorld(&tstWorld, 1);
	quitter = FALSE;

	while (!quitter)
	{
		printf("You are in a grid of little cells, all different.\n\n");

		handleCollectableCollision(&tstWorld, &tstWorld.mainPlayer);

		if (secSinceDmg >= SECONDS_OF_IMMUNITY)
		{
			toggleImmunity(tstWorld.mainPlayer);
			puts("Immunity is over.");
			printf
			(
				"Immunity is %s.\n\n",
				getBoolName(tstWorld.mainPlayer.immune)
			);
			secSinceDmg = -1;
		}

		if (chkHazardCollision(&tstWorld, tstWorld.mainPlayer.x,
								tstWorld.mainPlayer.y))
		{
			if (!tstWorld.mainPlayer.immune)
			{
				secSinceDmg = 0;
			}

			lostLife(&tstWorld.mainPlayer);
			puts("You have collided with a hazard.");
			printf
			(
				"Immunity is %s.\n\n",
				getBoolName(tstWorld.mainPlayer.immune)
			);
		}

		printf
		(
			"Your current score is %lu.\n\n",
			tstWorld.mainPlayer.score.value
		);

		printf
		(
			"You have %i live(s) and are currently ",
			tstWorld.mainPlayer.lives.value
		);

		if (!(isPlayerAlive(tstWorld.mainPlayer)))
		{
			printf("DEAD.\n\n");
		}
		else
		{
			printf("ALIVE.\n\n");

			printf
			(
				"You are currently at the location (%i, %i).\n",
				tstWorld.mainPlayer.x, tstWorld.mainPlayer.y
			);
			coordToIndex(&tstWorld, &rowIdx, &cellIdx,
						  tstWorld.mainPlayer.x, tstWorld.mainPlayer.y);
			printf
			(
				"This corresponds to Row %i and Cell %i in the World.\n\n",
				rowIdx + 1, cellIdx + 1
			);

			printf("To the left of you is a ");
			outObjInPos(&tstWorld, tstWorld.mainPlayer.x - CELL_LEN,
						tstWorld.mainPlayer.y);
			putchar('\n');

			printf("To the right of you is a ");
			outObjInPos(&tstWorld, tstWorld.mainPlayer.x + CELL_LEN,
						tstWorld.mainPlayer.y);
			putchar('\n');

			printf("Above you is a ");
			outObjInPos(&tstWorld, tstWorld.mainPlayer.x,
						tstWorld.mainPlayer.y - CELL_LEN);
			putchar('\n');

			printf("Below you is a ");
			outObjInPos(&tstWorld, tstWorld.mainPlayer.x,
						tstWorld.mainPlayer.y + CELL_LEN);
			putchar('\n');
		}

		do
		{
			puts("Where do you want to do?\n");
			puts("Use the arrow keys to move.");
			puts("Press 'q' to quit and 'r' to reset the state of the World.");
			puts("Press the Space Bar to stay in place while the time advances \
by one second.");

			keyIn = getKeyBlocking();
			keyValid = TRUE;

			switch(keyIn)
			{
				case IKBD_Q_SCANCODE:
					quitter = TRUE;
					break;
				case IKBD_R_SCANCODE:
					puts("\nThe World has been reset.\n");
					initWorld(&tstWorld, 1);
					break;
				case IKBD_UP_SCANCODE:
					setPlayerDir(&tstWorld.mainPlayer, M_UP);
					break;
				case IKBD_LEFT_SCANCODE:
					setPlayerDir(&tstWorld.mainPlayer, M_LEFT);
					break;
				case IKBD_RIGHT_SCANCODE:
					setPlayerDir(&tstWorld.mainPlayer, M_RIGHT);
					break;
				case IKBD_DOWN_SCANCODE:
					setPlayerDir(&tstWorld.mainPlayer, M_DOWN);
					break;
				default:
					keyValid = FALSE;
					puts("\nThe provided key is invalid. Please try again.\n");
			}
		} while (!keyValid);

		while (playerMayMove(&tstWorld.mainPlayer))
		{
			oldSsp = Su(0);
			movePlayer(&tstWorld, &tstWorld.mainPlayer);
			Su(oldSsp);
		}

		if (secSinceDmg >= 0)
		{
			secSinceDmg++;
		}

		putchar('\n');
	}

	puts("\nLook out. There is a demon behind you.");
}

/**
 * @brief Outputs any information about objects at a specific position in the
 * given world to stdout.
 * 
 * @param world The World to look for an object in.
 * @param x The x coordinate of an object.
 * @param y The y coordinate of an object.
 */
void outObjInPos(const World* const world, int x, int y)
{
	int rowIdx;
	int cellIdx;

	coordToIndex(world, &rowIdx, &cellIdx, x, y);

	if (world->rows[rowIdx].cells[cellIdx].collectableValue != NO_COLLECT)
	{
		switch(world->rows[rowIdx].cells[cellIdx].collectableValue)
		{
			case A_COLLECT_VAL:
				printf("A ");
				break;
			case B_COLLECT_VAL:
				printf("B ");
				break;
			case C_COLLECT_VAL:
				printf("C ");
				break;
			default:
				printf("Unknown ");
		}

		printf("collectable and a ");
	}

	if (chkBorderCollision(x, y))
	{
		printf("border.\n");
	}
	else if (chkHedgeCollision(world, x, y))
	{
		printf("hedge.\n");
	}
	else if (chkHazardCollision(world, x, y))
	{
		printf("hazard.\n");
	}
	else
	{
		printf("cell.\n");
	}
}

/**
 * @brief Holds everything hostage while awaiting a key press.
 * 
 * @return An IKBD scancode.
 */
IKBD_Scancode getKeyBlocking()
{
	return Cnecin() >> 16;
}

/**
 * @brief Gets the name corresponding to a particular orientation.
 * 
 * @param orient The orientation to get the name of.
 * @param orientName The character array to store the result in.
 * @return char* The name of the orientation as a string.
 */
char* getOrientName(Direction orient, char orientName[])
{
	switch(orient)
	{
		case M_NORTH:
			orientName = "NORTH";
			break;
		case M_DOWN:
			orientName = "SOUTH";
			break;
		case M_WEST:
			orientName = "WEST";
			break;
		case M_EAST:
			orientName = "EAST";
			break;
		case M_NONE:
			orientName = "SYMMETRIC";
			break;
		default:
			orientName = "Unknown";
	}

	return orientName;
}

/**
 * @brief Outputs all information about cells to stdout.
 * 
 * @param cell The cell to print the information of.
 * @param id A integral identifier for the cell.
 * @param index The cell's index.
 */
void outCellInfo(const Cell* const cell, int id, int index)
{
	CellName cellName;

	printf("Cell %i (index %i):\n", id, index);
	printf("Cell Type: %s\n", getCellTypeName(cell->cellType, cellName));
	printf("Collectable Value: %i\n", cell->collectableValue);
	printf("X coord: %i\n", cell->x);
}