/**
 * @file tst_mse.c
 * @author Academia Team
 * @brief Contains an environment for testing the mouse functions.
 * 
 * @copyright Copyright Academia Team 2023
 */

#include <stdio.h>

#include "arg_list.h"
#include "input.h"
#include "test.h"
#include "tst_hndl.h"
#include "types.h"
#include "vector.h"

void mseTstMgr(void (*tstFunc)(ArgList *args));
void t1Mse(ArgList *args);

int main()
{
	TestSuiteID suiteID;

	suiteID = registerTestSuite("Tests mouse functionality.", mseTstMgr);

	registerTestCase(suiteID, "Track mouse position.", NULL, t1Mse);

	handleTests();

	return 0;
}

/**
 * @brief Sets up an environment for testing the mouse.
 * 
 * @param tstFunc The function to test the mouse.
 */
void mseTstMgr(void (*tstFunc)(ArgList *args))
{
	ArgList args;
	Vector origKybd = initKybd();

	initArgList(&args);

	tstFunc(&args);

	restoreKybd(origKybd);
}

/**
 * @brief Displays where the mouse has moved to.
 * 
 * @param args Holds a list of arguments. (Unused)
 */
void t1Mse(ArgList *args)
{
	int   x, y;
	UINT8 asciiKybdVal;

	do
	{
		if (mouseMoved())
		{
			getMousePos(&x, &y);
			printf("Mouse has moved to (%i, %i).\n", x, y);
		}

		if (mouseLclick())
		{
			puts("Mouse has been left clicked.");
		}

		if (mouseRclick())
		{
			puts("Mouse has been right clicked.");
		}

		asciiKybdVal = getAscii();
	} while (asciiKybdVal != 'q' && asciiKybdVal != 'Q');
}