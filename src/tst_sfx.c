/**
 * @file tst_sfx.c
 * @author Academia Team
 * @brief It is designed to test the functionality of the effects module.
 * 
 * @copyright Copyright Academia Team 2023
 */

#include <stdio.h>

#include "arg_list.h"
#include "effects.h"
#include "input.h"
#include "psg.h"
#include "test.h"
#include "tst_hndl.h"
#include "vector.h"

void sfxTstMgr(void (*tstFunc)(ArgList *args));

void t1SFX(ArgList *args);
void t2SFX(ArgList *args);
void t3SFX(ArgList *args);
void t4SFX(ArgList *args);
void t5SFX(ArgList *args);
void t6SFX(ArgList *args);

int main(int argc, char **argv)
{
	TestSuiteID suiteID;

	suiteID = registerTestSuite("Tests playing sound effects.", sfxTstMgr);

	registerTestCase(suiteID, "Play the Pain sound effect.", NULL, t1SFX);

	registerTestCase(suiteID,
					 "Play the three stages of the Death sound effect.", NULL,
					 t2SFX);

	registerTestCase(suiteID, "Play the Walking sound effect.", NULL, t3SFX);

	registerTestCase(suiteID, "Play the Train sound effect.", NULL, t4SFX);

	registerTestCase(suiteID, "Play the Collecting Collectables sound effect.",
					 NULL, t5SFX);

	registerTestCase(suiteID, "Play the Beep sound effect.", NULL, t6SFX);

	handleTests();

	return 0;
}

/**
 * @brief Sets up an environment for testing the playing of sound effects.
 * @details It ensures that a test doesn't end until a key is pressed. Also
 * ensures all audio is reset before moving on to the next test.
 * 
 * @param tstFunc The function to test a sound effect.
 */
void sfxTstMgr(void (*tstFunc)(ArgList *args))
{
	ArgList args;
	Vector origKybd = initKybd();
	IKBD_Scancode scancode;

	initArgList(&args);

	tstFunc(&args);

	while ((scancode = getKey()) == NO_KEY);

	restoreKybd(origKybd);
	stop_sound();
}

/**
 * @brief Play the Pain sound effect.
 * 
 * @param args Holds a list of arguments. (Unused)
 */
void t1SFX(ArgList *args)
{
	play_pain();
}

/**
 * @brief Play the three stages of the Death sound effect.
 * 
 * @param args Holds a list of arguments. (Unused)
 */
void t2SFX(ArgList *args)
{
	const int MAX_DEATH_COUNT = 3;
	int count;

	for (count = 1; count <= MAX_DEATH_COUNT; count++)
	{
		printf("Stage %i/%i.\n", count, MAX_DEATH_COUNT);
		play_death();

		if (count < MAX_DEATH_COUNT)
		{
			getBKey();
		}
	}
}

/**
 * @brief Play the Walking sound effect.
 * 
 * @param args Holds a list of arguments. (Unused)
 */
void t3SFX(ArgList *args)
{
	play_walk();
}

/**
 * @brief Play the Train sound effect.
 */
void t4SFX(ArgList *args)
{
	play_train();
}

/**
 * @brief Play the Collecting Collectables sound effect.
 * 
 * @param args Holds a list of arguments. (Unused)
 */
void t5SFX(ArgList *args)
{
	play_collect();
}

/**
 * @brief Play the Beep sound effect.
 * 
 * @param args Holds a list of arguments. (Unused)
 */
void t6SFX(ArgList *args)
{
	play_beep();
}