/**
 * @file input.c
 * @author Academia Team
 * @brief Contains functions for handling input from IO interfaces.
 * 
 * @copyright Copyright Academia Team 2023
 */

#include <stddef.h>

#include "bool.h"
#include "input.h"
#include "ints.h"
#include "ikbdcode.h"
#include "scrn.h"
#include "super.h"
#include "types.h"
#include "vector.h"

#define DEFAULT_KYBD_CTRL_REG  0x96
#define DISABLE_KYBD_INTERRUPT 0x16

#define DEFAULT_MIDI_CTRL_REG  0x96
#define DISABLE_MIDI_INTERRUPT 0x16

#define KYBD_CHANNEL_LEV          6
#define KYBD_VECTOR              70

#define ALT_CODE               0x08
#define CAPS_CODE              0x10
#define CTRL_CODE              0x04
#define LSHIFT_CODE            0x02
#define RSHIFT_CODE            0x01

/**
 * @brief The number of pixels to move the mouse cursor when a mouse-changing
 * keyboard key is pressed.
 */
#define KEYBOARD_M_MOVE_DIST      8

/**
 * @brief The amount that the scancode is supposed to be shifted by before
 * adding to the keyboard buffer.
 */
#define SCANCODE_BUFFER_SHIFT_VAL 24

enum
{
	CAPS_IDLE     = 0,
	CAPS_PRESSED  = 1,
	CAPS_RELEASED = 2,
	CAPS_RESET    = 3
} capsState = CAPS_IDLE;

const UINT8 UNSHIFT_SCANCODE_TO_ASCII[SCANCODE_TO_ASCII_LEN] =
{
	0			/* Unutilized.*/,
	ESC_CHAR	/* 0x01 */,
	'1'			/* 0x02*/,
	'2'			/* 0x03 */,
	'3'			/* 0x04 */,
	'4'			/* 0x05 */,
	'5'			/* 0x06	*/,
	'6'			/* 0x07 */,
	'7'			/* 0x08 */,
	'8'			/* 0x09 */,
	'9'			/* 0x0A */,
	'0'			/* 0x0B */,
	'-'			/* 0x0C */,
	'='			/* 0x0D */,
	'\b'		/* 0x0E */,
	'	'		/* 0x0F */,
	'q'			/* 0x10 */,
	'w'			/* 0x11 */,
	'e'			/* 0x12 */,
	'r'			/* 0x13 */,
	't'			/* 0x14 */,
	'y'			/* 0x15 */,
	'u'			/* 0x16 */,
	'i'			/* 0x17 */,
	'o'			/* 0x18 */,
	'p'			/* 0x19 */,
	'['			/* 0x1A */,
	']'			/* 0x1B */,
	'\r'		/* 0x1C */,
	0			/* 0x1D */,
	'a'			/* 0x1E */,
	's'			/* 0x1F */,
	'd'			/* 0x20 */,
	'f'			/* 0x21 */,
	'g'			/* 0x22 */,
	'h'			/* 0x23 */,
	'j'			/* 0x24 */,
	'k'			/* 0x25 */,
	'l'			/* 0x26 */,
	';'			/* 0x27 */,
	'\''		/* 0x28 */,
	'`'			/* 0x29 */,
	0			/* 0x2A */,
	'\\'		/* 0x2B */,
	'z'			/* 0x2C */,
	'x'			/* 0x2D */,
	'c'			/* 0x2E */,
	'v'			/* 0x2F */,
	'b'			/* 0x30 */,
	'n'			/* 0x31 */,
	'm'			/* 0x32 */,
	','			/* 0x33 */,
	'.'			/* 0x34 */,
	'/'			/* 0x35 */,
	0			/* 0x36 */,
	0			/* Unutilized */,
	0			/* 0x38 */,
	' '			/* 0x39 */,
	0			/* 0x3A */,
	0			/* 0x3B */,
	0			/* 0x3C */,
	0			/* 0x3D */,
	0			/* 0x3E */,
	0			/* 0x3F */,
	0			/* 0x40 */,
	0			/* 0x41 */,
	0			/* 0x42 */,
	0			/* 0x43 */,
	0			/* 0x44 */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* 0x47 */,
	0			/* 0x48 */,
	0			/* Unutilized */,
	'-'			/* 0x4A */,
	0			/* 0x4B */,
	0			/* Unutilized */,
	0			/* 0x4D */,
	'+'			/* 0x4E */,
	0			/* Unutilized */,
	0			/* 0x50 */,
	0			/* Unutilized */,
	0			/* 0x52 */,
	DEL_CHAR	/* 0x53 */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Not present on US keyboard */,
	0			/* 0x61 */,
	0			/* 0x62 */,
	'('			/* 0x63 */,
	')'			/* 0x64 */,
	'/'			/* 0x65 */,
	'*'			/* 0x66 */,
	'7'			/* 0x67 */,
	'8'			/* 0x68 */,
	'9'			/* 0x69 */,
	'4'			/* 0x6A */,
	'5'			/* 0x6B */,
	'6'			/* 0x6C */,
	'1'			/* 0x6D */,
	'2'			/* 0x6E */,
	'3'			/* 0x6F */,
	'0'			/* 0x70 */,
	'.'			/* 0x71 */,
	'\r'		/* 0x72 */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */
};

