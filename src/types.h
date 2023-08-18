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


#ifndef SINT8_MAX
#define SINT8_MAX 127
#endif

#define SINT8_MAX_DIGITS 3

#ifndef SINT8_WIDTH
#define SINT8_WIDTH 8
#endif

#define SINT8_BYTES 1

typedef signed char SINT8;


#ifndef UINT16_MAX
#define UINT16_MAX 65535U
#endif

#define UINT16_MAX_DIGITS 5

#ifndef UINT16_WIDTH
#define UINT16_WIDTH 16
#endif

#define UINT16_BYTES 2

typedef unsigned short UINT16;


#ifndef SINT16_MAX
#define SINT16_MAX 32767
#endif

#define SINT16_MAX_DIGITS 5

#ifndef SINT16_WIDTH
#define SINT16_WIDTH 16
#endif

#define SINT16_BYTES 2

typedef signed short SINT16;


#ifndef UINT32_MAX
#define UINT32_MAX 4294967295UL
#endif

#define UINT32_MAX_DIGITS 10

#ifndef UINT32_WIDTH
#define UINT32_WIDTH 32
#endif

#define UINT32_BYTES 4

typedef unsigned long UINT32;


#ifndef SINT32_MAX
#define SINT32_MAX 2147483647L
#endif

#define SINT32_MAX_DIGITS 10

#ifndef SINT32_WIDTH
#define SINT32_WIDTH 32
#endif

#define SINT32_BYTES 4

typedef signed long SINT32;

#endif
