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

#define UINT8_MAX   255
#define UINT8_WIDTH   8
typedef unsigned char UINT8;

#define UINT16_MAX   65535
#define UINT16_WIDTH    16
typedef unsigned int  UINT16;

#define UINT32_MAX   4294967295
#define UINT32_WIDTH         32
typedef unsigned long UINT32;

#endif
