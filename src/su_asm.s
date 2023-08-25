; Provides functionality for gaining super privileges.
; 
; Copyright Academia Team 2023

				xdef			_Su
				xdef			_isSu

; UINT32 Su(UINT32 ssp);
;
; Brief: Executes the Super gemdos call.
;
; Details: When 0 is passed as a stack address, the mode we are in is toggled
; with the current stack used in the changed mode. If anything else other than
; 1 is passed, the stack address is changed to the specified address. Else, if
; 1 is specified as parameter, it returns -1 if we are in Super mode or 0 if in
; User mode.
;
; Register Table:
; ---------------
; d0	-	Holds the old system stack pointer so it can be returned.
; a6	-	Holds the address of the start of the stack frame.

SU_SSP:			equ				8

_Su:			link			a6,#0
				movem.l			d1-d2/a0-a2,-(sp)

				move.l			SU_SSP(a6),-(sp)
				move.w			#$20,-(sp)
				trap			#1
				addq.l			#6,sp

				movem.l			(sp)+,d1-d2/a0-a2
				unlk			a6
				rts


; UINT8 isSu(void);

; Brief: Checks if code is in Super mode or not.
;
; Register Table:
; ---------------
; d0	-	Holds the returned value of Su() indicating whether we are in
;			Super Mode or not.
;		-	The return value indicating if we are in Super mode or not.

_isSu:			move.l			#1,-(sp)
				bsr				_Su
				addq.l			#4,sp
				tst.l			d0
				bmi				ISU_IS_SUPER
				clr.b			d0
				bra				ISU_RETURN

ISU_IS_SUPER:	move.b			#1,d0

ISU_RETURN:		rts