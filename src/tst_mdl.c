/**
 * @file tst_mdl.c
 * @author Academia Team
 * @brief Contains functions aimed at testing the model.
 * 
 * @copyright Copyright Academia Team 2023
 */

#include <stdio.h>

#include "arg_list.h"
#include "events.h"
#include "ikbdcode.h"
#include "input.h"
#include "model.h"
#include "move.h"
#include "num_util.h"
#include "super.h"
#include "test.h"
#include "tst_hndl.h"
#include "types.h"
#include "vector.h"

void modelTstMgr(void (*tstFunc)(ArgList *args));

void t1ScoreBox(ArgList *args);
void t2ScoreBox(ArgList *args);
void t3ScoreBox(ArgList *args);
void t4ScoreBox(ArgList *args);
void t5ScoreBox(ArgList *args);
void t6ScoreBox(ArgList *args);

void outScoreInfo(Score *scoreBox, FILE *stream);

void t1LivesBox(ArgList *args);
void t2LivesBox(ArgList *args);
void t3LivesBox(ArgList *args);
void t4LivesBox(ArgList *args);
void t5LivesBox(ArgList *args);

void outLivesInfo(Player *player, FILE *stream);

void t1RowGen(ArgList *args);
void t2RowGen(ArgList *args);
void testRowGenCommon(World *world);

void t1WorldShift(ArgList *args);
void t2WorldShift(ArgList *args);
void testWorldShiftCommon(World *world);

void outRowInfo(const Row* const row, int id, int index, FILE *stream);

void t1HazAdd(ArgList *args);

void outHazInfo(const Hazard* const hazard, FILE *stream);

void t1PlayerMove(ArgList *args);

void outObjInPos(const World* const world, int x, int y, FILE *stream);
void outCellInfo(const Cell* const cell, int id, int index, FILE *stream);

int main(int argc, char **argv)
{
	TestSuiteID suiteID;

	suiteID = registerTestSuite("Tests the Score Box.", modelTstMgr);

	registerTestCase(suiteID,
					 "Displays the text and location of the components of a recently initialized Score Box whose x and y values are zero.",
					 NULL, t1ScoreBox);
	
	registerTestCase(suiteID,
					 "Displays information on a Score Box whose score has been incremented by 100.",
					 NULL, t2ScoreBox);

	registerTestCase(suiteID,
					 "Displays information on a Score Box whose score has been incremented by 1000.",
					 NULL, t3ScoreBox);

	registerTestCase(suiteID,
					 "Displays information on a Score Box whose score has been incremented by the maximum value a UINT32 can hold.",
					 NULL, t4ScoreBox);

	registerTestCase(suiteID,
					 "Checks for a carry error if the score is incremented by the maximum possible score after holding a non-zero value.",
					 NULL, t5ScoreBox);

	registerTestCase(suiteID,
					 "Checks for a carry error if the score is incremented by one after holding the maximum possible score.",
					 NULL, t6ScoreBox);

	suiteID = registerTestSuite("Tests the Lives Box.", modelTstMgr);

	registerTestCase(suiteID,
					 "Displays the text and location of a Lives Box associated with a recently initialized player.",
					 NULL, t1LivesBox);

	registerTestCase(suiteID,
					 "Displays information on a Lives Box associated with a player who has lost one life.",
					 NULL, t2LivesBox);

	registerTestCase(suiteID,
					 "Displays information on a Lives Box associated with a player who has lost two lives.",
					 NULL, t3LivesBox);

	registerTestCase(suiteID,
					 "Displays information on a Lives Box associated with a player who has lost all three lives.",
					 NULL, t4LivesBox);

	registerTestCase(suiteID,
					 "Displays information on a Lives Box where there is an attempt to remove a life from an already dead player.",
					 NULL, t5LivesBox);

	suiteID = registerTestSuite("Tests initial world generation.", modelTstMgr);

	registerTestCase(suiteID,
					 "Tests row generation in a single player world.",
					 NULL, t1RowGen);

	registerTestCase(suiteID,
					 "Tests row generation in a two player world.",
					 NULL, t2RowGen);

	suiteID = registerTestSuite("Tests shifting rows in a world.", modelTstMgr);

	registerTestCase(suiteID,
					 "Test the consequences of shifting all the rows off of the world for a single player world.",
					 NULL, t1WorldShift);

	registerTestCase(suiteID,
					 "Test the consequences of shifting all the rows off of the world for a two player world.",
					 NULL, t2WorldShift);

	suiteID = registerTestSuite("Tests hazard behaviour.", modelTstMgr);

	registerTestCase(suiteID,
					 "Prints information about hazard addition, movement, and removal over 40 clock ticks.",
					 NULL, t1HazAdd);

	suiteID = registerTestSuite("Tests player movement.", modelTstMgr);

	registerTestCase(suiteID,
					 "Show player movement across a static World.",
					 NULL, t1PlayerMove);

	handleTests();

	return 0;
}