const UINT8 SHIFT_SCANCODE_TO_ASCII[SCANCODE_TO_ASCII_LEN] =
{
	0			/* Non-existant*/,
	ESC_CHAR	/* 0x01 */,
	'!'			/* 0x02 */,
	'@'			/* 0x03 */,
	'#'			/* 0x04 */,
	'$'			/* 0x05 */,
	'%'			/* 0x06 */,
	'^'			/* 0x07 */,
	'&'			/* 0x08 */,
	'*'			/* 0x09 */,
	'('			/* 0x0A */,
	')'			/* 0x0B */,
	'_'			/* 0x0C */,
	'+'			/* 0x0D */,
	'\b'		/* 0x0E */,
	'	'		/* 0x0F */,
	'Q'			/* 0x10 */,
	'W'			/* 0x11 */,
	'E'			/* 0x12 */,
	'R'			/* 0x13 */,
	'T'			/* 0x14 */,
	'Y'			/* 0x15 */,
	'U'			/* 0x16 */,
	'I'			/* 0x17 */,
	'O'			/* 0x18 */,
	'P'			/* 0x19 */,
	'{'			/* 0x1A */,
	'}'			/* 0x1B */,
	'\r'		/* 0x1C */,
	0			/* 0x1D */,
	'A'			/* 0x1E */,
	'S'			/* 0x1F */,
	'D'			/* 0x20 */,
	'F'			/* 0x21 */,
	'G'			/* 0x22 */,
	'H'			/* 0x23 */,
	'J'			/* 0x24 */,
	'K'			/* 0x25 */,
	'L'			/* 0x26 */,
	':'			/* 0x27 */,
	'"'			/* 0x28 */,
	'`'			/* 0x29 */,
	0			/* 0x2A */,
	'|'			/* 0x2B */,
	'Z'			/* 0x2C */,
	'X'			/* 0x2D */,
	'C'			/* 0x2E */,
	'V'			/* 0x2F */,
	'B'			/* 0x30 */,
	'N'			/* 0x31 */,
	'M'			/* 0x32 */,
	'<'			/* 0x33 */,
	'>'			/* 0x34 */,
	'?'			/* 0x35 */,
	0			/* 0x36 */,
	0			/* Unutilized */,
	0			/* 0x38 */,
	' '			/* 0x39 */,
	0			/* 0x3A */,
	0			/* 0x3B */,
	0			/* 0x3C */,
	0			/* 0x3D */,
	0			/* 0x3E */,
	0			/* 0x3F */,
	0			/* 0x40 */,
	0			/* 0x41 */,
	0			/* 0x42 */,
	0			/* 0x43 */,
	0			/* 0x44 */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	'7'			/* 0x47 */,
	'8'			/* 0x48 */,
	0			/* Unutilized */,
	'-'			/* 0x4A */,
	'4'			/* 0x4B */,
	0			/* Unutilized */,
	'6'			/* 0x4D */,
	'+'			/* 0x4E */,
	0			/* Unutilized */,
	'2'			/* 0x50 */,
	0			/* Unutilized */,
	'0'			/* 0x52 */,
	DEL_CHAR	/* 0x53 */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Not present on US keyboard */,
	0			/* 0x61 */,
	0			/* 0x62 */,
	'('			/* 0x63 */,
	')'			/* 0x64 */,
	'/'			/* 0x65 */,
	'*'			/* 0x66 */,
	'7'			/* 0x67 */,
	'8'			/* 0x68 */,
	'9'			/* 0x69 */,
	'4'			/* 0x6A */,
	'5'			/* 0x6B */,
	'6'			/* 0x6C */,
	'1'			/* 0x6D */,
	'2'			/* 0x6E */,
	'3'			/* 0x6F */,
	'0'			/* 0x70 */,
	'.'			/* 0x71 */,
	'\r'		/* 0x72 */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */
};

