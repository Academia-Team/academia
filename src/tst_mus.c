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
#include "vbl.h"
#include "vector.h"

void musTstMgr(void (*tstFunc)(ArgList *args));

void t1Mus(ArgList *args);

int main(int argc, char **argv)
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
	const Vector ORIG_VBL = vbl_init();

	ArgList args;
	Vector origKybd = initKybd();

	initArgList(&args);

	tstFunc(&args);

	restoreKybd(origKybd);
	vbl_restore(ORIG_VBL);
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
	timeMusUpdated = get_time();
	
	do
	{
		curTime = get_time();
		update_music(curTime - timeMusUpdated);
		timeMusUpdated = get_time();
	} while (getAscii() != 'q' && getAscii() != 'Q');
}