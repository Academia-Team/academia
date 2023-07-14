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

#define FONT16_NUM_CHARS  95
#define FONT16_HEIGHT     16
#define FONT16_WIDTH      16
#define FONT16_BYTE_SIZE 256

/**
 * @brief Returns the address of the font16 bitmap corresponding to the given
 * digit.
 * @details The bitmap is copied to the dest memory location unless the
 * provided digit is out of range or the destination is NULL.
 * 
 * @param digit The digit to get the font16 character of. Must be between 0 and
 * 9.
 * @param dest The pointer to copy the font16 character bitmap to.
 * @return The address of the font16 bitmap corresponding to the given digit or
 * NULL if the provided digit is out of range.
 */
const UINT16 *getFont16Digit(int digit, UINT16 *dest);

/**
 * @brief Returns the address of the font16 bitmap corresponding to the given
 * ascii character.
 * @details The bitmap is copied to the dest memory location unless the
 * provided character is out of range or the destination is NULL.
 * 
 * @param digit The printable ascii character to get the font16 character of.
 * Extended ASCII characters are not supported.
 * @param dest The pointer to copy the font16 character bitmap to.
 * @return The address of the font16 bitmap corresponding to the given
 * printable ascii character or NULL if the character is not printable or
 * ASCII.
 */
const UINT16 *getFont16Char(char character, UINT16 *dest);

#endif