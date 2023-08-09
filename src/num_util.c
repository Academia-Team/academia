/**
 * @file num_util.c
 * @author Academia Team
 * @brief Contains mathematical functions to interact with integral values.
 * 
 * @copyright Copyright Academia Team 2023
 */

#include <stdlib.h>

#include "num_util.h"

int random(int rangeMax)
{
	int value;

	do
	{
		value = rand();
	} while (value == 0);
	
	return (value % (rangeMax + 1));
}

void resetRandom()
{
	srand(1);
}