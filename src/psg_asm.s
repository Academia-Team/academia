; Includes low-level functions to interact with the Atari ST's Programmable
; Sound Generator.
; 
; Copyright Academia Team 2023

					xdef			_write_psg
					xdef			_read_psg

					xref			_isSu
					xref			_Su

PSG_REG_SELECT:		equ				$FFFF8800
PSG_REG_READ:		equ				$FFFF8800
PSG_REG_WRITE:		equ				$FFFF8802

MAX_PSG_REG_NUM:	equ				15
MAX_PSG_VAL:		equ				$FF

; void write_psg(PsgReg reg, UINT16 val)
;
; Brief: Writes the given byte value (0-255) to the given PSG register (0-15).
;
; Register Table:
; ---------------
; d0	-	Holds a value indicating if the subroutine is currently running in
;			supervisor mode.
;		-	Holds the old system stack pointer from Su().
; d1	-	Holds the PSG register to write to.
; d2	-	Holds the value to write to a PSG register.
; d4	-	Holds a value indicating if the subroutine has entered supervisor
;			mode.
; a6	-	Holds the address of the start of the stack frame.

W_PSG_REG_PARAM:	equ					8
W_PSG_VAL_PARAM:	equ					10

_write_psg:			link				a6,#0
					movem.l				d0-d2/d4,-(sp)

					; Enter Supervisor Mode.
					jsr					_isSu
					move.b				d0,d4
					bne					W_PSG_MAIN
					clr.l				-(sp)
					jsr					_Su
					addq.l				#4,sp

					; Confirm that all parameters are in range.
W_PSG_MAIN:			move.w				W_PSG_REG_PARAM(a6),d1
					bmi					W_PSG_RETURN
					cmpi.w				#MAX_PSG_REG_NUM,d1
					bgt					W_PSG_RETURN
					move.w				W_PSG_VAL_PARAM(a6),d2
					cmpi.w				#MAX_PSG_VAL,d2
					bhi					W_PSG_RETURN

					; Move the register number and the value to write as bytes.
					; The original parameters were only words for compatibility
					; with a C compiler.
					move.b				d1,PSG_REG_SELECT
					move.b				d2,PSG_REG_WRITE

					; Leave Supervisor Mode.
					tst.b				d4
					bne					W_PSG_RETURN
					move.l				d0,-(sp)
					jsr					_Su
					addq.l				#4,sp

W_PSG_RETURN:		movem.l				(sp)+,d0-d2/d4
					unlk				a6
					rts

; UINT8 read_psg(PsgReg reg)
;
; Brief: Reads a byte value from the given PSG register (0-15).
;
; Details: If any invalid parameter is provided, nothing will be written to a
;		   PSG register.
;
; Register Table:
; ---------------
; d0	-	Holds a value indicating if the subroutine is currently running in
;			supervisor mode.
;		-	Holds the old system stack pointer from Su().
;		-	Holds the PSG register value to be returned.
; d1	-	Holds the PSG register to write to.
; d4	-	Holds a value indicating if the subroutine has entered supervisor
;			mode.
; d5	-	Temporarily holds the value to return.
; a6	-	Holds the address of the start of the stack frame.

R_PSG_REG_PARAM:	equ					8

_read_psg:			link				a6,#0
					movem.l				d1/d4-d5,-(sp)

					; Enter Supervisor Mode.
					jsr					_isSu
					move.b				d0,d4
					bne					R_PSG_MAIN
					clr.l				-(sp)
					jsr					_Su
					addq.l				#4,sp

					; Confirm that the parameter is in range.
R_PSG_MAIN:			clr.l				d5
					move.w				R_PSG_REG_PARAM(a6),d1
					bmi					R_PSG_RETURN
					cmpi.w				#MAX_PSG_REG_NUM,d1
					bgt					R_PSG_RETURN

					move.b				d1,PSG_REG_SELECT
					move.b				PSG_REG_READ,d5

					; Leave Supervisor Mode.
					tst.b				d4
					bne					R_PSG_RETURN
					move.l				d0,-(sp)
					jsr					_Su
					addq.l				#4,sp

R_PSG_RETURN:		move.b				d5,d0
					movem.l				(sp)+,d1/d4-d5
					unlk				a6
					rts