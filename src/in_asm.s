; Contains subroutines for handling input from IO interfaces.
; 
; Copyright Academia Team 2023

						include	bool_asm.i
						include mouse.i
						include scde_asm.i
						include scrn_asm.i

						xdef	_IKBD_isr

						xref	_addToKeyBuffer
						xref	_kybdShiftBuffer

IKBD_STATUS_REG:		equ		$FFFFFC00
IKBD_RDR_REG:			equ		$FFFFFC02
MIDI_STATUS_REG:		equ		$FFFFFC04
MIDI_RDR_REG:			equ		$FFFFFC06
RDRF_BIT:				equ		0
OVRN_BIT:				equ		5
IRQ_BIT:				equ		7
IKBD_BREAK_BIT:			equ		7
IKBD_MAX_SCANCODE:		equ		$72
IKBD_MIN_SCANCODE:		equ		$01

IKBD_MIN_MOUSE_PKT_VAL:	equ		$F8
IKBD_RCLICK_BIT:		equ		0
IKBD_LCLICK_BIT:		equ		1

IKBD_CAPS_BITMASK:		equ		$10
IKBD_CTRL_BITMASK:		equ		$04
IKBD_ALT_BITMASK:		equ		$08
IKBD_LSHIFT_BITMASK:	equ		$02
IKBD_RSHIFT_BITMASK:	equ		$01

IKBD_CHANNEL_LEV:		equ		6

MFP_IN_SERVICE_B_REG:	equ		$FFFFFA11
IKBD_MFP_SERVICE_BIT:	equ		6


; void IKBD_isr(void)
;
; Brief: Handles keyboard and mouse input.
;
; Register Table:
; ---------------
; d0	-	Holds the value recieved by the keyboard.
; a0	-	Holds the keyboard status register for reading.
; a1	-	Holds the MIDI status register for reading.
;		-	Holds the address of the receiver register of the MIDI.
; a2	-	Holds the address of the receiver register of the keyboard.
; a3	-	Holds the address of the mouse struct.
_IKBD_isr:				movem.l	d0-d7/a0-a6,-(sp)

						; If the keyboard doesn't have anything in its buffer,
						; get out of dodge.
						movea.l	#IKBD_STATUS_REG,a0
						btst.b	#RDRF_BIT,(a0)
						bne		IKBD_GET_VAL
						btst.b	#OVRN_BIT,(a0)
						bne		IKBD_GET_VAL

						; Check if MIDI is causing an interrupt.
						movea.l	#MIDI_STATUS_REG,a0
						btst.b	#IRQ_BIT,(a0)
						beq		IKBD_READ_MIDI
						; A spurious interupt is not good. Time to fail
						; ungracefully.
						illegal

						; Don't need to store value. Just read it and get out
						; of there.
IKBD_READ_MIDI:			movea.l	#MIDI_RDR_REG,a1
						tst.b	(a1)
						bra IKBD_RETURN

						; Get the value held by the keyboard.
IKBD_GET_VAL:			clr.l	d0
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

						; Check if the scancode is valid.
						cmpi.b	#IKBD_MAX_SCANCODE,d0
						bhi		IKBD_RETURN
						cmpi.b	#IKBD_MIN_SCANCODE,d0
						blo		IKBD_RETURN

						; Check if something should be removed from the shift
						; buffer.
						cmpi.b	#IKBD_CTRL_SCANCODE,d0
						bne		IKBD_NOT_CTRL_BREAK
						eori.b	#IKBD_CTRL_BITMASK,_kybdShiftBuffer
						bra		IKBD_RETURN

IKBD_NOT_CTRL_BREAK:	cmpi.b	#IKBD_ALT_SCANCODE,d0
						bne		IKBD_NOT_ALT_BREAK
						eori.b	#IKBD_ALT_BITMASK,_kybdShiftBuffer
						bra		IKBD_RETURN

IKBD_NOT_ALT_BREAK:		cmpi.b	#IKBD_LSHIFT_SCANCODE,d0
						bne		IKBD_NOT_LSHIFT_BREAK
						eori.b	#IKBD_LSHIFT_BITMASK,_kybdShiftBuffer
						bra		IKBD_RETURN

IKBD_NOT_LSHIFT_BREAK:	cmpi.b	#IKBD_RSHIFT_SCANCODE,d0
						bne		IKBD_NOT_RSHIFT_BREAK
						eori.b	#IKBD_RSHIFT_BITMASK,_kybdShiftBuffer
						bra		IKBD_RETURN

IKBD_NOT_RSHIFT_BREAK:	cmpi.b	#IKBD_CAPS_SCANCODE,d0
						bne		IKBD_RETURN
						eori.b	#IKBD_CAPS_BITMASK,_kybdShiftBuffer
						bra		IKBD_RETURN


						; Check if the scancode is valid.
IKBD_HANDLE_MAKE_CODE:	cmpi.b	#IKBD_MAX_SCANCODE,d0
						bhi		IKBD_RETURN
						cmpi.b	#IKBD_MIN_SCANCODE,d0
						blo		IKBD_RETURN

						; Check if something should be added to the shift
						; buffer.
						cmpi.b	#IKBD_CTRL_SCANCODE,d0
						bne		IKBD_NOT_CTRL_MAKE
						ori.b	#IKBD_CTRL_BITMASK,_kybdShiftBuffer
						bra		IKBD_RETURN

IKBD_NOT_CTRL_MAKE:		cmpi.b	#IKBD_ALT_SCANCODE,d0
						bne		IKBD_NOT_ALT_MAKE
						ori.b	#IKBD_ALT_BITMASK,_kybdShiftBuffer
						bra		IKBD_RETURN

IKBD_NOT_ALT_MAKE:		cmpi.b	#IKBD_LSHIFT_SCANCODE,d0
						bne		IKBD_NOT_LSHIFT_MAKE
						ori.b	#IKBD_LSHIFT_BITMASK,_kybdShiftBuffer
						bra		IKBD_RETURN

IKBD_NOT_LSHIFT_MAKE:	cmpi.b	#IKBD_RSHIFT_SCANCODE,d0
						bne		IKBD_NOT_RSHIFT_MAKE
						ori.b	#IKBD_RSHIFT_BITMASK,_kybdShiftBuffer
						bra		IKBD_RETURN

IKBD_NOT_RSHIFT_MAKE:	cmpi.b	#IKBD_CAPS_SCANCODE,d0
						bne		IKBD_REG_KEY
						ori.b	#IKBD_CAPS_BITMASK,_kybdShiftBuffer
						bra		IKBD_RETURN

IKBD_REG_KEY:			move.w	d0,-(sp)
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

mouse_packets_received:	dc.b	0