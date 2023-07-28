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

/**
 * @brief Set the CPU's interrupt mask to the given value.
 * 
 * @param mask The Interrupt Priority Level to set.
 * @return The old Interrupt Priority Level.
 */
short set_ipl(short mask);

/**
 * @brief Toggles masking for a specific device with the given priority level in
 * the MC68901.
 * 
 * @param channel A four bit value that specifies the device to be masked.
 */
void mask_level_toggle(short channel);

#endif
