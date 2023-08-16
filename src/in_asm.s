; Contains subroutines for handling input from IO interfaces.
; 
; Copyright Academia Team 2023

						include	bool_asm.i
						include mouse.i
						include scde_asm.i
						include scrn_asm.i

						xdef	_IKBD_isr

						xref	_addToShiftBuffer
						xref	_addToKeyBuffer
						xref	_handleSpecialAction
						xref	_hasSpecial
						xref	_isKeyMod

IKBD_STATUS_REG:		equ		$FFFFFC00
IKBD_RDR_REG:			equ		$FFFFFC02
MIDI_STATUS_REG:		equ		$FFFFFC04
MIDI_RDR_REG:			equ		$FFFFFC06
IRQ_BIT:				equ		7
IKBD_BREAK_BIT:			equ		7
IKBD_MAX_SCANCODE:		equ		$72
IKBD_MIN_SCANCODE:		equ		$01

IKBD_MIN_MOUSE_PKT_VAL:	equ		$F8
MOUSE_RCLICK_BIT:		equ		0
MOUSE_LCLICK_BIT:		equ		1

IKBD_CHANNEL_LEV:		equ		6

MFP_IN_SERVICE_B_REG:	equ		$FFFFFA11
IKBD_MFP_SERVICE_BIT:	equ		6


; void IKBD_isr(void)
;
; Brief: Handles keyboard and mouse input.
;
; Register Table:
; ---------------
; d0	-	Holds the returned result indicating whether a scancode corresponds
;			to a key modifier.
;		-	Holds a boolean value indicating whether a special action has
;			occurred.
; d4	-	Holds a boolean value indicating whether a scancode corresponds to
;			a key modifier.
; d5	-	Holds the value recieved by the keyboard.
; d6	-	Holds a boolean value that indicates TRUE when a make code is being
;			handled and FALSE when a break code is being handled.
_IKBD_isr:				movem.l	d0-d7/a0-a6,-(sp)

						; If the keyboard doesn't have anything in its buffer,
						; get out of dodge.
						btst.b	#IRQ_BIT,IKBD_STATUS_REG
						bne		IKBD_GET_VAL

						; Check if MIDI is causing an interrupt.
						btst.b	#IRQ_BIT,MIDI_STATUS_REG
						bne		IKBD_READ_MIDI
						; A spurious interupt is not good. Time to fail
						; gracefully.
						bra		IKBD_RETURN

						; Don't need to store value. Just read it and get out
						; of there.
IKBD_READ_MIDI:			tst.b	MIDI_RDR_REG
						bra IKBD_RETURN

						; Get the value held by the keyboard.
IKBD_GET_VAL:			clr.l	d5
						move.b	IKBD_RDR_REG,d5

						; Check if a mouse packet has previously been received.
						; If no mouse packets have been processed before, check
						; for a mouse header packet.
						tst.b	mouse_packets_received
						bhi		IKBD_MANAGE_MOUSE
						cmpi.b	#IKBD_MIN_MOUSE_PKT_VAL,d5
						blo		IKBD_HANDLE_KEYS
IKBD_MANAGE_MOUSE:		move.b	d5,-(sp)
						jsr		handle_mouse
						addq.l	#2,sp
						bra		IKBD_RETURN

						; Determine whether we are dealing with a make or break
						; code.
IKBD_HANDLE_KEYS:		bclr.l	#IKBD_BREAK_BIT,d5
						bne		IKBD_BREAK_CODE
						move.l	#TRUE,d6
						bra		IKBD_CHK_SCANCODE
IKBD_BREAK_CODE:		move.l	#FALSE,d6

						; Check if the scancode is valid.
IKBD_CHK_SCANCODE:		cmpi.b	#IKBD_MAX_SCANCODE,d5
						bhi		IKBD_RETURN
						cmpi.b	#IKBD_MIN_SCANCODE,d5
						blo		IKBD_RETURN

						; Handle any key modifiers
						move.w	d5,-(sp)
						jsr		_isKeyMod
						addq.l	#2,sp
						move.b	d0,d4
						beq		IKBD_HANDLE_KEY

						move.w	d5,-(sp)
						jsr		_addToShiftBuffer
						addq.l	#2,sp

						; Handle any special actions associated with the current
						; key and modifiers.
IKBD_HANDLE_KEY:		move.w	d5,-(sp)
						jsr		_hasSpecial
						addq.l	#2,sp

						cmpi.b	#TRUE,d0
						bne		IKBD_KEY_BUFF

						move.w	d6,-(sp)
						move.w	d5,-(sp)
						jsr		_handleSpecialAction
						addq.l	#4,sp
						bra		IKBD_RETURN

						; Do not handle any break codes; otherwise, everything
						; would be handled twice.
IKBD_KEY_BUFF:			cmpi.b	#TRUE,d6
						bne		IKBD_RETURN

						; Do not handle any key modifiers.
						cmpi.b	#TRUE,d4
						beq		IKBD_RETURN

						move.w	d5,-(sp)
						jsr 	_addToKeyBuffer
						addq.l	#2,sp

						; Ensure the MIDI or keyboard aren't still interrupting.
						; Otherwise, the ISR won't run anymore.