const UINT8 CAPSLOCK_SCANCODE_TO_ASCII[SCANCODE_TO_ASCII_LEN] =
{
	0			/* Non-existant */,
	ESC_CHAR	/* 0x01 */,
	'1'			/* 0x02*/,
	'2'			/* 0x03 */,
	'3'			/* 0x04 */,
	'4'			/* 0x05 */,
	'5'			/* 0x06	*/,
	'6'			/* 0x07 */,
	'7'			/* 0x08 */,
	'8'			/* 0x09 */,
	'9'			/* 0x0A */,
	'0'			/* 0x0B */,
	'-'			/* 0x0C */,
	'='			/* 0x0D */,
	'\b'		/* 0x0E */,
	'	'		/* 0x0F */,
	'Q'			/* 0x10 */,
	'W'			/* 0x11 */,
	'E'			/* 0x12 */,
	'R'			/* 0x13 */,
	'T'			/* 0x14 */,
	'Y'			/* 0x15 */,
	'U'			/* 0x16 */,
	'I'			/* 0x17 */,
	'O'			/* 0x18 */,
	'P'			/* 0x19 */,
	'['			/* 0x1A */,
	']'			/* 0x1B */,
	'\r'		/* 0x1C */,
	0			/* 0x1D */,
	'A'			/* 0x1E */,
	'S'			/* 0x1F */,
	'D'			/* 0x20 */,
	'F'			/* 0x21 */,
	'G'			/* 0x22 */,
	'H'			/* 0x23 */,
	'J'			/* 0x24 */,
	'K'			/* 0x25 */,
	'L'			/* 0x26 */,
	';'			/* 0x27 */,
	'\''		/* 0x28 */,
	'`'			/* 0x29 */,
	0			/* 0x2A */,
	'\\'		/* 0x2B */,
	'Z'			/* 0x2C */,
	'X'			/* 0x2D */,
	'C'			/* 0x2E */,
	'V'			/* 0x2F */,
	'B'			/* 0x30 */,
	'N'			/* 0x31 */,
	'M'			/* 0x32 */,
	','			/* 0x33 */,
	'.'			/* 0x34 */,
	'/'			/* 0x35 */,
	0			/* 0x36 */,
	0			/* Unutilized */,
	0			/* 0x38 */,
	' '			/* 0x39 */,
	0			/* 0x3A */,
	0			/* 0x3B */,
	0			/* 0x3C */,
	0			/* 0x3D */,
	0			/* 0x3E */,
	0			/* 0x3F */,
	0			/* 0x40 */,
	0			/* 0x41 */,
	0			/* 0x42 */,
	0			/* 0x43 */,
	0			/* 0x44 */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* 0x47 */,
	0			/* 0x48 */,
	0			/* Unutilized */,
	'-'			/* 0x4A */,
	0			/* 0x4B */,
	0			/* Unutilized */,
	0			/* 0x4D */,
	'+'			/* 0x4E */,
	0			/* Unutilized */,
	0			/* 0x50 */,
	0			/* Unutilized */,
	0			/* 0x52 */,
	DEL_CHAR	/* 0x53 */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Not present on US keyboard */,
	0			/* 0x61 */,
	0			/* 0x62 */,
	'('			/* 0x63 */,
	')'			/* 0x64 */,
	'/'			/* 0x65 */,
	'*'			/* 0x66 */,
	'7'			/* 0x67 */,
	'8'			/* 0x68 */,
	'9'			/* 0x69 */,
	'4'			/* 0x6A */,
	'5'			/* 0x6B */,
	'6'			/* 0x6C */,
	'1'			/* 0x6D */,
	'2'			/* 0x6E */,
	'3'			/* 0x6F */,
	'0'			/* 0x70 */,
	'.'			/* 0x71 */,
	'\r'		/* 0x72 */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */
};

