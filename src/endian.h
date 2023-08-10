/**
 * @file endian.h
 * @author Academia Team
 * @brief Contains macros and constants to assist in handling the differences
 * between big and little endianness.
 * 
 * @copyright Copyright Academia Team 2023
 */

#ifndef ENDIAN_H
#define ENDIAN_H

#include "types.h"

#define swap16(value) (((UINT16)(value) << 8) | ((UINT16)(value) >> 8))

#define swap32(value) \
	( \
		( \
			((UINT32)(value) << 24) | (((UINT32)(value) << 8) & 0x00FF0000) \
		) | \
		( \
			(((UINT32)(value) >> 8) & 0x0000FF00) | ((UINT32)(value) >> 24) \
		) \
	)

#define B_ENDIAN

#ifdef L_ENDIAN
#define swap16OnBE(value) (value)
#define swap32OnBE(value) (value)

#define swap16OnLE(value) swap16(value)
#define swap32OnLE(value) swap32(value)
#else
#define swap16OnBE(value) swap16(value)
#define swap32OnBE(value) swap32(value)

#define swap16OnLE(value) (value)
#define swap32OnLE(value) (value)
#endif

#endif