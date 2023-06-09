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

#define VBL_VECTOR 28

/**
 * @brief Stops the VBL ISR from showing a cursor on the screen.
 * @details Any remaining cursors on screen will be erased.
 */
void hide_cursor();

/**
 * @brief Causes the VBL to replot the cursor to the screen.
 * @details All previous cursors will be cleared.
 */
#define reset_cursor() \
	hide_cursor(); \
	show_cursor()

/**
 * @brief Allows the VBL ISR to show a cursor on the screen.
 */
void show_cursor();

/**
 * @brief Temporarily pauses any game-related operations.
 */
#define game_pause() game_end()

/**
 * @brief Resumes any game-related operations.
 */
#define game_resume() game_start()

/**
 * @brief Handles the cleanup after a game ends.
 */
void game_end();

/**
 * @brief Sets the appropriate values for the start of a game.
 */
void game_start();

/**
 * @brief Returns the current time provided by the VBL clock.
 * 
 * @return The current VBL clock value as a UINT32.
 */
UINT32 get_time();

/**
 * @brief Checks to see if it is okay to render to the screen.
 * @details It is only okay to render to the screen if and only if a vertical
 * blank has occurred.
 * 
 * @return TRUE if it is safe; FALSE otherwise.
 */
BOOL rend_req();

/**
 * @brief Manages all timed events and music.
 */
void vbl_isr();

/**
 * @brief Blocks processing until a vertical sync has occurred.
 */
void vert_sync();

#endif