const UINT8 CTRL_SCANCODE_TO_ASCII[SCANCODE_TO_ASCII_LEN] =
{
	0			/* Non-existant */,
	ESC_CHAR	/* 0x01 */,
	DC1_CHAR	/* 0x02 */,
	0			/* 0x03 */,
	DC3_CHAR	/* 0x04 */,
	DC4_CHAR	/* 0x05 */,
	NAK_CHAR	/* 0x06 */,
	RS_CHAR		/* 0x07 */,
	ETB_CHAR	/* 0x08 */,
	CAN_CHAR	/* 0x09 */,
	EM_CHAR		/* 0x0A */,
	DLE_CHAR	/* 0x0B */,
	US_CHAR		/* 0x0C */,
	GS_CHAR		/* 0x0D */,
	'\b'		/* 0x0E */,
	'\t'		/* 0x0F */,
	DC1_CHAR	/* 0x10 */,
	ETB_CHAR	/* 0x11 */,
	ENQ_CHAR	/* 0x12 */,
	DC2_CHAR	/* 0x13 */,
	DC4_CHAR	/* 0x14 */,
	EM_CHAR		/* 0x15 */,
	NAK_CHAR	/* 0x16 */,
	'\t'		/* 0x17 */,
	SI_CHAR		/* 0x18 */,
	DLE_CHAR	/* 0x19 */,
	ESC_CHAR	/* 0x1A */,
	GS_CHAR		/* 0x1B */,
	'\n'		/* 0x1C */,
	0			/* 0x1D */,
	SOH_CHAR	/* 0x1E */,
	DC3_CHAR	/* 0x1F */,
	EOT_CHAR	/* 0x20 */,
	ACK_CHAR	/* 0x21 */,
	'\a'		/* 0x22 */,
	'\b'		/* 0x23 */,
	'\n'		/* 0x24 */,
	'\v'		/* 0x25 */,
	'\f'		/* 0x26 */,
	ESC_CHAR	/* 0x27 */,
	'\a'		/* 0x28 */,
	0			/* 0x29 */,
	0			/* 0x2A */,
	FS_CHAR		/* 0x2B */,
	SUB_CHAR	/* 0x2C */,
	CAN_CHAR	/* 0x2D */,
	ETX_CHAR	/* 0x2E */,
	SYN_CHAR	/* 0x2F */,
	STX_CHAR	/* 0x30 */,
	SO_CHAR		/* 0x31 */,
	'\r'		/* 0x32 */,
	'\f'		/* 0x33 */,
	SO_CHAR		/* 0x34 */,
	SI_CHAR		/* 0x35 */,
	0			/* 0x36 */,
	0			/* Unutilized */,
	0			/* 0x38 */,
	0			/* 0x39 */,
	0			/* 0x3A */,
	0			/* 0x3B */,
	0			/* 0x3C */,
	0			/* 0x3D */,
	0			/* 0x3E */,
	0			/* 0x3F */,
	0			/* 0x40 */,
	0			/* 0x41 */,
	0			/* 0x42 */,
	0			/* 0x43 */,
	0			/* 0x44 */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* 0x47 */,
	0			/* 0x48 */,
	0			/* Unutilized */,
	US_CHAR		/* 0x4A */,
	0			/* 0x4B */,
	0			/* Unutilized */,
	0			/* 0x4D */,
	'\v'		/* 0x4E */,
	0			/* Unutilized */,
	0			/* 0x50 */,
	0			/* Unutilized */,
	0			/* 0x52 */,
	US_CHAR		/* 0x53 */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Not present on US keyboard */,
	0			/* 0x61 */,
	0			/* 0x62 */,
	'\b'		/* 0x63 */,
	'\t'		/* 0x64 */,
	SI_CHAR		/* 0x65 */,
	'\n'		/* 0x66 */,
	ETB_CHAR	/* 0x67 */,
	CAN_CHAR	/* 0x68 */,
	EM_CHAR		/* 0x69 */,
	DC4_CHAR	/* 0x6A */,
	NAK_CHAR	/* 0x6B */,
	RS_CHAR		/* 0x6C */,
	DC1_CHAR	/* 0x6D */,
	0			/* 0x6E */,
	DC3_CHAR	/* 0x6F */,
	DLE_CHAR	/* 0x70 */,
	SO_CHAR		/* 0x71 */,
	'\n'		/* 0x72 */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */
};

