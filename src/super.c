/**
 * @file super.c
 * @author Academia Team
 * @brief Provides functionality for gaining super privileges.
 * 
 * @copyright Copyright Academia Team 2023
 */

#include "super.h"
#include "types.h"

UINT8 isSu()
{
	return (Su(1) == -1);
}