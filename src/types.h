/**
 * @file types.h
 * @author Academia Team
 * @brief Contains aliases and constants to assist in interacting with common
 * types.
 * 
 * @copyright Copyright Academia Team 2023
 */

#ifndef TYPES_H
#define TYPES_H

/**
 * @brief The value that needs to be used during a right bitshift to get the
 * equivalent of a division by 8.
 */
#define DIV_SHIFT_BY_8 3

/**
 * @brief The value that needs to be used during a right bitshift to get the
 * equivalent of a division by 16.
 */
#define DIV_SHIFT_BY_16 4

/**
 * @brief The value that needs to be used during a right bitshift to get the
 * equivalent of a division by 32.
 */
#define DIV_SHIFT_BY_32 5

#ifndef UINT8_MAX
#define UINT8_MAX 255
#endif

#define UINT8_MAX_DIGITS 3

#ifndef UINT8_WIDTH
#define UINT8_WIDTH 8
#endif

#define UINT8_BYTES 1

typedef unsigned char UINT8;


#ifndef UINT16_MAX
#define UINT16_MAX 65535U
#endif

#define UINT16_MAX_DIGITS 5

#ifndef UINT16_WIDTH
#define UINT16_WIDTH 16
#endif

#define UINT16_BYTES 2

typedef unsigned short UINT16;


#ifndef UINT32_MAX
#define UINT32_MAX 4294967295UL
#endif

#define UINT32_MAX_DIGITS 10

#ifndef UINT32_WIDTH
#define UINT32_WIDTH 32
#endif

#define UINT32_BYTES 4

typedef unsigned long UINT32;

#endif
