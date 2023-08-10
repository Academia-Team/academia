/**
 * @file vbl.c
 * @author Academia Team
 * @brief Manages the Vertical Blank ISR.
 * 
 * @copyright Copyright 2023 Academia Team
 */

#include "bool.h"
#include "input.h"
#include "ints.h"
#include "raster.h"
#include "renderer.h"
#include "super.h"
#include "types.h"
#include "vbl.h"
#include "vector.h"

UINT32 timeNow         =  0;

/* Holds the total number of clock ticks that must be reached before handling
synchronous events. */
UINT32 timeDesired     =  0;

UINT32 immunityTimer   = -1;
UINT32 playerMoveTimer = -1;

/**
 * @brief The number of ticks since the VBL ISR has been registered.
 */
UINT32 vertTimer       =  0;

UINT16 oldCursX;
UINT16 oldCursY;
UINT16 loopCounter     =  1;
UINT16 deathCounter    =  1;
UINT16 rendReq         =  FALSE;
UINT8  gameStart       =  FALSE;
UINT8  plotMouse       =  FALSE;

void reset_rend_req(void);

void hide_cursor(void)
{
	int    oldIpl;

	oldIpl = set_ipl(MASK_ALL_INTERRUPTS);
	
	if (plotMouse)
	{
		renderCursor(get_video_base(), oldCursX, oldCursY);

		plotMouse = FALSE;
	}

	set_ipl(oldIpl);
}

void show_cursor(void)
{
	int    oldIpl;

	oldIpl = set_ipl(MASK_ALL_INTERRUPTS);

	if (!plotMouse)
	{
		renderCursor(get_video_base(), mouse.x, mouse.y);

		oldCursX  = mouse.x;
		oldCursY  = mouse.y;
		plotMouse = TRUE;
	}
	set_ipl(oldIpl);
}

void game_end(void)
{
	int    oldIpl;

	oldIpl = set_ipl(MASK_ALL_INTERRUPTS);
	gameStart = FALSE;
	set_ipl(oldIpl);
}

void game_start(void)
{
	int    oldIpl;

	oldIpl = set_ipl(MASK_ALL_INTERRUPTS);

	/* Only adjust the time desired if and only if it hasn't already been
	assigned a non-zero value. This allows games that have been stopped to be
	resumed without any ill effect. */
	if (timeDesired == 0)
	{
		timeDesired = get_time() + MIN_NUM_TICKS;
	}
	gameStart = TRUE;

	set_ipl(oldIpl);
}

UINT32 get_time(void)
{
	return vertTimer;
}

BOOL rend_req(void)
{
	BOOL returnVal;
	int  oldIpl;

	oldIpl = set_ipl(MASK_ALL_INTERRUPTS);
	returnVal = rendReq;
	rendReq   = FALSE;
	set_ipl(oldIpl);

	return returnVal;
}

/**
 * @brief Removes any request to render.
 */
void reset_rend_req(void)
{
	int    oldIpl;

	oldIpl = set_ipl(MASK_ALL_INTERRUPTS);
	rendReq = FALSE;
	set_ipl(oldIpl);
}

Vector vbl_init(void)
{
	int    oldIpl;
	Vector oldVector;

	oldIpl = set_ipl(MASK_ALL_INTERRUPTS);
	oldVector = install_vector(VBL_VECTOR, vbl_isr);
	set_ipl(oldIpl);

	return oldVector;
}

void vbl_main(void)
{
	vertTimer++;
}

void vbl_restore(Vector sysVblVec)
{
	int    oldIpl;

	oldIpl = set_ipl(MASK_ALL_INTERRUPTS);
	install_vector(VBL_VECTOR, sysVblVec);
	set_ipl(oldIpl);
}

void vert_sync(void)
{
	reset_rend_req();
	while (!rendReq);
}