/**
 * @brief Sets up an environment for testing the model.
 * @details It ensures that a test doesn't end until a key is pressed.
 * 
 * @param tstFunc The function to test the model.
 */
void modelTstMgr(void (*tstFunc)(ArgList *args))
{
	ArgList args;
	Vector origKybd = initKybd();
	IKBD_Scancode scancode;

	initArgList(&args);

	/* Since the model takes advantage of random numbers, make sure the rng is
	reset before every test so that choosing to do/skip certain tests won't
	affect the results of all the other tests. */
	resetRandom();

	tstFunc(&args);

	while ((scancode = getKey()) == NO_KEY);

	restoreKybd(origKybd);
}

/**
 * @brief Displays the text and location of the components of a recently
 * initialized Score Box whose x and y values are zero.
 * 
 * @param args Holds a list of arguments. (Unused)
 */
void t1ScoreBox(ArgList *args)
{
	Score scoreBox;

	initScore(0, 0, &scoreBox);
	outScoreInfo(&scoreBox, stdout);
}

/**
 * @brief Displays the text and location of the components of a Score Box whose
 * score has been incremented by 100.
 * 
 * @param args Holds a list of arguments. (Unused)
 */
void t2ScoreBox(ArgList *args)
{
	Score scoreBox;

	initScore(0, 0, &scoreBox);
	updateScore(100, &scoreBox);
	outScoreInfo(&scoreBox, stdout);
}

/**
 * @brief Displays the text and location of the components of a Score Box whose
 * score has been incremented by 1000.
 * 
 * @param args Holds a list of arguments. (Unused)
 */
void t3ScoreBox(ArgList *args)
{
	Score scoreBox;

	initScore(0, 0, &scoreBox);
	updateScore(1000, &scoreBox);
	outScoreInfo(&scoreBox, stdout);
}

/**
 * @brief Displays the text and location of the components of a Score Box whose
 * score has been incremented by the maximum value a UINT32 can hold.
 * 
 * @param args Holds a list of arguments. (Unused)
 */
void t4ScoreBox(ArgList *args)
{
	Score scoreBox;

	initScore(0, 0, &scoreBox);
	updateScore(UINT32_MAX, &scoreBox);
	outScoreInfo(&scoreBox, stdout);
}

/**
 * @brief Checks if the score can have a carry error if the score is attempted
 * to be incremented by the maximum possible score after holding a non-zero
 * value.
 * 
 * @param args Holds a list of arguments. (Unused)
 */
void t5ScoreBox(ArgList *args)
{
	Score scoreBox;

	initScore(0, 0, &scoreBox);
	updateScore(1, &scoreBox);
	updateScore(UINT32_MAX, &scoreBox);
	
	puts(scoreBox.value < UINT32_MAX ?
		 "The test has failed." :
		 "The test has succeeded.");
	printf("The score has a value of %lu.\n", scoreBox.value);
}

/**
 * @brief Checks if the score can have a carry error if the score is attempted
 * to be incremented by one after holding the maximum possible score.
 * 
 * @param args Holds a list of arguments. (Unused)
 */
void t6ScoreBox(ArgList *args)
{
	Score scoreBox;

	initScore(0, 0, &scoreBox);
	updateScore(UINT32_MAX, &scoreBox);
	updateScore(1, &scoreBox);
	
	puts(scoreBox.value < UINT32_MAX ?
		 "The test has failed." :
		 "The test has succeeded.");
	printf("The score has a value of %lu.\n", scoreBox.value);
}

/**
 * @brief Outputs information about the individual components of the given
 * scoreBox to the given stream.
 * 
 * @details Includes details of where the score text and the label saying
 * "SCORE" are on screen. Also displays the actual text that will be rendered
 * on screen. If the scoreBox is NULL, it also indicates that.
 * 
 * @param scoreBox The scoreBox to display the information of.
 * @param stream The stream to write the scoreBox information to.
 */
void outScoreInfo(Score *scoreBox, FILE *stream)
{
	if (scoreBox == NULL)
	{
		fputs("Score is NULL.\n", stream);
	}
	else
	{
		fprintf
		(
			stream, "Score Label \"%s\": (%i, %i)\n", scoreBox->label.text,
			scoreBox->label.x, scoreBox->label.y
		);

		fprintf
		(
			stream, "Score Text \"%lu\": (%i, %i)\n", scoreBox->value,
			scoreBox->x, scoreBox->y
		);

		fprintf(stream, "Current Score: %lu\n", scoreBox->value);
	}
}

