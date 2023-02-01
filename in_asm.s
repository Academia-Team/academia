; Contains subroutines for handling input from IO interfaces.
; 
; Copyright Academia Team 2023

						include	bool_asm.i
						include ints.i
						include mouse.i
						include scrn_asm.i

						xdef	_IKBD_isr
						xdef	_mouseLclick
						xdef	_mouseRclick
						xdef	_mouseMoved
						xdef	_getMousePos

						xref	_addToKeyBuffer
						xref	_kybdShiftBuffer

IKBD_STATUS_REG:		equ		$FFFFFC00
IKBD_RDR_REG:			equ		$FFFFFC02
RDRF_BIT:				equ		0
IKBD_BREAK_BIT:			equ		7

IKBD_MIN_MOUSE_PKT_VAL:	equ		$F8
IKBD_RCLICK_BIT:		equ		0
IKBD_LCLICK_BIT:		equ		1

IKBD_CAPS_KEY:			equ		$3A
IKBD_CAPS_BITMASK:		equ		$10

IKBD_CTRL_KEY:			equ		$1D
IKBD_CTRL_BITMASK:		equ		$04

IKBD_ALT_KEY:			equ		$38
IKBD_ALT_BITMASK:		equ		$08

IKBD_LSHIFT_KEY:		equ		$2A
IKBD_LSHIFT_BITMASK:	equ		$02

IKBD_RSHIFT_KEY:		equ		$36
IKBD_RSHIFT_BITMASK:	equ		$01

IKBD_CHANNEL_LEV:		equ		6

MFP_IN_SERVICE_B_REG:	equ		$FFFFFA11


; void IKBD_isr()
;
; Brief: Handles keyboard and mouse input.
;
; Register Table:
; ---------------
; d0	-	Holds the value recieved by the keyboard.
; a0	-	Holds the keyboard status register for reading.
; a2	-	Holds the address of the receiver register of the keyboard.
; a3	-	Holds the address of the mouse struct.
_IKBD_isr:				movem.l	d0-d7/a0-a6,-(sp)

						; If the keyboard doesn't have anything in its buffer,
						; get out of dodge.
						movea.l	#IKBD_STATUS_REG,a0
						btst.b	#RDRF_BIT,(a0)
						beq		IKBD_RETURN

						; Get the value held by the keyboard.
						clr.l	d0
						movea.l	#IKBD_RDR_REG,a2
						move.b	(a2),d0

						; Check if a mouse packet has previously been received.
						; If no mouse packets have been processed before, check
						; for a mouse header packet.
						tst.b	mouse_packets_received
						beq		IKBD_CHK_MOUSE_HEADER
						addq.b	#1,mouse_packets_received
						cmpi.b	#2,mouse_packets_received
						beq		IKBD_SECOND_M_PKT
						cmpi.b	#3,mouse_packets_received
						beq		IKBD_THIRD_M_PKT
						; Shouldn't get here.
						illegal


						; Check if we have received a mouse header packet
						; and handle it. A mouse header packet contains data
						; on what buttons (if any) have been pressed.
IKBD_CHK_MOUSE_HEADER:	cmpi.b	#IKBD_MIN_MOUSE_PKT_VAL,d0
						blo		IKBD_HANDLE_KEYS
						addq.b	#1,mouse_packets_received
						lea		_mouse,a3

						btst.l	#IKBD_LCLICK_BIT,d0
						beq		IKBD_N_LCLICK
						move.w	#TRUE,MOUSE_LEFT_CLICK(a3)

IKBD_N_LCLICK:			btst.l	#IKBD_RCLICK_BIT,d0
						beq		IKBD_RETURN
						move.w	#TRUE,MOUSE_RIGHT_CLICK(a3)
						bra		IKBD_RETURN


						; Handle the second mouse packet (which specifies the
						; signed change in x). It returns early if delta x is
						; zero or if the current x position is already at its
						; maximum or minimum.
IKBD_SECOND_M_PKT:		lea		_mouse,a3
						tst.b	d0
						beq		IKBD_RETURN
						bmi		IKBD_X_DELTA_NEG
						
						cmpi.w	#SCRN_MAX_X,MOUSE_X(a3)
						bhs		IKBD_RETURN
						bra		IKBD_X_DELTA_ADD

IKBD_X_DELTA_NEG:		tst.w	MOUSE_X(a3)
						beq		IKBD_RETURN
						bra		IKBD_X_DELTA_ADD

						; Confirm that the new x coordinate is in range.
IKBD_X_DELTA_ADD:		ext.w	d0
						add.w	MOUSE_X(a3),d0
						bmi		IKBD_X_TOO_SMALL
						cmpi.w	#SCRN_MAX_X,d0
						bhi		IKBD_X_TOO_LARGE

						move.w	d0,MOUSE_X(a3)
						move.w	#TRUE,MOUSE_POS_CHANGE(a3)
						bra		IKBD_RETURN

