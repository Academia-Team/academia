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
#include "ikbdcode.h"
#include "move.h"
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

/**
 * @brief The number of pixels to move the mouse cursor when a mouse-moving
 * keyboard key is pressed.
 */
#define KEYBOARD_M_MOVE_DIST 8

typedef struct
{
	const UINT8 *unshift;
	const UINT8 *shift;
	const UINT8 *capslock;
	const UINT8 *ctrl;
	const UINT8 *alt;
} KybdTransTables;

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
	UINT8 pos;
	UINT8 trigger;
} Joy;

extern Mouse     mouse;
extern Direction kybdMouseMov;
extern Joy       joy;

/**
 * @brief Checks if a left or right mouse click has happened with the given
 * mouse.
 * @details The mouse's click status will be reset after being checked.
 * 
 * @param mouse The mouse object to check for clicking.
 * @return TRUE if the mouse has been clicked; FALSE otherwise.
 */
#define mouseClick() (mouseLclick() || mouseRclick())

/**
 * @brief Empties all the keyboard buffers.
 */
void flushKybd(void);

/**
 * @brief Initializes everything required for the keyboard to work.
 * @details The MIDI device is disabled as part of the initialization, as it
 * can interfere with the operation of the keyboard.
 * @note Due to the way the Atari ST is set up, it will also setup the mouse.
 * @return The original keyboard ISR.
 */
Vector initKybd(void);

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
UINT32 getKybdRaw(void);

/**
 * @brief Returns a value from the keyboard.
 * @details It does block for input.
 * 
 * @return A 32-bit number where the bottom 8-bits is the ASCII code
 * corresponding to a key that was pressed and the bits 16-23 correspond to the
 * physical location of the key on the keyboard (the scancode). All other bits
 * are guaranteed to be zero.
 */
UINT32 getKybdBRaw(void);

/**
 * @brief Retrieves an ascii value corresponding to a key that was pressed.
 * 
 * @return The ascii value of a pressed key (or zero if no key was pressed or
 * there is no corresponding ascii value).
 */
UINT8 getAscii(void);

/**
 * @brief Retrieves an ascii value corresponding to a key that was pressed.
 * @details It blocks while awaiting input. If a key is pressed that does not
 * correspond to an ASCII value, then it will continue to block.
 * 
 * @return The ascii value of a pressed key.
 */
UINT8 getBAscii(void);

/**
 * @brief Gets a number representing a location of a pressed key on the keyboard
 * without blocking anything.
 * 
 * @return A 16-bit number with the lower 8-bits representing a key on the
 * keyboard if a key was pressed. Otherwise, a negative integral 16-bit number
 * will be returned (NO_KEY).
 */
IKBD_Scancode getKey(void);

/**
 * @brief Gets a number representing a location of a pressed key on the
 * keyboard.
 * @details It blocks while awaiting input.
 * 
 * @return A 16-bit number with the lower 8-bits representing a key on the
 * keyboard if a key was pressed. Otherwise, a negative integral 16-bit number
 * will be returned (NO_KEY).
 */
IKBD_Scancode getBKey(void);

/**
 * @brief Returns if a key is being pressed or not.
 * 
 * @return TRUE if a key is being pressed; FALSE otherwise.
 */
UINT8 keyPressed(void);

/**
 * @brief Checks if a left mouse click has happened.
 * @details The mouse's left click status will be reset after being checked.
 * 
 * @return TRUE if the mouse has been clicked; FALSE otherwise.
 */
BOOL mouseLclick(void);

/**
 * @brief Checks if a right mouse click has happened.
 * @details The mouse's right click status will be reset after being checked.
 * 
 * @return TRUE if the mouse has been clicked; FALSE otherwise.
 */
BOOL mouseRclick(void);

/**
 * @brief Checks if the mouse has moved since last getting the position of it.
 * @details Once the mouse has been moved, the subroutine will always indicate
 * the mouse has moved until the actual values have been read.
 * 
 * @return TRUE if the mouse has been moved; FALSE otherwise.
 */
BOOL mouseMoved(void);

/**
 * @brief Returns the mouse's current position by reference.
 * @details The boolean specifying if movement has occurred will be reset.
 * 
 * @param x Returns the current x position of the mouse.
 * @param y Returns the current y position of the mouse.
 */
void getMousePos(int *x, int *y);

/**
 * @brief Sets the mouse position to the provided coordinates.
 * 
 * @param x The desired x position of the mouse.
 * @param y The desired y position of the mouse.
 * @return TRUE if the coordinates are valid; FALSE otherwise.
 */
BOOL setMousePos(int x, int y);

/**
 * @brief Adjusts the mouse position by the provided x and y deltas.
 * @details If the resultant coordinates are out of range, they will be modified
 * to their closest valid values.
 * 
 * @param deltaX The desired adjustment of the x position of the mouse.
 * @param deltaY The desired adjustment of the y position of the mouse.
 */
void setRelMousePos(int deltaX, int deltaY);

/**
 * @brief Returns the joystick's current position.
 * 
 * @return The position of the joystick.
 */
UINT8 getJoyPos(void);

/**
 * @brief Checks if a button on a joystick has been pressed.
 * @details The joystick's button status will be reset after being checked.
 * 
 * @return TRUE if a joystick button has been pressed; FALSE otherwise.
 */
BOOL joyButtonPressed(void);

#endif
