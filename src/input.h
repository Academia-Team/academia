/**
 * @file input.h
 * @author Academia Team
 * @brief Contains functions for handling input from IO interfaces.
 * 
 * @copyright Copyright Academia Team 2023
 */

#ifndef INPUT_H
#define INPUT_H

#include "bool.h"
#include "scrn.h"
#include "types.h"
#include "vector.h"

/**
 * @brief The number of keys that can be stored within the key buffer.
 */
#define SIZE_KEY_BUFF 256

/**
 * @brief An integral constant representing the lack of a key press.
 */
#define NO_KEY -1

#define ESC_CHAR 0x1B
#define DEL_CHAR 0x7F
#define DC1_CHAR 0x11
#define DC2_CHAR 0x12
#define DC3_CHAR 0x13
#define DC4_CHAR 0x14
#define NAK_CHAR 0x15
#define RS_CHAR 0x1E
#define ETB_CHAR 0x17
#define CAN_CHAR 0x18
#define EM_CHAR 0x19
#define DLE_CHAR 0x10
#define US_CHAR	0x1F
#define GS_CHAR 0x1D
#define ENQ_CHAR 0x05
#define SI_CHAR 0x0F
#define SOH_CHAR 0x01
#define EOT_CHAR 0x04
#define ACK_CHAR 0x06
#define FS_CHAR 0x1C
#define SUB_CHAR 0x1A
#define ETX_CHAR 0x03
#define SYN_CHAR 0x16
#define STX_CHAR 0x02
#define SO_CHAR 0x0E

#define SCANCODE_TO_ASCII_LEN 128

#define MAX_SCANCODE_VAL 0x72

#define INITIAL_MOUSE_X SCRN_MID_X
#define INITIAL_MOUSE_Y SCRN_MID_Y

typedef struct
{
	int  x;
	int  y;
	BOOL leftClick;
	BOOL rightClick;
	BOOL posChange;
} Mouse;

typedef struct
{
	const UINT8 *unshift;
	const UINT8 *shift;
	const UINT8 *capslock;
	const UINT8 *ctrl;
	const UINT8 *alt;
} KybdTransTables;

extern Mouse mouse;

/**
 * @brief Checks if a left or right mouse click has happened with the given
 * mouse.
 * @details The mouse's click status will be reset after being checked.
 * 
 * @param mouse The mouse object to check for clicking.
 * @return TRUE if the mouse has been clicked; FALSE otherwise.
 */
#define mouseClick(mouse) (mouseLclick(&mouse) || mouseRclick(&mouse))

/**
 * @brief Disables any interrupts coming from the MIDI.
 */
void disableMidiInterrupt();

/**
 * @brief Enables any interrupts coming from the MIDI.
 */
void enableMidiInterrupt();

/**
 * @brief Empties all the keyboard buffers.
 */
void flushKybd();

/**
 * @brief Initializes everything required for the keyboard to work.
 * @details The MIDI device is disabled as part of the initialization, as it
 * can interfere with the operation of the keyboard.
 * @note Due to the way the Atari ST is set up, it will also setup the mouse.
 * @return The original keyboard ISR.
 */
Vector initKybd();

/**
 * @brief Restores the keyboard back to the way it was before.
 * 
 * @param sysKybdVec The original keyboard ISR.
 */
void restoreKybd(Vector sysKybdVec);

/**
 * @brief Returns a value from the keyboard.
 * @details It does not block for input.
 * 
 * @return A 32-bit number where the bottom 8-bits is the ASCII code
 * corresponding to a key that was pressed and the bits 16-23 correspond to the
 * physical location of the key on the keyboard (the scancode). All other bits
 * are guaranteed to be zero.
 */
UINT32 getKybdRaw();

/**
 * @brief Retrieves an ascii value corresponding to a key that was pressed.
 * 
 * @return The ascii value of a pressed key (or zero if no key was pressed or
 * there is no corresponding ascii value).
 */
UINT8 getAscii();

/**
 * @brief Gets a number representing a location of a pressed key on the keyboard
 * without blocking anything.
 * 
 * @return A 16-bit number with the lower 8-bits representing a key on the
 * keyboard if a key was pressed. Otherwise, a negative integral 16-bit number
 * will be returned (NO_KEY).
 */
int getKey();

/**
 * @brief Checks if a left mouse click has happened with the given
 * mouse.
 * @details The mouse's left click status will be reset after being checked.
 * 
 * @param mouse The mouse object to check for clicking.
 * @return TRUE if the mouse has been clicked; FALSE otherwise.
 */
BOOL mouseLclick(Mouse * const mouse);

/**
 * @brief Checks if a right mouse click has happened with the given
 * mouse.
 * @details The mouse's right click status will be reset after being checked.
 * 
 * @param mouse The mouse object to check for clicking.
 * @return TRUE if the mouse has been clicked; FALSE otherwise.
 */
BOOL mouseRclick(Mouse * const mouse);

/**
 * @brief Checks if the given mouse has moved since last getting the position of
 * it.
 * @details Once the mouse has been moved, the subroutine will always indicate
 * the mouse has moved until the actual values have been read.
 * 
 * @param mouse The mouse to check the movement of.
 * @return TRUE if the mouse has been moved; FALSE otherwise.
 */
BOOL mouseMoved(const Mouse * const mouse);

/**
 * @brief Returns the given mouse's current position by reference.
 * @details The boolean specifying if movement has occurred will be reset.
 * 
 * @param mouse The mouse to get the position of.
 * @param x Returns the current x position of the mouse.
 * @param y Returns the current y position of the mouse.
 */
void getMousePos(Mouse const *mouse, int *x, int *y);

#endif
