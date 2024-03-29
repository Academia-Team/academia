/**
 * @file ikbdcode.h
 * @author Academia Team
 * @brief Provides named constants for the IKBD scancodes.
 * 
 * @copyright Copyright Academia Team 2023
 */

#ifndef IKBDCODE_H
#define IKBDCODE_H

typedef enum
{
	IKBD_RESERVED_SCANCODE   = 0x00,
	IKBD_ESC_SCANCODE        = 0x01,
	IKBD_1_SCANCODE          = 0x02,
	IKBD_2_SCANCODE          = 0x03,
	IKBD_3_SCANCODE          = 0x04,
	IKBD_4_SCANCODE          = 0x05,
	IKBD_5_SCANCODE          = 0x06,
	IKBD_6_SCANCODE          = 0x07,
	IKBD_7_SCANCODE          = 0x08,
	IKBD_8_SCANCODE          = 0x09,
	IKBD_9_SCANCODE          = 0x0A,
	IKBD_0_SCANCODE          = 0x0B,
	IKBD_DASH_SCANCODE       = 0x0C,
	IKBD_EQUALS_SCANCODE     = 0x0D,
	IKBD_BSPACE_SCANCODE     = 0x0E,
	IKBD_TAB_SCANCODE        = 0x0F,
	IKBD_Q_SCANCODE          = 0x10,
	IKBD_W_SCANCODE          = 0x11,
	IKBD_E_SCANCODE          = 0x12,
	IKBD_R_SCANCODE          = 0x13,
	IKBD_T_SCANCODE          = 0x14,
	IKBD_Y_SCANCODE          = 0x15,
	IKBD_U_SCANCODE          = 0x16,
	IKBD_I_SCANCODE          = 0x17,
	IKBD_O_SCANCODE          = 0x18,
	IKBD_P_SCANCODE          = 0x19,
	IKBD_LBRACKET_SCANCODE   = 0x1A,
	IKBD_RBRACKET_SCANCODE   = 0x1B,
	IKBD_RETURN_SCANCODE     = 0x1C,
	IKBD_CTRL_SCANCODE       = 0x1D,
	IKBD_A_SCANCODE          = 0x1E,
	IKBD_S_SCANCODE          = 0x1F,
	IKBD_D_SCANCODE          = 0x20,
	IKBD_F_SCANCODE          = 0x21,
	IKBD_G_SCANCODE          = 0x22,
	IKBD_H_SCANCODE          = 0x23,
	IKBD_J_SCANCODE          = 0x24,
	IKBD_K_SCANCODE          = 0x25,
	IKBD_L_SCANCODE          = 0x26,
	IKBD_SEMICOLON_SCANCODE  = 0x27,
	IKBD_APOSTROPHE_SCANCODE = 0x28,
	IKBD_BTICK_SCANCODE      = 0x29,
	IKBD_LSHIFT_SCANCODE     = 0x2A,
	IKBD_BSLASH_SCANCODE     = 0x2B,
	IKBD_Z_SCANCODE          = 0x2C,
	IKBD_X_SCANCODE          = 0x2D,
	IKBD_C_SCANCODE          = 0x2E,
	IKBD_V_SCANCODE          = 0x2F,
	IKBD_B_SCANCODE          = 0x30,
	IKBD_N_SCANCODE          = 0x31,
	IKBD_M_SCANCODE          = 0x32,
	IKBD_COMMA_SCANCODE      = 0x33,
	IKBD_PERIOD_SCANCODE     = 0x34,
	IKBD_SLASH_SCANCODE      = 0x35,
	IKBD_RSHIFT_SCANCODE     = 0x36,
	IKBD_ALT_SCANCODE        = 0x38,
	IKBD_SPACE_SCANCODE      = 0x39,
	IKBD_CAPS_SCANCODE       = 0x3A,
	IKBD_F1_SCANCODE         = 0x3B,
	IKBD_F2_SCANCODE         = 0x3C,
	IKBD_F3_SCANCODE         = 0x3D,
	IKBD_F4_SCANCODE         = 0x3E,
	IKBD_F5_SCANCODE         = 0x3F,
	IKBD_F6_SCANCODE         = 0x40,
	IKBD_F7_SCANCODE         = 0x41,
	IKBD_F8_SCANCODE         = 0x42,
	IKBD_F9_SCANCODE         = 0x43,
	IKBD_F10_SCANCODE        = 0x44,
	IKBD_CLHM_SCANCODE       = 0x47,
	IKBD_UP_SCANCODE         = 0x48,
	IKBD_KP_EQUALS_SCANCODE  = 0x4A,
	IKBD_LEFT_SCANCODE       = 0x4B,
	IKBD_RIGHT_SCANCODE      = 0x4D,
	IKBD_KP_PLUS             = 0x4E,
	IKBD_DOWN_SCANCODE       = 0x50,
	IKBD_INSERT_SCANCODE     = 0x52,
	IKBD_DELETE_SCANCODE     = 0x53,
	IKBD_UNDO_SCANCODE       = 0x61,
	IKBD_HELP_SCANCODE       = 0x62,
	IKBD_KP_LPAREN_SCANCODE  = 0x63,
	IKBD_KP_RPAREN_SCANCODE  = 0x64,
	IKBD_KP_SLASH_SCANCODE   = 0x65,
	IKBD_KP_STAR_SCANCODE    = 0x66,
	IKBD_KP_7_SCANCODE       = 0x67,
	IKBD_KP_8_SCANCODE       = 0x68,
	IKBD_KP_9_SCANCODE       = 0x69,
	IKBD_KP_4_SCANCODE       = 0x6A,
	IKBD_KP_5_SCANCODE       = 0x6B,
	IKBD_KP_6_SCANCODE       = 0x6C,
	IKBD_KP_1_SCANCODE       = 0x6D,
	IKBD_KP_2_SCANCODE       = 0x6E,
	IKBD_KP_3_SCANCODE       = 0x6F,
	IKBD_KP_0_SCANCODE       = 0x70,
	IKBD_KP_PERIOD_SCANCODE  = 0x71,
	IKBD_KP_ENTER_SCANCODE   = 0x72
} IKBD_Scancode;

#endif