const UINT8 ALT_SCANCODE_TO_ASCII[SCANCODE_TO_ASCII_LEN] =
{
	0			/* Non-existant */,
	ESC_CHAR	/* 0x01 */,
	0			/* 0x02 */,
	0			/* 0x03 */,
	0			/* 0x04 */,
	0			/* 0x05 */,
	0			/* 0x06 */,
	0			/* 0x07 */,
	0			/* 0x08 */,
	0			/* 0x09 */,
	0			/* 0x0A */,
	0			/* 0x0B */,
	0			/* 0x0C */,
	0			/* 0x0D */,
	'\b'		/* 0x0E */,
	'\t'		/* 0x0F */,
	0			/* 0x10 */,
	0			/* 0x11 */,
	0			/* 0x12 */,
	0			/* 0x13 */,
	0			/* 0x14 */,
	0			/* 0x15 */,
	0			/* 0x16 */,
	0			/* 0x17 */,
	0			/* 0x18 */,
	0			/* 0x19 */,
	'['			/* 0x1A */,
	']'			/* 0x1B */,
	'\r'		/* 0x1C */,
	0			/* 0x1D */,
	0			/* 0x1E */,
	0			/* 0x1F */,
	0			/* 0x20 */,
	0			/* 0x21 */,
	0			/* 0x22 */,
	0			/* 0x23 */,
	0			/* 0x24 */,
	0			/* 0x25 */,
	0			/* 0x26 */,
	';'			/* 0x27 */,
	'\''		/* 0x28 */,
	'`'			/* 0x29 */,
	0			/* 0x2A */,
	'\\'		/* 0x2B */,
	0			/* 0x2C */,
	0			/* 0x2D */,
	0			/* 0x2E */,
	0			/* 0x2F */,
	0			/* 0x30 */,
	0			/* 0x31 */,
	0			/* 0x32 */,
	','			/* 0x33 */,
	'.'			/* 0x34 */,
	'/'			/* 0x35 */,
	0			/* 0x36 */,
	0			/* Unutilized */,
	0			/* 0x38 */,
	' '			/* 0x39 */,
	0			/* 0x3A */,
	0			/* 0x3B */,
	0			/* 0x3C */,
	0			/* 0x3D */,
	0			/* 0x3E */,
	0			/* 0x3F */,
	0			/* 0x40 */,
	0			/* 0x41 */,
	0			/* 0x42 */,
	0			/* 0x43 */,
	0			/* 0x44 */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* 0x47 - Used to activate right mouse button */,
	0			/* 0x48 - Used to move the mouse cursor up */,
	0			/* Unutilized */,
	'-'			/* 0x4A */,
	0			/* 0x4B - Used to move the mouse cursor left */,
	0			/* Unutilized */,
	0			/* 0x4D - Used to move the mouse cursor right */,
	'+'			/* 0x4E */,
	0			/* Unutilized */,
	0			/* 0x50 - Used to move the mouse cursor down */,
	0			/* Unutilized */,
	0			/* 0x52 - Used to activate left mouse button */,
	DEL_CHAR	/* 0x53 */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Unutilized */,
	0			/* Not present on US keyboard */,
	0			/* 0x61 */,
	0			/* 0x62 - Used to do a screen print (not implemented) */,
	'('			/* 0x63 */,
	')'			/* 0x64 */,
	'/'			/* 0x65 */,
	'*'			/* 0x66 */,
	'7'			/* 0x67 */,
	'8'			/* 0x68 */,
	'9'			/* 0x69 */,
	'4'			/* 0x6A */,
	'5'			/* 0x6B */,
	'6'			/* 0x6C */,
	'1'			/* 0x6D */,
	'2'			/* 0x6E */,
	'3'			/* 0x6F */,
	'0'			/* 0x70 */,
	'.'			/* 0x71 */,
	'\r'		/* 0x72 */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */,
	0			/* Non-existant */
};