IKBD_X_TOO_SMALL:		clr.w	MOUSE_X(a3)
						move.w	#TRUE,MOUSE_POS_CHANGE(a3)
						bra		IKBD_RETURN

IKBD_X_TOO_LARGE:		move.w	#SCRN_MAX_X,MOUSE_X(a3)
						move.w	#TRUE,MOUSE_POS_CHANGE(a3)
						bra		IKBD_RETURN


						; Handle the third mouse packet (which specifies the
						; signed change in y). It returns early if delta y is
						; zero or if the current y position is already at its
						; maximum or minimum.
IKBD_THIRD_M_PKT:		clr.b	mouse_packets_received
						lea		_mouse,a3
						tst.b	d0
						beq		IKBD_RETURN
						bmi		IKBD_Y_DELTA_NEG
						
						cmpi.w	#SCRN_MAX_Y,MOUSE_Y(a3)
						bhs		IKBD_RETURN
						bra		IKBD_Y_DELTA_ADD

IKBD_Y_DELTA_NEG:		tst.w	MOUSE_Y(a3)
						beq		IKBD_RETURN
						bra		IKBD_Y_DELTA_ADD

						; Confirm that the new y coordinate is in range.
IKBD_Y_DELTA_ADD:		ext.w	d0
						add.w	MOUSE_Y(a3),d0
						bmi		IKBD_Y_TOO_SMALL
						cmpi.w	#SCRN_MAX_Y,d0
						bhi		IKBD_Y_TOO_LARGE

						move.w	d0,MOUSE_Y(a3)
						move.w	#TRUE,MOUSE_POS_CHANGE(a3)
						bra		IKBD_RETURN

IKBD_Y_TOO_SMALL:		clr.w	MOUSE_Y(a3)
						move.w	#TRUE,MOUSE_POS_CHANGE(a3)
						bra		IKBD_RETURN

IKBD_Y_TOO_LARGE:		move.w	#SCRN_MAX_Y,MOUSE_Y(a3)
						move.w	#TRUE,MOUSE_POS_CHANGE(a3)
						bra		IKBD_RETURN


						; Check if it is a make or break code.
IKBD_HANDLE_KEYS:		bclr.l	#IKBD_BREAK_BIT,d0
						beq		IKBD_HANDLE_MAKE_CODE

						; Check if something should be removed from the shift
						; buffer.
						cmpi.b	#IKBD_CTRL_KEY,d0
						bne		IKBD_NOT_CTRL_BREAK
						eori.b	#IKBD_CTRL_BITMASK,_kybdShiftBuffer
						bra		IKBD_RETURN

IKBD_NOT_CTRL_BREAK:	cmpi.b	#IKBD_ALT_KEY,d0
						bne		IKBD_NOT_ALT_BREAK
						eori.b	#IKBD_ALT_BITMASK,_kybdShiftBuffer
						bra		IKBD_RETURN

IKBD_NOT_ALT_BREAK:		cmpi.b	#IKBD_LSHIFT_KEY,d0
						bne		IKBD_NOT_LSHIFT_BREAK
						eori.b	#IKBD_LSHIFT_BITMASK,_kybdShiftBuffer
						bra		IKBD_RETURN

IKBD_NOT_LSHIFT_BREAK:	cmpi.b	#IKBD_RSHIFT_KEY,d0
						bne		IKBD_NOT_RSHIFT_BREAK
						eori.b	#IKBD_RSHIFT_BITMASK,_kybdShiftBuffer
						bra		IKBD_RETURN

IKBD_NOT_RSHIFT_BREAK:	cmpi.b	#IKBD_CAPS_KEY,d0
						bne		IKBD_RETURN
						eori.b	#IKBD_CAPS_BITMASK,_kybdShiftBuffer
						bra		IKBD_RETURN


						; Check if something should be added to the shift
						; buffer.
IKBD_HANDLE_MAKE_CODE:	cmpi.b	#IKBD_CTRL_KEY,d0
						bne		IKBD_NOT_CTRL_MAKE
						ori.b	#IKBD_CTRL_BITMASK,_kybdShiftBuffer
						bra		IKBD_RETURN

IKBD_NOT_CTRL_MAKE:		cmpi.b	#IKBD_ALT_KEY,d0
						bne		IKBD_NOT_ALT_MAKE
						ori.b	#IKBD_ALT_BITMASK,_kybdShiftBuffer
						bra		IKBD_RETURN

IKBD_NOT_ALT_MAKE:		cmpi.b	#IKBD_LSHIFT_KEY,d0
						bne		IKBD_NOT_LSHIFT_MAKE
						ori.b	#IKBD_LSHIFT_BITMASK,_kybdShiftBuffer
						bra		IKBD_RETURN