IKBD_RETURN:			movem.l	(sp)+,d0-d7/a0-a6
						btst.b	#IRQ_BIT,IKBD_STATUS_REG
						bne		_IKBD_isr
						btst.b	#IRQ_BIT,MIDI_STATUS_REG
						bne		_IKBD_isr

						bclr.b	#IKBD_MFP_SERVICE_BIT,MFP_IN_SERVICE_B_REG
						rte

; void handle_mouse(UINT8 packet)
;
; Brief: Handles mouse packets.
;
; Details: Every time the function is run, mouse_packets_received is incremented
;		   until all three mouse packets are handled. 
;
; Register Table:
; ---------------
; d0	-	Holds the value from a mouse packet.
; a3	-	Holds the address of the mouse struct.
; a6	-	Holds the address to the start of the stack frame.

MOUSE_PACKET_PARAM:		equ		8

handle_mouse:			link	a6,#0
						movem.l	d0/a3,-(sp)
						move.b	MOUSE_PACKET_PARAM(a6),d0

						addq.b	#1,mouse_packets_received
						cmpi.b	#1,mouse_packets_received
						beq		MOUSE_FIRST_PKT
						cmpi.b	#2,mouse_packets_received
						beq		MOUSE_SECOND_PKT
						cmpi.b	#3,mouse_packets_received
						beq		MOUSE_THIRD_PKT
						; Shouldn't get here.
						bra		MOUSE_RETURN


						; A mouse header packet contains data on what buttons
						; (if any) have been pressed.
MOUSE_FIRST_PKT:		lea		_mouse,a3

						btst.l	#MOUSE_LCLICK_BIT,d0
						beq		MOUSE_N_LCLICK
						move.w	#TRUE,MOUSE_LEFT_CLICK(a3)

MOUSE_N_LCLICK:			btst.l	#MOUSE_RCLICK_BIT,d0
						beq		MOUSE_RETURN
						move.w	#TRUE,MOUSE_RIGHT_CLICK(a3)
						bra		MOUSE_RETURN


; Handle the second mouse packet (which specifies the
; signed change in x). It returns early if delta x is
; zero or if the current x position is already at its
; maximum or minimum.
MOUSE_SECOND_PKT:		lea		_mouse,a3
						tst.b	d0
						beq		MOUSE_RETURN
						bmi		MOUSE_X_DELTA_NEG

						cmpi.w	#SCRN_MAX_X,MOUSE_X(a3)
						bhs		MOUSE_RETURN
						bra		MOUSE_X_DELTA_ADD

MOUSE_X_DELTA_NEG:		tst.w	MOUSE_X(a3)
						beq		MOUSE_RETURN
						bra		MOUSE_X_DELTA_ADD

; Confirm that the new x coordinate is in range.
MOUSE_X_DELTA_ADD:		ext.w	d0
						add.w	MOUSE_X(a3),d0
						bmi		MOUSE_X_TOO_SMALL
						cmpi.w	#SCRN_MAX_X,d0
						bhi		MOUSE_X_TOO_LARGE

						move.w	d0,MOUSE_X(a3)
						move.w	#TRUE,MOUSE_POS_CHANGE(a3)
						bra		MOUSE_RETURN

MOUSE_X_TOO_SMALL:		clr.w	MOUSE_X(a3)
						move.w	#TRUE,MOUSE_POS_CHANGE(a3)
						bra		MOUSE_RETURN

MOUSE_X_TOO_LARGE:		move.w	#SCRN_MAX_X,MOUSE_X(a3)
						move.w	#TRUE,MOUSE_POS_CHANGE(a3)
						bra		MOUSE_RETURN


; Handle the third mouse packet (which specifies the
; signed change in y). It returns early if delta y is
; zero or if the current y position is already at its
; maximum or minimum.
MOUSE_THIRD_PKT:		clr.b	mouse_packets_received
						lea		_mouse,a3
						tst.b	d0
						beq		MOUSE_RETURN
						bmi		MOUSE_Y_DELTA_NEG

						cmpi.w	#SCRN_MAX_Y,MOUSE_Y(a3)
						bhs		MOUSE_RETURN
						bra		MOUSE_Y_DELTA_ADD

MOUSE_Y_DELTA_NEG:		tst.w	MOUSE_Y(a3)
						beq		MOUSE_RETURN
						bra		MOUSE_Y_DELTA_ADD

; Confirm that the new y coordinate is in range.
MOUSE_Y_DELTA_ADD:		ext.w	d0
						add.w	MOUSE_Y(a3),d0
						bmi		MOUSE_Y_TOO_SMALL
						cmpi.w	#SCRN_MAX_Y,d0
						bhi		MOUSE_Y_TOO_LARGE

						move.w	d0,MOUSE_Y(a3)
						move.w	#TRUE,MOUSE_POS_CHANGE(a3)
						bra		MOUSE_RETURN

MOUSE_Y_TOO_SMALL:		clr.w	MOUSE_Y(a3)
						move.w	#TRUE,MOUSE_POS_CHANGE(a3)
						bra		MOUSE_RETURN

MOUSE_Y_TOO_LARGE:		move.w	#SCRN_MAX_Y,MOUSE_Y(a3)
						move.w	#TRUE,MOUSE_POS_CHANGE(a3)

MOUSE_RETURN:			movem.l	(sp)+,d0/a3
						unlk	a6
						rts

mouse_packets_received:	dc.b	0