UINT32 kybdKeyBuffer[SIZE_KEY_BUFF] = {0};
UINT8  keyFindPos                   =  0;
UINT8  keyPlacePos                  =  0;

UINT8  kybdShiftBuffer              =  0;

const KybdTransTables DEFAULT_KYBD_TRANS_TABLES =
{
	UNSHIFT_SCANCODE_TO_ASCII, SHIFT_SCANCODE_TO_ASCII,
	CAPSLOCK_SCANCODE_TO_ASCII, CTRL_SCANCODE_TO_ASCII, ALT_SCANCODE_TO_ASCII
};

const KybdTransTables *currTransTables = &DEFAULT_KYBD_TRANS_TABLES;

Mouse mouse = {INITIAL_MOUSE_X, INITIAL_MOUSE_Y, FALSE, FALSE, FALSE};

void IKBD_isr(void);

Vector initKybd(void)
{
	const BOOL IS_SUPER = isSu();

	Vector sysKybdVec;
	UINT32 oldSsp;

	if (!IS_SUPER) oldSsp  = Su(0);
	mask_level_toggle(KYBD_CHANNEL_LEV);
	if (!IS_SUPER) Su(oldSsp);

	sysKybdVec = install_vector(KYBD_VECTOR, IKBD_isr);

	if (!IS_SUPER) oldSsp = Su(0);
	mask_level_toggle(KYBD_CHANNEL_LEV);
	if (!IS_SUPER) Su(oldSsp);

	return sysKybdVec;
}

void flushKybd(void)
{
	const BOOL IS_SUPER = isSu();

	int index;
	UINT32 oldSsp;

	if (!IS_SUPER) oldSsp = Su(0);
	mask_level_toggle(KYBD_CHANNEL_LEV);
	if (!IS_SUPER) Su(oldSsp);

	for (index = 0; index < SIZE_KEY_BUFF; index++)
	{
		kybdKeyBuffer[index] = 0;
	}

	kybdShiftBuffer = 0;
	keyFindPos      = 0;
	keyPlacePos     = 0;

	if (!IS_SUPER) oldSsp = Su(0);
	mask_level_toggle(KYBD_CHANNEL_LEV);
	if (!IS_SUPER) Su(oldSsp);
}

void restoreKybd(Vector sysKybdVec)
{
	install_vector(KYBD_VECTOR, sysKybdVec);
}

/**
 * @brief Adds a value to the shift buffer based on the given scancode.
 * @details If the scancode does not correspond to a key modifier, nothing will
 * happen.
 * 
 * @param scancode The scancode corresponding to a key modifier.
 */
void addToShiftBuffer(UINT16 scancode)
{
	switch(scancode)
	{
		case IKBD_CTRL_SCANCODE:
			kybdShiftBuffer ^= CTRL_CODE;
			break;
		case IKBD_ALT_SCANCODE:
			kybdShiftBuffer ^= ALT_CODE;
			break;
		case IKBD_LSHIFT_SCANCODE:
			kybdShiftBuffer ^= ALT_CODE;
			break;
		case IKBD_RSHIFT_SCANCODE:
			kybdShiftBuffer ^= RSHIFT_CODE;
			break;
		case IKBD_CAPS_SCANCODE:
			switch(capsState)
			{
				case CAPS_IDLE:
					capsState = CAPS_PRESSED;
					kybdShiftBuffer |= CAPS_CODE;
					break;
				case CAPS_PRESSED:
					capsState = CAPS_RELEASED;
					break;
				case CAPS_RELEASED:
					capsState = CAPS_RESET;
					kybdShiftBuffer ^= CAPS_CODE;
					break;
				case CAPS_RESET:
					capsState = CAPS_IDLE;
					break;
			}

			break;
	}
}

