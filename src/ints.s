; Contains subroutines designed to allow for the disabling and enabling
; of different hardware interrupts.

			xdef	_set_ipl
			xdef	_mask_level_toggle
			
			xref	_isSu
			xref	_Su

; short set_ipl(int mask);
;
; Brief: Set the CPU's interrupt mask to the given value.
;
; Note: It is a wrapper for modify_ipl.
;
; Register Table
; --------------
; d0	-	Holds a value indicating if the subroutine is currently running in
;			supervisor mode.
;		-	Holds the old system stack pointer from Su().
;		-	Holds a copy of the original status register to return.
; d4	-	Holds a value indicating if the subroutine has entered supervisor
;			mode.
; d5	-	Holds the old system stack pointer from Su().
; d6	-	Holds a copy of the original status register to return.
; a6	-	Holds the address to the start of the stack frame.
_set_ipl: 	link	a6,#0
			movem.l	d1-d7/a0-a5,-(sp)

			jsr		_isSu
			move.b	d0,d4
			bne		S_IPL_MAIN
			clr.l	-(sp)
			jsr		_Su
			move.l	d0,d5
			addq.l	#4,sp

S_IPL_MAIN:	move.w	8(a6),-(sp)
			jsr		modify_ipl
			move.w	d0,d6
			addq.l	#2,sp

			tst.b	d4
			bne		S_IPL_RET
			move.l	d5,-(sp)
			jsr		_Su
			addq.l	#4,sp

S_IPL_RET:	move.w	d6,d0
			movem.l	(sp)+,d1-d7/a0-a5
			unlk	a6
			rts

; Brief: Set the CPU's interrupt mask to the given value.
;
; Note: Requires Super privileges.
;
; Register Table
; --------------
; d0	-	Holds a copy of the original status register to return.
; d1	-	Holds the desired Interrupt Priority Level.
;		-	Holds the new status register.
modify_ipl:	move.w	sr,d0
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
; d0	-	Holds a value indicating if the subroutine is currently running in
;			supervisor mode.
;		-	Holds the old system stack pointer from Su().
;		-	Holds the bit position that needs to be toggled in one of the
;			mask registers.
; d1	-	Holds a value indicating if the subroutine has entered supervisor
;			mode.
; d2	-	Holds the old system stack pointer from Super().
; a0	-	Holds the Interrupt Mask Register A.
;		-	Holds the Interrupt Mask Register B.
; a6	-	Holds the address to the start of the stack frame.
ML_MAX_CHANNEL:		equ		%1111
ML_HIGH_BIT:		equ		3
ML_CHANNEL:			equ		8
REG_A_MASK:			equ		$FFFFFA13
REG_B_MASK:			equ		$FFFFFA15

_mask_level_toggle:	link	a6,#0
					movem.l	d0-d2/a0,-(sp)
					cmpi.w	#ML_MAX_CHANNEL,ML_CHANNEL(a6)
					bhi		ML_RETURN

					jsr		_isSu
					move.b	d0,d1
					bne		ML_CHK_BIT
					clr.l	-(sp)
					jsr		_Su
					move.l	d0,d2
					addq.l	#4,sp

ML_CHK_BIT:			clr.l	d0
					bclr.b	#ML_HIGH_BIT,ML_CHANNEL+1(a6)
					beq		ML_REG_B

					movea.l	#REG_A_MASK,a0
					bra		ML_TOGGLE_BIT
ML_REG_B:			movea.l	#REG_B_MASK,a0

ML_TOGGLE_BIT:		clr.l	d0
					move.w	ML_CHANNEL(a6),d0
					bchg.b	d0,(a0)

					tst.b	d1
					bne		ML_RETURN
					move.l	d2,-(sp)
					jsr		_Su
					addq.l	#4,sp

ML_RETURN:			movem.l	(sp)+,d0-d2/a0
					unlk	a6
					rts