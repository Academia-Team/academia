/**
 * @file mus_vbl.h
 * @author Academia Team
 * @brief Enables the VBL ISR to load a note automatically every time it runs.
 * 
 * @copyright Copyright Academia Team 2023
 */

#ifndef MUS_VBL_H
#define MUS_VBL_H

#include "bool.h"

/**
 * @brief Registers the music module with the VBL ISR.
 * 
 * @return TRUE if successful; FALSE otherwise.
 */
BOOL reg_music_vbl(void);

/**
 * @brief Removes registration of the music module from the VBL ISR.
 * 
 * @return TRUE if successful; FALSE otherwise.
 */
BOOL unreg_music_vbl(void);

#endif
