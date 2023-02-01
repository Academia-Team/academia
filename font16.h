/**
 * @file font16.h
 * @author Morgan Payette
 * @author Academia Team
 * @brief Provides access to a 16x16 font (which was created by Morgan on behalf
 * of the Academia Team).
 * 
 * @copyright Copyright Academia Team 2023
 */

#ifndef FONT16_H
#define FONT16_H

#include "types.h"

extern const UINT16 font16[];

#define FONT16_HEIGHT 16
#define FONT16_WIDTH  16

/**
 * @brief Returns the index corresponding to the digit in the font16 array.
 * 
 * @param digit The digit to get the index for.
 */
#define getFont16Digit(digit) (FONT16_HEIGHT * ((digit) + 16))

/**
 * @brief Returns the index corresponding to the printable character
 * corresponding to the character in the font16 array.
 */
#define getFont16PrintableChar(character) (FONT16_HEIGHT * (character - ' '))

#endif