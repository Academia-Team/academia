; Manages the Vertical Blank ISR.
;
; Copyright 2023 Academia Team

						include			bool_asm.i

						xdef			_vbl_isr
						xref			_vbl_main


; void vbl_isr(void)
;
; Brief: Executes vbl_main() every time the vertical blank clock interrupts.

_vbl_isr:				movem.l			d0-d7/a0-a6,-(sp)

						jsr				_vbl_main

						movem.l			(sp)+,d0-d7/a0-a6
						rte