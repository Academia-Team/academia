/**
 * @file vbl.h
 * @author Academia Team
 * @brief Manages the Vertical Blank ISR.
 * 
 * @copyright Copyright 2023 Academia Team
 */

#ifndef VBL_H
#define VBL_H

#include "bool.h"
#include "types.h"
#include "vector.h"

#define MAX_REGISTERED_VBL_FUNCS 12

#define VBL_VECTOR 28

/**
 * @brief Returns the current time provided by the VBL clock.
 * 
 * @return The current VBL clock value as a UINT32.
 */
UINT32 get_time(void);

/**
 * @brief Checks to see if it is okay to render to the screen.
 * @details It is only okay to render to the screen if and only if a vertical
 * blank has occurred.
 * 
 * @return TRUE if it is safe; FALSE otherwise.
 */
BOOL rend_req(void);

/**
 * @brief The function that handles the core VBL functionality and runs the
 * desired registered functions.
 */
void vbl_main(void);

/**
 * @brief Sets up the VBL ISR.
 * 
 * @return The original VBL ISR vector.
 */
Vector vbl_init(void);

/**
 * @brief Executes vbl_main() every time the vertical blank clock interrupts.
 */
void vbl_isr(void);

/**
 * @brief Register a function to be run while the VBL ISR runs.
 * @details The functions will be run in the order that they are defined.
 * 
 * @param func The function to set to run during the VBL ISR.
 * @return TRUE if the function was successfully registered; FALSE otherwise.
 */
BOOL vbl_register(void (*func)(void));

/**
 * @brief Restores the given VBL ISR vector.
 * 
 * @param sysVblVec The vector to restore.
 */
void vbl_restore(Vector sysVblVec);

/**
 * @brief Removes a function from being run while the VBL ISR runs.
 * 
 * @param func The function that should be removed.
 * @return TRUE if the function was found and removed; FALSE otherwise.
 */
BOOL vbl_unregister(void (*func)(void));

/**
 * @brief Blocks processing until a vertical sync has occurred.
 */
void vert_sync(void);

#endif
