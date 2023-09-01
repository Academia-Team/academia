; Contains subroutines for handling input from IO interfaces.
; 
; Copyright Academia Team 2023

						include	bool_asm.i
						include joy.i
						include mouse.i
						include scde_asm.i
						include scrn_asm.i

						xdef	_IKBD_isr
						xdef	_keyPressed

						xref	_addToShiftBuffer
						xref	_addToKeyBuffer
						xref	_handleSpecialAction
						xref	_hasSpecial
						xref	_isKeyMod
						xref	_mask_level_toggle
						xref	_setRelMousePos

IKBD_STATUS_REG:		equ		$FFFFFC00
IKBD_RDR_REG:			equ		$FFFFFC02
MIDI_STATUS_REG:		equ		$FFFFFC04
MIDI_RDR_REG:			equ		$FFFFFC06
IRQ_BIT:				equ		7
IKBD_BREAK_BIT:			equ		7
IKBD_MAX_SCANCODE:		equ		$72
IKBD_MIN_SCANCODE:		equ		$01
IKBD_PRIORITY_LEV:		equ		6

IKBD_MIN_JOY_REC_VAL:	equ		$FE
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

						; Check if a joystick event marker has previously been
						; received and handle accordingly.
						cmpi.b	#TRUE,joy_record
						bne		IKBD_CHK_PREV_M_PKT
						move.b	#FALSE,joy_record
						move.b	d5,-(sp)
						bsr		handle_joy
						addq.l	#2,sp
						bra		IKBD_RETURN

						; Check if a mouse packet has previously been received
						; and handle accordingly.
IKBD_CHK_PREV_M_PKT:	tst.b	mouse_packets_received
						beq		IKBD_CHK_JOY_HEADER
						move.b	d5,-(sp)
						bsr		handle_mouse
						addq.l	#2,sp
						bra		IKBD_RETURN

						; Check for a joystick event marker.
IKBD_CHK_JOY_HEADER:	cmpi.b	#IKBD_MIN_JOY_REC_VAL,d5
						blo		IKBD_CHK_MOUSE_HEADER
						move.b	#TRUE,joy_record
						bra		IKBD_RETURN

						; Check for a mouse header packet.
IKBD_CHK_MOUSE_HEADER:	cmpi.b	#IKBD_MIN_MOUSE_PKT_VAL,d5
						blo		IKBD_HANDLE_KEYS
						move.b	d5,-(sp)
						bsr		handle_mouse
						addq.l	#2,sp
						bra		IKBD_RETURN

						; Determine whether we are dealing with a make or break
						; code.
IKBD_HANDLE_KEYS:		bclr.l	#IKBD_BREAK_BIT,d5
						bne		IKBD_BREAK_CODE
						move.l	#TRUE,d6
						addq.b	#1,keys_pressed
						bra		IKBD_CHK_SCANCODE

						; If no keys have been pressed, then the break code is
						; from before the current keyboard ISR was activated. In
						; that case, the value will be ignored.
IKBD_BREAK_CODE:		move.l	#FALSE,d6
						tst.b	keys_pressed
						beq		IKBD_RETURN
						subq.b	#1,keys_pressed

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
IKBD_RETURN:			btst.b	#IRQ_BIT,IKBD_STATUS_REG
						bne		IKBD_GET_VAL
						btst.b	#IRQ_BIT,MIDI_STATUS_REG
						bne		IKBD_READ_MIDI

						movem.l	(sp)+,d0-d7/a0-a6
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
						movem.l	d0-d7/a0-a6,-(sp)
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
						; signed change in x).
MOUSE_SECOND_PKT:		ext.w	d0
						move.w	d0,delta_mouse_x
						bra		MOUSE_RETURN


						; Handle the third mouse packet (which specifies the
						; signed change in y).
MOUSE_THIRD_PKT:		ext.w	d0
						move.w	d0,-(sp)
						move.w	delta_mouse_x,-(sp)
						jsr		_setRelMousePos
						addq.l	#4,sp
						clr.b	mouse_packets_received

MOUSE_RETURN:			movem.l	(sp)+,d0-d7/a0-a6
						unlk	a6
						rts

; UINT8 keyPressed(void)
;
; Brief: Returns if a key is being pressed or not.
;
; Register Table:
; ---------------
; d0	-	Holds the BOOLEAN value to be returned.

_keyPressed:			move.w	#IKBD_PRIORITY_LEV,-(sp)
						jsr		_mask_level_toggle
						addq.l	#2,sp

						tst.b	keys_pressed
						beq		KEYP_NOT_PRESSED
						move.b	#TRUE,d0
						bra		KEYP_RETURN
KEYP_NOT_PRESSED:		move.b	#FALSE,d0

KEYP_RETURN:			move.w	#IKBD_PRIORITY_LEV,-(sp)
						jsr		_mask_level_toggle
						addq.l	#2,sp

						rts

; void handle_joy(UINT8 record)
;
; Brief: Handles joystick record.
;
; Register Table:
; ---------------
; a3	-	Holds the address of the joy struct.
; a6	-	Holds the address to the start of the stack frame.

JOY_RECORD_PARAM:		equ		8
JOY_TRIGGER_BIT:		equ		7

handle_joy:				link	a6,#0
						movem.l	d0/a3,-(sp)
						lea		_joy,a3

						bclr.b	#JOY_TRIGGER_BIT,JOY_RECORD_PARAM(a6)
						beq		JOY_GET_POS
						move.b	#TRUE,JOY_TRIGGER(a3)

JOY_GET_POS:			move.b	JOY_RECORD_PARAM(a6),JOY_POS(a3)

						movem.l	(sp)+,d0/a3
						unlk	a6
						rts

delta_mouse_x:			dc.w	0
keys_pressed:			dc.b	0
mouse_packets_received:	dc.b	0
joy_record:				dc.b	FALSE
