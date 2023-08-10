; Manages the Vertical Blank ISR.
;
; Copyright 2023 Academia Team

						include			bool_asm.i
						include			ints.i
						include			mouse.i

						xdef			_hide_cursor
						xdef			_rend_req
						xdef			_vbl_isr

						xref			_update_music
						xref			_processSync
						xref			_dead
						xref			_gameWorld
						xref			_mouse
						xref			_get_video_base
						xref			_renderCursor
						xref			_isSu
						xref			_Su

						xref			_timeNow
						xref			_timeDesired
						xref			_immunityTimer
						xref			_playerMoveTimer
						xref			_vertTimer
						xref			_oldCursX
						xref			_oldCursY
						xref			_loopCounter
						xref			_deathCounter
						xref			_rendReq
						xref			_gameStart
						xref			_plotMouse


UNSET_CURS_X:			equ				-1
UNSET_CURS_Y:			equ				-1

; void cursor_hide(void);
;
; Brief: Stops the VBL ISR from showing a cursor on the screen.
;
; Register Table
; --------------
; d0	-	Holds a value indicating if the subroutine is currently running in
;			supervisor mode.
;		-	Holds the original system stack pointer.
;		-	Holds the original 68000 interrupt mask.
;		-	Holds the current frame buffer start address.
;		-	Holds the old x coordinate of the mouse.
;		-	Holds the old y coordinate of the mouse.
;		-	Holds the y coordinate of the mouse.
; d4	-	Holds the original system stack pointer.
; d5	-	Holds the original 68000 interrupt mask.
; d6	-	Holds the current frame buffer start address.
; d7	-	Holds a value indicating if the subroutine has entered supervisor
;			mode.
_hide_cursor:			movem.l			d0-d7/a0-a6,-(sp)

						; Enter Supervisor Mode.
						jsr				_isSu
						move.b			d0,d7
						bne				HC_MASK_INTS
						clr.l			-(sp)
						jsr				_Su
						move.l			d0,d4
						addq.l			#4,sp

						; Mask all interrupts.
HC_MASK_INTS:			move.w			#MASK_ALL_INTERRUPTS,-(sp)
						jsr				_set_ipl
						addq.l			#2,sp
						move.w			d0,d5

						; Leave Supervisor Mode.
						tst.b			d7
						bne				HC_GET_FRAMEBUFFER
						move.l			d4,-(sp)
						jsr				_Su
						addq.l			#4,sp

HC_GET_FRAMEBUFFER:		jsr				_get_video_base
						move.l			d0,d6

						; Clear the old mouse position by plotting over it.
						; Only attempt to clear if both the x and y coordinates
						; are not equal to the unset value.
						move.w			_oldCursX,d0
						cmp.w			#UNSET_CURS_X,d0
						bne				HC_CLEAR_CURS
						move.w			_oldCursY,d0
						cmp.w			#UNSET_CURS_Y,d0
						beq				HC_RESET

HC_CLEAR_CURS:			move.w			_oldCursY,-(sp)
						move.w			_oldCursX,-(sp)
						move.l			d6,-(sp)
						jsr				_renderCursor
						addq.l			#8,sp

						; Reset the other mouse related values.
HC_RESET:				move.b			#FALSE,_plotMouse
						move.w			#UNSET_CURS_X,_oldCursX
						move.w			#UNSET_CURS_Y,_oldCursY

						; Enter Supervisor Mode.
						tst.b			d7
						bne				HC_RESTORE_INTS
						clr.l			-(sp)
						jsr				_Su
						move.l			d0,d4
						addq.l			#4,sp

						; Restore previous interrupt mask.
HC_RESTORE_INTS:		move.w			d5,-(sp)
						jsr				_set_ipl
						addq.l			#2,sp

						; Leave Supervisor Mode.
						tst.b			d7
						bne				HC_RETURN
						move.l			d4,-(sp)
						jsr				_Su
						addq.l			#4,sp

HC_RETURN:				movem.l			(sp)+,d0-d7/a0-a6
						rts


