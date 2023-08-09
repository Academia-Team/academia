; Provides functionality for gaining super privileges.
; 
; Copyright Academia Team 2023

			xdef			_Su

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

SU_SSP:		equ				8

_Su:		link			a6,#0
			movem.l			d1-d2/a0-a2,-(sp)

			move.l			SU_SSP(a6),-(sp)
			move.w			#$20,-(sp)
			trap			#1
			addq.l			#6,sp

			movem.l			(sp)+,d1-d2/a0-a2
			unlk			a6
			rts