/**
 * @brief Displays the text and location of a Lives Box associated with a
 * recently initialized player.
 * 
 * @param args Holds a list of arguments. (Unused)
 */
void t1LivesBox(ArgList *args)
{
	Player player;

	initPlayer(&player, 1);
	outLivesInfo(&player, stdout);
	putchar('\n');
}

/**
 * @brief Displays the text and location of a Lives Box associated with a
 * player who has lost one life.
 * 
 * @param args Holds a list of arguments. (Unused)
 */
void t2LivesBox(ArgList *args)
{
	const int NUM_LIVES_TO_LOSE = 1;

	Player player;
	int    counter;

	initPlayer(&player, 1);

	for (counter = 1;
		 counter <= NUM_LIVES_TO_LOSE;
		 counter++, toggleImmunity(player))
	{
		lostLife(&player);
	}
	
	outLivesInfo(&player, stdout);
	putchar('\n');
}

/**
 * @brief Displays the text and location of a Lives Box associated with a
 * player who has lost two lives.
 * 
 * @param args Holds a list of arguments. (Unused)
 */
void t3LivesBox(ArgList *args)
{
	const int NUM_LIVES_TO_LOSE = 2;

	Player player;
	int    counter;

	initPlayer(&player, 1);

	for (counter = 1;
		 counter <= NUM_LIVES_TO_LOSE;
		 counter++, toggleImmunity(player))
	{
		lostLife(&player);
	}

	outLivesInfo(&player, stdout);
	putchar('\n');
}

/**
 * @brief Displays the text and location of a Lives Box associated with a
 * player who has lost all three lives.
 * 
 * @param args Holds a list of arguments. (Unused)
 */
void t4LivesBox(ArgList *args)
{
	const int NUM_LIVES_TO_LOSE = 3;

	Player player;
	int    counter;

	initPlayer(&player, 1);

	for (counter = 1;
		 counter <= NUM_LIVES_TO_LOSE;
		 counter++, toggleImmunity(player))
	{
		lostLife(&player);
	}

	outLivesInfo(&player, stdout);
	putchar('\n');
}

/**
 * @brief Displays the text and location of a Lives Box where there is an
 * attempt to remove a life from an already dead player.
 * 
 * @param args Holds a list of arguments. (Unused)
 */
void t5LivesBox(ArgList *args)
{
	const int NUM_LIVES_TO_LOSE = 4;

	Player player;
	int    counter;

	initPlayer(&player, 1);

	for (counter = 1;
		 counter <= NUM_LIVES_TO_LOSE;
		 counter++, toggleImmunity(player))
	{
		lostLife(&player);
	}

	outLivesInfo(&player, stdout);
	putchar('\n');
}

/**
 * @brief Outputs information about the heath of the given player.
 * 
 * @note Every LivesBox is connected to a Player object.
 * 
 * @details Includes details of where the life text and the label saying
 * "LIVES" are on screen. Also displays the actual text that will be rendered
 * on screen. If the player is NULL, it also indicates that.
 * 
 * @param player The player to display the lives information of.
 * @param stream The stream to write the lives information to.
 */
void outLivesInfo(Player *player, FILE *stream)
{
	if (player == NULL)
	{
		fputs("Player is NULL.\n", stream);
	}
	else
	{
		fprintf
		(
			stream, "Lives Label \"%s\": (%i, %i)\n", player->lives.label.text,
			player->lives.label.x, player->lives.label.y
		);

		fprintf
		(
			stream, "Current Lives: %i (at %i, %i)\n", player->lives.value,
			player->lives.x, player->lives.y
		);

		fprintf(stream, "Player Alive: %s\n", getBoolName(player->alive));
	}
}

/**
 * @brief Tests row generation in a single player world.
 * 
 * @param args Holds a list of arguments. (Unused)
 */
void t1RowGen(ArgList *args)
{
	World world;

	initWorld(&world, 1);
	testRowGenCommon(&world);
}

/**
 * @brief Tests row generation in a two player world.
 * 
 * @param args Holds a list of arguments. (Unused)
 */
void t2RowGen(ArgList *args)
{
	World world;

	initWorld(&world, 2);
	testRowGenCommon(&world);
}

/**
 * @brief Shows information related to the rows in a given world.
 * 
 * @param world The world to display the information of.
 */