; BOOL rend_req(void)
;
; Brief: Returns whether it is appropriate render or not.
;
; Register Table
; --------------
; d0	-	Holds a value indicating if the subroutine is currently running in
;			supervisor mode.
;		-	Holds the original system stack pointer.
;		-	Holds the original 68000 interrupt mask.
;		-	Holds the Boolean value to be returned.
; d4	-	Holds the original system stack pointer.
; d5	-	Holds the original 68000 interrupt mask.
; d6	-	Temporary holding spot for the Boolean value to be returned.
; d7	-	Holds a value indicating if the subroutine has entered supervisor
;			mode.
_rend_req:				movem.l			d1-d7/a0-a6,-(sp)

						; Enter Supervisor Mode.
						jsr				_isSu
						move.b			d0,d7
						bne				R_REQ_MASK_INTS
						clr.l			-(sp)
						jsr				_Su
						move.l			d0,d4
						addq.l			#4,sp

						; Mask all interrupts.
R_REQ_MASK_INTS:		move.w			#MASK_ALL_INTERRUPTS,-(sp)
						jsr				_set_ipl
						addq.l			#2,sp
						move.w			d0,d5

						move.w			_rendReq,d6
						move.w			#FALSE,_rendReq

						; Restore previous interrupt mask.
						move.w			d5,-(sp)
						jsr				_set_ipl
						addq.l			#2,sp

						; Leave Supervisor Mode.
						tst.b			d7
						bne				R_REQ_RETURN
						move.l			d4,-(sp)
						jsr				_Su
						addq.l			#4,sp

R_REQ_RETURN:			move.w			d6,d0
						movem.l			(sp)+,d1-d7/a0-a6
						rts


; void vbl_isr(void)
;
; Brief: Manages all timed events and music.
;
; Register Table
; --------------
; d0	-	Holds the x coordinate of the mouse.
;		-	Holds the y coordinate of the mouse.
;		-	Holds the current frame buffer start address.
; a0	-	Holds the address to the _mouse structure.

_vbl_isr:				movem.l			d0-d7/a0-a6,-(sp)

						addq.l			#1,_vertTimer

						; Since update_music wants the time changed as provided
						; by the vertical blank clock, the change in duration
						; will always be one since it is run by the VBL ISR.
						move.l			#1,-(sp)
						jsr				_update_music
						addq.l			#4,sp
						cmpi.b			#TRUE,_plotMouse
						bne				VBL_HANDLE_SYNC_EVENTS

						; Only handle the mouse if it has actually moved since
						; last checked.
						lea				_mouse,a0
						move.w			MOUSE_X(a0),d0
						cmp.w			_oldCursX,d0
						bne				VBL_HANDLE_MOUSE
						move.w			MOUSE_Y(a0),d0
						cmp.w			_oldCursY,d0
						beq				VBL_HANDLE_SYNC_EVENTS

						; If there is no previous valid cursor position, then
						; nothing should be cleared.
VBL_HANDLE_MOUSE:		cmpi.w			#UNSET_CURS_X,_oldCursX
						bne				VBL_CLR_OLD_MOUSE
						cmpi.w			#UNSET_CURS_Y,_oldCursY
						beq				VBL_SET_OLD_MOUSE_POS

						; Clear the old mouse position by plotting over it.
VBL_CLR_OLD_MOUSE:		move.w			_oldCursY,-(sp)
						move.w			_oldCursX,-(sp)
						jsr				_get_video_base
						move.l			d0,-(sp)
						jsr				_renderCursor
						addq.l			#8,sp

VBL_SET_OLD_MOUSE_POS:	lea				_mouse,a0
						move.w			MOUSE_X(a0),_oldCursX
						move.w			MOUSE_Y(a0),_oldCursY

						; Plot the cursor at its new position.
						move.w			MOUSE_Y(a0),-(sp)
						move.w			MOUSE_X(a0),-(sp)
						jsr				_get_video_base
						move.l			d0,-(sp)
						jsr				_renderCursor
						addq.l			#8,sp

VBL_HANDLE_SYNC_EVENTS:	cmpi.b			#TRUE,_gameStart
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

						; Set rendReq to true before leaving.
VBL_RETURN:				move.w			#TRUE,_rendReq
						movem.l			(sp)+,d0-d7/a0-a6
						rte