IKBD_NOT_LSHIFT_MAKE:	cmpi.b	#IKBD_RSHIFT_KEY,d0
						bne		IKBD_NOT_RSHIFT_MAKE
						ori.b	#IKBD_RSHIFT_BITMASK,_kybdShiftBuffer
						bra		IKBD_RETURN

IKBD_NOT_RSHIFT_MAKE:	cmpi.b	#IKBD_CAPS_KEY,d0
						bne		IKBD_REG_KEY
						ori.b	#IKBD_CAPS_BITMASK,_kybdShiftBuffer
						bra		IKBD_RETURN

IKBD_REG_KEY:			move.w	d0,-(sp)
						jsr 	_addToKeyBuffer
						addq.l	#2,sp

IKBD_RETURN:			movem.l	(sp)+,d0-d7/a0-a6
						andi.b	#$BF,MFP_IN_SERVICE_B_REG
						rte

; BOOL mouseLclick(Mouse * const mouse);
;
; Brief: Checks if a left mouse click has happened with the given
; mouse.
; Details: The mouse's left click status will be reset after being checked.
;
; Param: mouse The mouse object to check for clicking.
; Return TRUE if the mouse has been clicked; FALSE otherwise.
;
; Register Table
; --------------
; d0	-	Holds the original system stack pointer.
;		-	Holds the Boolean return value.
; d3	-	Holds the Boolean value indicating whether a mouse has been left
;			clicked or not.
; a0	-	Holds the address of the mouse struct.
; a6	-	Holds the address to the start of the stack frame.

M_LCLICK_MOUSE:			equ		8

_mouseLclick:			link	a6,#0
						movem.l	d1-d7/a0-a5,-(sp)

						; Enter Supervisor Mode.
						clr.l	-(sp)
						move.w	#$20,-(sp)
						trap	#1
						addq.l	#6,sp

						; Mask keyboard/mouse interrupts.
						move.w	#IKBD_CHANNEL_LEV,-(sp)
						jsr		_mask_level_toggle
						addq.l	#2,sp

						; Exit Supervisor Mode.
						move.l	d0,-(sp)
						move.w	#$20,-(sp)
						trap	#1
						addq.l	#6,sp

						clr.l	d3
						movea.l	M_LCLICK_MOUSE(a6),a0
						move.w	MOUSE_LEFT_CLICK(a0),d3
						move.w	#FALSE,MOUSE_LEFT_CLICK(a0)

						; Enter Supervisor Mode.
						clr.l	-(sp)
						move.w	#$20,-(sp)
						trap	#1
						addq.l	#6,sp

						; Unmask keyboard/mouse interrupts.
						move.w	#IKBD_CHANNEL_LEV,-(sp)
						jsr		_mask_level_toggle
						addq.l	#2,sp

						; Exit Supervisor Mode.
						move.l	d0,-(sp)
						move.w	#$20,-(sp)
						trap	#1
						addq.l	#6,sp

						move.w	d3,d0
						movem.l	(sp)+,d1-d7/a0-a5
						unlk	a6
						rts


; BOOL mouseRclick(Mouse * const mouse);
;
; Brief: Checks if a right mouse click has happened with the given
; mouse.
; Details: The mouse's right click status will be reset after being checked.
;
; Param: mouse The mouse object to check for clicking.
; Return TRUE if the mouse has been clicked; FALSE otherwise.
;
; Register Table
; --------------
; d0	-	Holds the original system stack pointer.
;		-	Holds the Boolean return value.
; d3	-	Holds the Boolean value indicating whether a mouse has been right
;			clicked or not.
; a0	-	Holds the address of the mouse struct.
; a6	-	Holds the address to the start of the stack frame.

M_RCLICK_MOUSE:			equ		8

_mouseRclick:			link	a6,#0
						movem.l	d1-d7/a0-a5,-(sp)

						; Enter Supervisor Mode.
						clr.l	-(sp)
						move.w	#$20,-(sp)
						trap	#1
						addq.l	#6,sp

						; Mask keyboard/mouse interrupts.
						move.w	#IKBD_CHANNEL_LEV,-(sp)
						jsr		_mask_level_toggle
						addq.l	#2,sp

						; Exit Supervisor Mode.
						move.l	d0,-(sp)
						move.w	#$20,-(sp)
						trap	#1
						addq.l	#6,sp

						clr.l	d3
						movea.l	M_RCLICK_MOUSE(a6),a0
						move.w	MOUSE_RIGHT_CLICK(a0),d3
						move.w	#FALSE,MOUSE_RIGHT_CLICK(a0)

						; Enter Supervisor Mode.
						clr.l	-(sp)
						move.w	#$20,-(sp)
						trap	#1
						addq.l	#6,sp

						; Unmask keyboard/mouse interrupts.
						move.w	#IKBD_CHANNEL_LEV,-(sp)
						jsr		_mask_level_toggle
						addq.l	#2,sp

						; Exit Supervisor Mode.
						move.l	d0,-(sp)
						move.w	#$20,-(sp)
						trap	#1
						addq.l	#6,sp

						move.w	d3,d0
						movem.l	(sp)+,d1-d7/a0-a5
						unlk	a6
						rts


