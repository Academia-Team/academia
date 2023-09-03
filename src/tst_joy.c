/**
 * @file tst_joy.c
 * @author Academia Team
 * @brief Contains an environment for testing the joystick functions.
 * 
 * @copyright Copyright Academia Team 2023
 */

#include <stdio.h>

#include "arg_list.h"
#include "input.h"
#include "move.h"
#include "test.h"
#include "tst_hndl.h"
#include "types.h"
#include "vector.h"

void joyTstMgr(void (*tstFunc)(ArgList *args));
void t1Joy(ArgList *args);

int main(int argc, char **argv)
{
	TestSuiteID suiteID;

	suiteID = registerTestSuite("Tests joystick functionality.", joyTstMgr);

	registerTestCase(suiteID, "Track joystick position.", NULL, t1Joy);

	handleTests();

	return 0;
}

/**
 * @brief Sets up an environment for testing the joystick.
 * 
 * @param tstFunc The function to test the joystick.
 */
void joyTstMgr(void (*tstFunc)(ArgList *args))
{
	ArgList args;
	Vector origKybd = initKybd();

	initArgList(&args);

	tstFunc(&args);

	restoreKybd(origKybd);
}

/**
 * @brief Displays the current status of the joystick.
 * 
 * @param args Holds a list of arguments. (Unused)
 */
void t1Joy(ArgList *args)
{
	UINT8 asciiKybdVal;
	SINT8 joyPos;
	SINT8 prevJoyPos = -1;

	joyPos = getJoyPos();
	printf("Joystick Pos is currently %s\n", getBodyRelDir(joyPos));
	prevJoyPos = joyPos;

	do
	{
		if ((joyPos = getJoyPos()) != prevJoyPos)
		{
			printf("Joystick Pos Changed To: %s\n", getBodyRelDir(joyPos));
			prevJoyPos = joyPos;
		}
		if (joyButtonPressed())
		{
			puts("Joystick Button Pressed.");
		}

		asciiKybdVal = getAscii();
	} while (asciiKybdVal != 'q' && asciiKybdVal != 'Q');
}