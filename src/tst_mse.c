/**
 * @file tst_mse.c
 * @author Academia Team
 * @brief Contains an environment for testing the mouse functions.
 * 
 * @copyright Copyright Academia Team 2023
 */

#include <stdio.h>

#include "bool.h"
#include "input.h"
#include "types.h"

int main()
{
	const Vector SYS_KYBD = initKybd();
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

	restoreKybd(SYS_KYBD);

	return 0;
}