void testRowGenCommon(World *world)
{
	const int MAX_CELL_INFO_ON_SCRN = 4;

	int index;
	int cellPos;
	int hazardIndex;

	if (world != NULL)
	{
		printf
		(
			"%i Player World (%i rows):\n",
			world->numPlayers, world->usableRows
		);

		for (index = 0; index < world->usableRows; index++)
		{
			outRowInfo(&world->rows[index], index + 1, index, stdout);
			putchar('\n');
			getBKey();

			for (cellPos = 0; cellPos < MAX_CELLS; cellPos++)
			{
				if (cellPos > 0 && cellPos % MAX_CELL_INFO_ON_SCRN == 0)
				{
					getBKey();
				}

				outCellInfo(&world->rows[index].cells[cellPos],
							cellPos + 1, cellPos, stdout);
				putchar('\n');
			}

			putchar('\n');
			getBKey();

			for (hazardIndex = 0;
				 hazardIndex < world->rows[index].hazardCount;
				 hazardIndex++)
			{
				outHazInfo(&world->rows[index].hazards[hazardIndex], stdout);
				putchar('\n');
			}

			if (world->rows[index].hazardCount > 0)
			{
				putchar('\n');
				getBKey();
			}
		}
	}
}

/**
 * @brief Test shifting the rows off of a one player world.
 * 
 * @param args Holds a list of arguments. (Unused)
 */
void t1WorldShift(ArgList *args)
{
	World world;

	initWorld(&world, 1);
	testWorldShiftCommon(&world);
}

/**
 * @brief Test shifting the rows off of a two player world.
 * 
 * @param args Holds a list of arguments. (Unused)
 */
void t2WorldShift(ArgList *args)
{
	World world;

	initWorld(&world, 2);
	testWorldShiftCommon(&world);
}

/**
 * @brief Test the consequences of shifting all the rows off of the given world.
 * 
 * @param world The world to display the information of.
 */
void testWorldShiftCommon(World *world)
{
	int rowCounter;
	int shiftCounter;
	int index;

	for (shiftCounter = 0; shiftCounter <= world->usableRows; shiftCounter++)
	{
		printf("After shifting World %i time(s):\n", shiftCounter);
		printf("Bottom Index: %i\n", world->bottom);
		printf("Top Index: %i\n\n", world->top);
		
		for (index = world->bottom, rowCounter = 0;
			 rowCounter < world->usableRows;
			 index = (index + 1) % world->usableRows, rowCounter++)
		{
			outRowInfo(&world->rows[index], rowCounter + 1, index, stdout);
			putchar('\n');
			getBKey();
		}

		shiftWorld(world);
	}
}

/**
 * @brief Outputs all information about rows to stdout.
 * 
 * @param row The row to print the information of.
 * @param id A integral identifier for the cell.
 * @param index The row's index.
 * @param stream The stream to write the scoreBox information to.
 */
void outRowInfo(const Row* const row, int id, int index, FILE *stream)
{
	fprintf(stream, "Row %i (index %i):\n", id, index);
	fprintf(stream, "Cell Type: %s\n", getCellTypeName(row->cellType));
	fprintf(stream, "Direction: %s\n", getDirName(row->horzDirection));
	fprintf(stream, "Hazard Count: %i\n", row->hazardCount);
	fprintf(stream, "Hedge Count: %i\n", row->hedgeCount);
	fprintf(stream, "Spike Count: %i\n", row->spikeCount);
	fprintf(stream, "Y Coordinate: %i\n", row->y);
}

/**
 * @brief Prints information about hazard addition, movement, and removal over
 * 40 clock ticks.
 * 
 * @param args Holds a list of arguments. (Unused)
 */
void t1HazAdd(ArgList *args)
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
		getBKey();

		puts("Hazards after adding:");
		for (rowIndex = 0; rowIndex < NUM_ROW_TYPES; rowIndex++)
		{
			addHazard(&tstRows[rowIndex]);
			outRowInfo(&tstRows[rowIndex], rowIndex + 1, rowIndex, stdout);
			putchar('\n');

			for (hazIndex = 0; hazIndex < tstRows[rowIndex].hazardCount;
				 hazIndex++)
			{
				outHazInfo(&tstRows[rowIndex].hazards[hazIndex], stdout);
				putchar('\n');
			}

			getBKey();
		}

		puts("Hazards after moving:");
		for (rowIndex = 0; rowIndex < NUM_ROW_TYPES; rowIndex++)
		{
			moveHazard(&tstRows[rowIndex]);
			outRowInfo(&tstRows[rowIndex], rowIndex + 1, rowIndex, stdout);
			putchar('\n');

			for (hazIndex = 0; hazIndex < tstRows[rowIndex].hazardCount;
				 hazIndex++)
			{
				outHazInfo(&tstRows[rowIndex].hazards[hazIndex], stdout);
				putchar('\n');
			}

			getBKey();
		}

		puts("Hazards after Removing:");
		for (rowIndex = 0; rowIndex < NUM_ROW_TYPES; rowIndex++)
		{
			removeHazard(&tstRows[rowIndex]);
			outRowInfo(&tstRows[rowIndex], rowIndex + 1, rowIndex, stdout);
			putchar('\n');

			for (hazIndex = 0; hazIndex < tstRows[rowIndex].hazardCount;
				 hazIndex++)
			{
				outHazInfo(&tstRows[rowIndex].hazards[hazIndex], stdout);
				putchar('\n');
			}
		}
	}
}

