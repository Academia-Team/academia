/**
 * @file toggle.h
 * @author Academia Team
 * @brief Defines the Toggle type with the integer constants OFF and ON.
 * 
 * @copyright Copyright Academia Team 2023
 */

#ifndef TOGGLE_H
#define TOGGLE_H

typedef enum
{
	OFF = 0,
	ON  = 1
} Toggle;

/**
 * @brief The maximum number of characters returned by getToggleName().
 */
#define MAX_TOGGLE_NAME_LEN 7

/**
 * @brief A type of string guaranteed to be able to hold the string returned by
 * getToggleName().
 */
typedef char ToggleName[MAX_TOGGLE_NAME_LEN + 1];

/**
 * @brief Returns the friendly name of a toggle value (ON/OFF).
 * 
 * @param toggleVal The toggle value to read.
 * @return The name of the toggle value given or "UNKNOWN" if the given value
 * is not recognized.
 */
#define getToggleName(toggleVal) \
	(toggleVal == OFF ? "OFF" : (toggleVal == ON ? "ON" : "UNKNOWN"))

#endif
