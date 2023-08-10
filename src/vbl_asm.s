; Manages the Vertical Blank ISR.
;
; Copyright 2023 Academia Team

						include			bool_asm.i

						xdef			_vbl_isr

						xref			_processSync
						xref			_dead
						xref			_gameWorld
						xref			_vbl_main

						xref			_timeNow
						xref			_timeDesired
						xref			_immunityTimer
						xref			_playerMoveTimer
						xref			_loopCounter
						xref			_deathCounter
						xref			_gameStart


; void vbl_isr(void)
;
; Brief: Executes vbl_main() every time the vertical blank clock interrupts.

_vbl_isr:				jsr				_vbl_main

						cmpi.b			#TRUE,_gameStart
						bne				VBL_RETURN
						pea				_deathCounter
						pea				_loopCounter
						pea				_playerMoveTimer
						pea				_immunityTimer
						pea				_timeDesired
						pea				_timeNow
						pea				_dead
						pea				_gameWorld
						jsr				_processSync
						add.l			#32,sp

VBL_RETURN:				rte