/**
 * @brief Outputs all information about a hazard to stdout.
 * 
 * @param hazard The hazard to print the information of.
 * @param stream The stream to write the scoreBox information to.
 */
void outHazInfo(const Hazard* const hazard, FILE *stream)
{
	fprintf(stream, "Hazard: %s\n", getHazName(hazard->hazardType));
	fprintf(stream, "Orientation: %s\n", getOrientName(hazard->orientation));
	fprintf(stream, "Current X Location: %i\n", hazard->x);
}

/**
 * @brief Shows the player to move across a static World.
 * @details No hazards will be moving. Lives and score will be displayed every
 * time a key is entered. The arrow keys are supported for navigation. Entering
 * 'q' will cause the test to quit. Pressing 'r' will cause the World and Player
 * to be regenerated.
 * 
 * If a player has been hit by a hazard and immunity has been activated, every
 * subsequent valid key press will count for a second of immunity.
 * 
 * @param args Holds a list of arguments. (Unused)
 */
void t1PlayerMove(ArgList *args)
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
						tstWorld.mainPlayer.y, stdout);
			putchar('\n');

			printf("To the right of you is a ");
			outObjInPos(&tstWorld, tstWorld.mainPlayer.x + CELL_LEN,
						tstWorld.mainPlayer.y, stdout);
			putchar('\n');

			printf("Above you is a ");
			outObjInPos(&tstWorld, tstWorld.mainPlayer.x,
						tstWorld.mainPlayer.y - CELL_LEN, stdout);
			putchar('\n');

			printf("Below you is a ");
			outObjInPos(&tstWorld, tstWorld.mainPlayer.x,
						tstWorld.mainPlayer.y + CELL_LEN, stdout);
			putchar('\n');
		}

		do
		{
			puts("What do you want to do?\n");
			puts("Use the arrow keys to move.");
			puts("Press 'q' to quit and 'r' to reset the state of the World.");
			puts("Press the Space Bar to stay in place while the time advances \
by one second.");

			keyIn = getBKey();
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
				case IKBD_SPACE_SCANCODE:
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
 * @param stream The stream to write the scoreBox information to.
 */
void outObjInPos(const World* const world, int x, int y, FILE *stream)
{
	int rowIdx;
	int cellIdx;

	coordToIndex(world, &rowIdx, &cellIdx, x, y);

	if (chkBorderCollision(x, y))
	{
		fprintf(stream, "border.\n");
	}
	else
	{
		if (world->rows[rowIdx].cells[cellIdx].collectableValue != NO_COLLECT)
		{
			switch(world->rows[rowIdx].cells[cellIdx].collectableValue)
			{
				case A_COLLECT_VAL:
					fprintf(stream, "A ");
					break;
				case B_COLLECT_VAL:
					fprintf(stream, "B ");
					break;
				case C_COLLECT_VAL:
					fprintf(stream, "C ");
					break;
				default:
					fprintf(stream, "UNKNOWN ");
			}

			fprintf(stream, "collectable and a ");
		}

		if (chkHedgeCollision(world, x, y))
		{
			fprintf(stream, "hedge.\n");
		}
		else if (chkHazardCollision(world, x, y))
		{
			fprintf(stream, "hazard.\n");
		}
		else
		{
			fprintf(stream, "cell.\n");
		}
	}
}

/**
 * @brief Outputs all information about cells to stdout.
 * 
 * @param cell The cell to print the information of.
 * @param id A integral identifier for the cell.
 * @param index The cell's index.
 * @param stream The stream to write the scoreBox information to.
 */
void outCellInfo(const Cell* const cell, int id, int index, FILE *stream)
{
	fprintf(stream, "Cell %i (index %i):\n", id, index);
	fprintf(stream, "Cell Type: %s\n", getCellTypeName(cell->cellType));
	fprintf(stream, "Collectable Value: %i\n", cell->collectableValue);
	fprintf(stream, "X coord: %i\n", cell->x);
}