; Contains subroutines designed to allow rasters to be plotted to an area in
; memory for use by the Atari ST's monochrome screen.
; 
; Copyright Academia Team 2023


; void clr_scrn(UINT32 *base)
;
; quick clear (uses movem to reduce fetch-execute cycle overhead)
; runs in about 1/100th of a second (at 8MHz)
;
; Original came from Marc Schroeder and has since been slightly modified.

					xdef			_clr_scrn

CLR_SCRN_BASE:		equ				64					; offset from SP, not A6

_clr_scrn:			movem.l			d0-7/a0-6,-(sp)
					lea				clr_scrn_zeros,a0
					movem.l			(a0)+,d1-7/a1-6
					movea.l			CLR_SCRN_BASE(sp),a0
					adda.l			#32000,a0
					move.w			#614,d0
clr_scrn_fill_loop:	movem.l			d1-7/a1-6,-(a0)
					dbra			d0,clr_scrn_fill_loop
					movem.l			d1-5,-(a0)
					movem.l			(sp)+,d0-7/a0-6
					rts

clr_scrn_zeros:		ds.l			13


; void fill_scrn(UINT32 *base)
;
; quick fill (uses movem to reduce fetch-execute cycle overhead)
; runs in about 1/100th of a second (at 8MHz) instead of 1/50th
;
; Derived from Marc Schroeder's Quick Clear subroutine.

					xdef			_fill_scrn

FILL_SCRN_BASE:		equ				64					; offset from SP, not A6

_fill_scrn:			movem.l			d0-7/a0-6,-(sp)
					lea				fill_scrn_ones,a0
					movem.l			(a0)+,d1-7/a1-6
					movea.l			FILL_SCRN_BASE(sp),a0
					adda.l			#32000,a0
					move.w			#614,d0
fill_scrn_loop:		movem.l			d1-7/a1-6,-(a0)
					dbra			d0,fill_scrn_loop
					movem.l			d1-5,-(a0)
					movem.l			(sp)+,d0-7/a0-6
					rts

fill_scrn_ones:		dcb.l			13,-1


; The start of the register holding the high and middle order bytes of the
; video base address.
; (Used by both get_video_base() and set_video_base().)
VBASE_REG:			equ				$FFFF8201


; UINT16 *get_video_base()
;
; Returns the current frame buffer start address.
;
; Note: The low 8-bits are always zero.
;
; Register Table:
; ---------------
; d0	-	Holds the old system stack pointer from Super().
;		-	Holds the return value of get_video_base().
;		-	Holds the current video base address so that it can be returned by
;			register.
; d3	-	Holds the current video base address.
; d4	-	Holds the old system stack pointer from Super().
; a6	-	Holds the address of the start of the stack frame.

					xdef			_get_video_base

_get_video_base:	link			a6,#0
					movem.l			d1-7/a0-5,-(sp)
					
					; Enter Supervisor Mode.
					clr.l			-(sp)
					move.w			#$20,-(sp)
					trap			#1
					addq.l			#6,sp
					move.l			d0,d4

					jsr				get_video_base
					move.l			d0,d3

					; Leave Supervisor Mode.
					move.l			d4,-(sp)
					move.w			#$20,-(sp)
					trap			#1
					addq.l			#6,sp

					move.l			d3,d0
					movem.l			(sp)+,d1-7/a0-5
					unlk			a6
					rts


; UINT16 *get_video_base()
;
; Returns the current frame buffer start address.
;
; Note: The low 8-bits are always zero. This is why bitshifting within the SR is
;		necessary. Also, supervisor privileges are required.
;
; Register Table:
; ---------------
; d0	-	Holds the current video base address so that it can be returned by
;			register.
; a0	-	Holds the address of the video base register.

					xdef			get_video_base

get_video_base:		movem.l			a0,-(sp)
					clr.l			d0
					movea.l			#VBASE_REG,a0
					movep.w			0(a0),d0
					lsl.l			#8,d0
					movem.l			(sp)+,a0
					rts


;void set_video_base(UINT16 *base)
;
; Sets the frame buffer start address.
;
; Register Table:
; ---------------
; d0	-	Holds the old system stack pointer from Super().
; d1	-	Holds the desired video base address.
; a0	-	Holds the address of the video base register.
; a6	-	Holds the address of the start of the stack frame.

					xdef			_set_video_base

S_VBASE_NEW_ADDR:	equ				8

_set_video_base:	link			a6,#0
					movem.l			d0-7/a0-6,-(sp)

					; Enter Supervisor Mode.
					clr.l			-(sp)
					move.w			#$20,-(sp)
					trap			#1
					addq.l			#6,sp
					
					; Places desired video base address into register.
					; (Low order byte is not stored in the register since it is
					; always zero, which is why bitshifting is necessary.)
					move.l			S_VBASE_NEW_ADDR(a6),d1
					lsr.l			#8,d1
					movea.l			#VBASE_REG,a0
					movep.w			d1,0(a0)

					; Leave Supervisor Mode.
					move.l			d0,-(sp)
					move.w			#$20,-(sp)
					trap			#1
					addq.l			#6,sp

					movem.l			(sp)+,d0-7/a0-6
					unlk			a6
					rts