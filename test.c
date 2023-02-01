/**
 * @file test.c
 * @author Academia Team
 * @brief Contains constants and functions designed to assist in testing.
 * 
 * @copyright Copyright Academia Team 2023
 */

#include <stdio.h>
#include "test.h"

char* getBoolName(BOOL val, char *boolName)
{
	switch(val)
	{
		case TRUE:
			boolName = "TRUE";
			break;
		case FALSE:
			boolName = "FALSE";
			break;
		default:
			boolName = "Unknown";
	}

	return boolName;
}

void off_curs()
{
	printf("\033f");
	fflush(stdout);
}

void on_curs()
{
	printf("\033e");
	fflush(stdout);
}