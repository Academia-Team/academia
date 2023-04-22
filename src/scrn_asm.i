 ; Contains convenience macros corresponding to the size and the
 ; different positions on the Atari ST's screen.
 ;
 ; Copyright Academia Team 2023

; The horizontal length of the Atari ST's monochrome screen (in pixels).
SCRN_LEN:			equ 	640

; The height of the Atari ST's monochrome screen (in pixels).
SCRN_HEIGHT:		equ		400

; The number of pixels in an Atari ST's monochrome screen.
SCRN_SIZE: 			equ		256000

; The number of bytes in an Atari ST's monochrome screen.
SCRN_BYTES:			equ 	32000

; The number of words in an Atari ST's monochrome screen.
SCRN_WORDS:			equ	 	16000

; The number of longs in an Atari ST's monochrome screen.
SCRN_LONGS:			equ		8000


; The horizontal length of the Atari ST's monochrome screen (in 8-bit
; bytes).
SCRN_LEN_BYTES:		equ		80

; The horizontal length of the Atari ST's monochrome screen (in 16-bit
; words).
SCRN_LEN_WORDS:		equ		40

; The horizontal length of the Atari ST's monochrome screen (in 32-bit
; long words).
SCRN_LEN_LONG:		equ		20


; The maximum value for the x coordinate (in pixels) such that any point
; plotted in that x coordinate and a valid y coordinate will be visible on the
; Atari ST's monochrome screen.
SCRN_MAX_X:			equ		639

; The maximum value for the y coordinate (in pixels) such that any point
; plotted in that y coordinate and a valid x coordinate will be visible on the
; Atari ST's monochrome screen.
SCRN_MAX_Y:			equ		399


; The value for the x coordinate (in pixels) that corresponds to the
; middle point on the Atari ST's monochrome screen.
SCRN_MID_X:			equ 	319

 ; The value for the y coordinate (in pixels) that corresponds to the
 ; middle point on the Atari ST's monochrome screen.
SCRN_MID_Y:			equ 	199