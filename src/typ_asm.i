; Contains constants to assist in interacting with common types.
; 
; Copyright Academia Team 2023

; The value that needs to be used during a right bitshift to get the equivalent
; of a division by 8.
DIV_SHIFT_BY_8:		equ		3

; The value that needs to be used during a right bitshift to get the equivalent
; of a division by 16.
DIV_SHIFT_BY_16:	equ		4

; The value that needs to be used during a right bitshift to get the equivalent
; of a division by 32.
DIV_SHIFT_BY_32:	equ		5

UINT8_MAX:			equ		255
UINT8_MAX_DIGITS:	equ		3
UINT8_WIDTH:		equ		8
UINT8_BYTES:		equ		1


SINT8_MAX:			equ		127
SINT8_MAX_DIGITS:	equ		3
SINT8_WIDTH:		equ		8
SINT8_BYTES:		equ		1


UINT16_MAX:			equ		65535
UINT16_MAX_DIGITS:	equ		5
UINT16_WIDTH:		equ		16
UINT16_BYTES:		equ		2


SINT16_MAX:			equ		32767
SINT16_MAX_DIGITS:	equ		5
SINT16_WIDTH:		equ		16
SINT16_BYTES:		equ		2


UINT32_MAX:			equ		4294967295
UINT32_MAX_DIGITS:	equ		10
UINT32_WIDTH:		equ		32
UINT32_BYTES:		equ		4


SINT32_MAX:			equ		2147483647
SINT32_MAX_DIGITS:	equ		10
SINT32_WIDTH:		equ		32
SINT32_BYTES:		equ		4