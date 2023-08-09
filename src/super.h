/**
 * @file super.h
 * @author Academia Team
 * @brief Provides functionality for gaining super privileges.
 * 
 * @copyright Copyright Academia Team 2023
 */

#ifndef SUPER_H
#define SUPER_H

#include "types.h"

/**
 * @brief Executes the Super gemdos call.
 * @details When 0 is passed as a stack address, the mode we are in is toggled
 * with the current stack used in the changed mode. If anything else other than
 * 1 is passed, the stack address is changed to the specified address. Else, if
 * 1 is specified as parameter, it returns -1 if we are in Super mode or 0 if in
 * User mode.
 * 
 * @param ssp The address to use for the stack or 0 or 1.
 * @return The old stack address or 0 or 1.
 */
UINT32 Su(UINT32 ssp);

/**
 * @brief Checks if code is in Super mode or not.
 * 
 * @return 1 if in Super mode; else 0.
 */
UINT8 isSu();

/**
 * @brief Runs the given function call with super privileges.
 * @param func The function call to execute.
 * @param ssp Used to store the old system stack pointer while gaining super
 * privileges.
 */
#define doSu(func, ssp) \
	ssp = Su(0); \
	func; \
	Su(ssp)

#endif
