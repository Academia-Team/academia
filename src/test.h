/**
 * @file test.h
 * @author Academia Team
 * @brief Contains constants and functions designed to assist in testing.
 * 
 * @copyright Copyright Academia Team 2023
 */

#ifndef TEST_H
#define TEST_H

#include <osbind.h>
#include <stdio.h>
#include "raster.h"
#include "types.h"

#define MAX_BOOL_NAME_LEN 7
typedef char BoolName[MAX_BOOL_NAME_LEN + 1];

/**
 * @brief Runs the given function call with super privileges.
 * @param func The function call to execute.
 * @param ssp Used to store the old system stack pointer while gaining super
 * privileges.
 */
#define doSu(func, ssp) \
	ssp = Super(0); \
	func; \
	Super(ssp)

/**
 * @brief Returns the friendly name of a boolean (TRUE/FALSE).
 * 
 * @param val The boolean value to read.
 * @param boolName The boolean name to return.
 * @return The name of the boolean value given.
 */
char* getBoolName(BOOL val, char *boolName);

/**
 * @brief Prompts the user to execute the given test function.
 * @details As part of running, it will clear the screen to ensure that the
 * text can be properly printed.
 * 
 * @param func The function call to execute.
 */
#define run_test(func) \
	clr_scrn((UINT32 *)Physbase()); \
	printf("Next test func: %s\n", #func); \
	printf("Press enter to continue or q to skip.\n"); \
	if ((Cnecin() & 0xFF) != 'q') \
	{ \
		clr_scrn((UINT32 *)Physbase()); \
		func; \
	} \
	else \
	{ \
		clr_scrn((UINT32 *)Physbase()); \
	}

/**
 * @brief Disables the cursor.
 */
void off_curs();

/**
 * @brief Enables the cursor.
 */
void on_curs();

#endif
