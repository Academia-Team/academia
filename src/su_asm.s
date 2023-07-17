; Provides functionality for gaining super privileges.
; 
; Copyright Academia Team 2023

			xdef			_Su

_Su:		move.l			4(sp),-(sp)
			move.w			#$20,-(sp)
			trap			#1
			addq.l			#6,sp
			rts
