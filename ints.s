; Contains subroutines designed to allow for the disabling and enabling of
; different hardware interrupts.

			xdef	_set_ipl

_set_ipl: 	move.w	sr,d0
			move.w	d0,-(sp)			; place orig. sr on stack

			lsr.w	#8,d0				; will return orig. ipl
			and.w	#$0007,d0			; ... in d0.w

			andi.w	#$F8FF,(sp)
			move.w	d1,-(sp)
			move.w	8(sp),d1			; place new ipl in d1.w
			lsl.w	#8,d1
			and.w	#$0700,d1
			or.w	d1,2(sp)			; insert it into sr on stack
			move.w 	(sp)+,d1

			rte							; trick: when returning,
										; ... install modified sr
										; ... from stack!

; void mask_level_toggle(UINT8 channel)
;
; Brief: Toggles masking for a specific device with the given priority level in
; the MC68901.
;
; Register Table
; --------------
; d0	-	Holds the bit position that needs to be toggled in one of the
;			mask registers.
; a0	-	Holds the Interrupt Mask Register A.
;		-	Holds the Interrupt Mask Register B.
; a6	-	Holds the address to the start of the stack frame.
ML_MAX_CHANNEL:		equ		%1111
ML_HIGH_BIT:		equ		3
ML_CHANNEL:			equ		8
REG_A_MASK:			equ		$FFFFFA13
REG_B_MASK:			equ		$FFFFFA15

					xdef	_mask_level_toggle

_mask_level_toggle:	link	a6,#0
					movem.l	d0/a0,-(sp)
					cmpi.w	#ML_MAX_CHANNEL,ML_CHANNEL(a6)
					bhi		ML_RETURN

					clr.l	d0
					bclr.b	#ML_HIGH_BIT,ML_CHANNEL+1(a6)
					beq		ML_REG_B

					movea.l	#REG_A_MASK,a0
					bra		ML_TOGGLE_BIT
ML_REG_B:			movea.l	#REG_B_MASK,a0

ML_TOGGLE_BIT:		clr.l	d0
					move.w	ML_CHANNEL(a6),d0
					bchg.b	d0,(a0)

ML_RETURN:			movem.l	(sp)+,d0/a0
					unlk	a6
					rts