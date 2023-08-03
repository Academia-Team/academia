/**
 * @file bool.h
 * @author Academia Team
 * @brief Defines the BOOL type with the integer constants TRUE and FALSE.
 * 
 * @copyright Copyright Academia Team 2023
 */

#ifndef BOOL_H
#define BOOL_H

#define BOOL_DEFINED 1

typedef enum {FALSE = 0, TRUE = 1} BOOL;


/**
 * @brief The maximum number of characters returned by getBoolName().
 */
#define MAX_BOOL_NAME_LEN 7

/**
 * @brief A type of string guaranteed to be able to hold the string returned by
 * getBoolName().
 */
typedef char BoolName[MAX_BOOL_NAME_LEN + 1];

/**
 * @brief Returns the friendly name of a boolean value (TRUE/FALSE).
 * 
 * @param boolean The boolean value to read.
 * @return The name of the boolean value given or "UNKNOWN" if the given value
 * is not recognized.
 */
#define getBoolName(boolean) \
	(boolean == FALSE ? "FALSE" : (boolean == TRUE ? "TRUE" : "UNKNOWN"))

#endif