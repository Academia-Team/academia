/**
 * @file in_vbl.h
 * @author Academia Team
 * @brief Enables the VBL ISR to manage displaying a cursor on the screen.
 * 
 * @copyright Copyright Academia Team 2023
 */

#ifndef IN_VBL_H
#define IN_VBL_H

/**
 * @brief Stops the VBL ISR from showing a cursor on the screen.
 * @details Any remaining cursors on screen will be erased.
 */
void hide_cursor(void);

/**
 * @brief Causes the VBL ISR to replot the cursor to the screen.
 * @details All previous cursors will be cleared.
 */
#define reset_cursor() \
	hide_cursor(); \
	show_cursor()

/**
 * @brief Allows the VBL ISR to show a cursor on the screen.
 */
void show_cursor(void);

#endif
