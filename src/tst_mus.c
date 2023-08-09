/**
 * @file tst_mus.c
 * @author Academia Team
 * @brief It is designed to test the functionality of the music module.
 * 
 * @copyright Copyright Academia Team 2023
 */

#include <stdio.h>

#include "arg_list.h"
#include "input.h"
#include "music.h"
#include "psg.h"
#include "super.h"
#include "test.h"
#include "tst_hndl.h"
#include "types.h"
#include "vector.h"

void musTstMgr(void (*tstFunc)(ArgList *args));

void t1Mus(ArgList *args);

UINT32 getTime();

int main()
{
	TestSuiteID suiteID;

	suiteID = registerTestSuite("Plays music used in game.", musTstMgr);

	registerTestCase(suiteID, "Plays the main game music", NULL, t1Mus);

	handleTests();

	return 0;
}

/**
 * @brief Sets up an environment for testing the playing of music.
 * @details It ensures all audio is reset before moving on to the next test.
 * 
 * @param tstFunc The function to test the music.
 */
void musTstMgr(void (*tstFunc)(ArgList *args))
{
	ArgList args;
	Vector origKybd = initKybd();

	initArgList(&args);

	tstFunc(&args);

	restoreKybd(origKybd);
	stop_sound();
}

/**
 * @brief Tests the music module by playing the main game song until the 'q' key
 * is pressed.
 * 
 * @param args Holds a list of arguments. (Unused)
 */
void t1Mus(ArgList *args)
{
	UINT32 curTime;
	UINT32 timeMusUpdated;

	puts("Press q to stop playing the song");
	start_music();
	timeMusUpdated = getTime();
	
	do
	{
		curTime = getTime();
		update_music(curTime - timeMusUpdated);
		timeMusUpdated = getTime();
	} while (getAscii() != 'q' && getAscii() != 'Q');
}

/**
 * @brief Returns the current time provided by the system clock.
 * 
 * @return The current system clock value as a UINT32.
 */
UINT32 getTime()
{
	UINT32 curTime;
	UINT32 *timer = (UINT32 *)0x462;
	UINT32 oldSsp;

	oldSsp = Su(0);
	curTime = *timer;
	Su(oldSsp);

	return curTime;
}