/**
 * @brief Adds the given scancode (with the corresponding ascii value) to the
 * key buffer.
 * @details If it is detected that placing a key will overwrite a key still
 * waiting to be read, the keyFindPos will be set to the next oldest key so that
 * newer inputs don't accidentally get used first.
 * 
 * @param scancode The code representing a key on a keyboard.
 */
void addToKeyBuffer(UINT16 scancode)
{
	if (kybdKeyBuffer[keyPlacePos] != 0)
	{
		keyFindPos++;
	}

	if (kybdShiftBuffer == CTRL_CODE)
	{
		kybdKeyBuffer[keyPlacePos] = currTransTables->ctrl[scancode];
	}
	else if (kybdShiftBuffer == ALT_CODE)
	{
		kybdKeyBuffer[keyPlacePos] = currTransTables->alt[scancode];
	}
	else if (kybdShiftBuffer == LSHIFT_CODE || kybdShiftBuffer == RSHIFT_CODE)
	{
		kybdKeyBuffer[keyPlacePos] = currTransTables->shift[scancode];
	}
	else if (kybdShiftBuffer == CAPS_CODE)
	{
		kybdKeyBuffer[keyPlacePos] = currTransTables->capslock[scancode];
	}
	else
	{
		kybdKeyBuffer[keyPlacePos] = currTransTables->unshift[scancode];
	}

	kybdKeyBuffer[keyPlacePos++] |= (UINT32)(scancode) <<
									SCANCODE_BUFFER_SHIFT_VAL;
}

UINT32 getKybdRaw(void)
{
	const BOOL IS_SUPER = isSu();

	long kybdVal;
	UINT32 oldSsp;

	if (!IS_SUPER) oldSsp = Su(0);
	mask_level_toggle(KYBD_CHANNEL_LEV);
	if (!IS_SUPER) Su(oldSsp);

	kybdVal = kybdKeyBuffer[keyFindPos];

	if (kybdVal)
	{
		kybdKeyBuffer[keyFindPos++] = 0;
	}

	if (!IS_SUPER) oldSsp = Su(0);
	mask_level_toggle(KYBD_CHANNEL_LEV);
	if (!IS_SUPER) Su(oldSsp);

	return kybdVal;
}

UINT32 getKybdBRaw(void)
{
	long kybdVal;

	do
	{
		kybdVal = getKybdRaw();
	} while (!kybdVal);

	return kybdVal;
}

UINT8 getAscii(void)
{
	return (UINT8)(getKybdRaw());
}

UINT8 getBAscii(void)
{
	UINT8 asciiVal;

	do
	{
		asciiVal = (UINT8)(getKybdBRaw());
	} while (!asciiVal);
	
	return asciiVal;
}

IKBD_Scancode getKey(void)
{
	long keyNum = getKybdRaw();

	if (!keyNum)
	{
		keyNum = NO_KEY;
	}
	else
	{
		keyNum >>= SCANCODE_BUFFER_SHIFT_VAL;
	}

	return (int)(keyNum);
}

IKBD_Scancode getBKey(void)
{
	return (int)(getKybdBRaw() >> SCANCODE_BUFFER_SHIFT_VAL);
}

/**
 * @brief Handles any special actions associated with the current combination
 * of scancode and key modifiers.
 * 
 * @param scancode The scancode to check for a special action.
 * @return TRUE if there is a special action associated with the given scancode;
 * FALSE otherwise.
 */