; BOOL mouseMoved(Mouse * const mouse);
;
; Brief: Checks if the given mouse has moved since last getting the position of
; it.
; Details: The mouse's right click status will be reset after being checked.
;
; Param: mouse The mouse to check the movement of.
; Return TRUE if the mouse has been moved; FALSE otherwise.
;
; Register Table
; --------------
; d0	-	Holds the original system stack pointer.
;		-	Holds the Boolean return value.
; d3	-	Holds the Boolean value indicating whether a mouse has been moved or
;			not.
; a0	-	Holds the address of the mouse struct.
; a6	-	Holds the address to the start of the stack frame.

M_MOVE_MOUSE:			equ		8

_mouseMoved:			link	a6,#0
						movem.l	d1-d7/a0-a5,-(sp)

						; Enter Supervisor Mode.
						clr.l	-(sp)
						move.w	#$20,-(sp)
						trap	#1
						addq.l	#6,sp

						; Mask keyboard/mouse interrupts.
						move.w	#IKBD_CHANNEL_LEV,-(sp)
						jsr		_mask_level_toggle
						addq.l	#2,sp

						; Exit Supervisor Mode.
						move.l	d0,-(sp)
						move.w	#$20,-(sp)
						trap	#1
						addq.l	#6,sp

						clr.l	d3
						movea.l	M_MOVE_MOUSE(a6),a0
						move.w	MOUSE_POS_CHANGE(a0),d3

						; Enter Supervisor Mode.
						clr.l	-(sp)
						move.w	#$20,-(sp)
						trap	#1
						addq.l	#6,sp

						; Unmask keyboard/mouse interrupts.
						move.w	#IKBD_CHANNEL_LEV,-(sp)
						jsr		_mask_level_toggle
						addq.l	#2,sp

						; Exit Supervisor Mode.
						move.l	d0,-(sp)
						move.w	#$20,-(sp)
						trap	#1
						addq.l	#6,sp

						move.w	d3,d0
						movem.l	(sp)+,d1-d7/a0-a5
						unlk	a6
						rts


; void getMousePos(Mouse const *mouse, int *x, int *y);
;
; Brief: Returns the given mouse's current position by reference.
; Details: The boolean specifying if movement has occurred will be reset.
; 
; Param: mouse The mouse to get the position of.
; Param: x Returns the current x position of the mouse.
; Param: y Returns the current y position of the mouse.
;
; Register Table
; --------------
; d0	-	Holds the original system stack pointer.
; a0	-	Holds the address of the mouse struct.
; a6	-	Holds the address to the start of the stack frame.

M_GPOS_MOUSE:			equ		8
M_GPOS_X:				equ		12
M_GPOS_Y:				equ		16

_getMousePos:			link	a6,#0
						movem.l	d0-d7/a0-a5,-(sp)

						; Enter Supervisor Mode.
						clr.l	-(sp)
						move.w	#$20,-(sp)
						trap	#1
						addq.l	#6,sp

						; Mask keyboard/mouse interrupts.
						move.w	#IKBD_CHANNEL_LEV,-(sp)
						jsr		_mask_level_toggle
						addq.l	#2,sp

						; Exit Supervisor Mode.
						move.l	d0,-(sp)
						move.w	#$20,-(sp)
						trap	#1
						addq.l	#6,sp

						movea.l	M_GPOS_MOUSE(a6),a0
						movea.l	M_GPOS_X(a6),a1
						movea.l	M_GPOS_Y(a6),a2
						move.w	MOUSE_X(a0),(a1)
						move.w	MOUSE_Y(a0),(a2)
						move.w	#FALSE,MOUSE_POS_CHANGE(a0)

						; Enter Supervisor Mode.
						clr.l	-(sp)
						move.w	#$20,-(sp)
						trap	#1
						addq.l	#6,sp

						; Unmask keyboard/mouse interrupts.
						move.w	#IKBD_CHANNEL_LEV,-(sp)
						jsr		_mask_level_toggle
						addq.l	#2,sp

						; Exit Supervisor Mode.
						move.l	d0,-(sp)
						move.w	#$20,-(sp)
						trap	#1
						addq.l	#6,sp

						movem.l	(sp)+,d0-d7/a0-a5
						unlk	a6
						rts

mouse_packets_received:	dc.b	0