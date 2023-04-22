/**
 * @file ints.h
 * @author Academia Team
 * @brief Contains functions designed to allow for the disabling and enabling of
 * different hardware interrupts.
 * 
 * @copyright Copyright Academia Team 2023
 */

#ifndef INTS_H
#define INTS_H

#include "types.h"

#define MASK_ALL_INTERRUPTS 07

/* sets IPL = mask, returns old IPL (interrupt priority level) */
int set_ipl(int mask); /* must be called from supervisor mode */

/**
 * @brief Toggles masking for a specific device with the given priority level in
 * the MC68901.
 * 
 * @param channel A four bit value that specifies the device to be masked.
 * @note Requires super privileges.
 */
void mask_level_toggle(int channel);

#endif