UINT8 handleSpecialAction(UINT16 scancode)
{
	UINT8 specialAction = FALSE;

	if (kybdShiftBuffer == ALT_CODE)
	{
		switch(scancode)
		{
			case IKBD_INSERT_SCANCODE:
				mouse.leftClick = TRUE;
				specialAction   = TRUE;

				break;
			case IKBD_CLHM_SCANCODE:
				mouse.rightClick = TRUE;
				specialAction    = TRUE;

				break;
			case IKBD_UP_SCANCODE:
				mouse.y -= KEYBOARD_M_MOVE_DIST;

				if (mouse.y < 0)
				{
					mouse.y = 0;
				}

				mouse.posChange = TRUE;
				specialAction   = TRUE;

				break;
			case IKBD_DOWN_SCANCODE:
				mouse.y += KEYBOARD_M_MOVE_DIST;

				if (mouse.y > SCRN_MAX_Y)
				{
					mouse.y = SCRN_MAX_Y;
				}

				mouse.posChange = TRUE;
				specialAction   = TRUE;

				break;
			case IKBD_LEFT_SCANCODE:
				mouse.x -= KEYBOARD_M_MOVE_DIST;

				if (mouse.x < 0)
				{
					mouse.x = 0;
				}

				mouse.posChange = TRUE;
				specialAction   = TRUE;

				break;
			case IKBD_RIGHT_SCANCODE:
				mouse.x += KEYBOARD_M_MOVE_DIST;

				if (mouse.x > SCRN_MAX_X)
				{
					mouse.x = SCRN_MAX_X;
				}

				mouse.posChange = TRUE;
				specialAction   = TRUE;

				break;
		}
	}

	return specialAction;
}

/**
 * @brief Returns whether the given scancode corresponds to a key modifier.
 * 
 * @param scancode The scancode to check.
 * @return TRUE if it is a key modifier; FALSE otherwise.
 */
UINT8 isKeyMod(UINT16 scancode)
{
	return (scancode == IKBD_LSHIFT_SCANCODE ||
			scancode == IKBD_RSHIFT_SCANCODE ||
			scancode == IKBD_ALT_SCANCODE    ||
			scancode == IKBD_CAPS_SCANCODE   ||
			scancode == IKBD_CTRL_SCANCODE);
}

BOOL mouseLclick(void)
{
	const BOOL IS_SUPER = isSu();

	BOOL mouseLclickStatus;
	UINT32 oldSsp;

	if (!IS_SUPER) oldSsp  = Su(0);
	mask_level_toggle(KYBD_CHANNEL_LEV);
	if (!IS_SUPER) Su(oldSsp);

	mouseLclickStatus = mouse.leftClick;
	mouse.leftClick = FALSE;

	if (!IS_SUPER) oldSsp = Su(0);
	mask_level_toggle(KYBD_CHANNEL_LEV);
	if (!IS_SUPER) Su(oldSsp);

	return mouseLclickStatus;
}

BOOL mouseRclick(void)
{
	const BOOL IS_SUPER = isSu();

	BOOL mouseRclickStatus;
	UINT32 oldSsp;

	if (!IS_SUPER) oldSsp  = Su(0);
	mask_level_toggle(KYBD_CHANNEL_LEV);
	if (!IS_SUPER) Su(oldSsp);

	mouseRclickStatus = mouse.rightClick;
	mouse.rightClick = FALSE;

	if (!IS_SUPER) oldSsp = Su(0);
	mask_level_toggle(KYBD_CHANNEL_LEV);
	if (!IS_SUPER) Su(oldSsp);

	return mouseRclickStatus;
}

BOOL mouseMoved(void)
{
	const BOOL IS_SUPER = isSu();

	BOOL mouseMovedStatus;
	UINT32 oldSsp;

	if (!IS_SUPER) oldSsp  = Su(0);
	mask_level_toggle(KYBD_CHANNEL_LEV);
	if (!IS_SUPER) Su(oldSsp);

	mouseMovedStatus = mouse.posChange;

	if (!IS_SUPER) oldSsp = Su(0);
	mask_level_toggle(KYBD_CHANNEL_LEV);
	if (!IS_SUPER) Su(oldSsp);

	return mouseMovedStatus;
}

void getMousePos(int *x, int *y)
{
	const BOOL IS_SUPER = isSu();
	UINT32 oldSsp;

	if (!IS_SUPER) oldSsp  = Su(0);
	mask_level_toggle(KYBD_CHANNEL_LEV);
	if (!IS_SUPER) Su(oldSsp);

	if (x != NULL)
	{
		*x = mouse.x;
	}

	if (y != NULL)
	{
		*y = mouse.y;
	}

	mouse.posChange = FALSE;

	if (!IS_SUPER) oldSsp = Su(0);
	mask_level_toggle(KYBD_CHANNEL_LEV);
	if (!IS_SUPER) Su(oldSsp);
}