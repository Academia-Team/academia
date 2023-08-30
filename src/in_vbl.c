/**
 * @file in_vbl.c
 * @author Academia Team
 * @brief Enables the VBL ISR to manage displaying a cursor on the screen.
 * 
 * @copyright Copyright Academia Team 2023
 */

#include "bool.h"
#include "in_vbl.h"
#include "input.h"
#include "ints.h"
#include "raster.h"
#include "renderer.h"
#include "types.h"
#include "vbl.h"

/**
 * @brief The cursor will move every 0.5 seconds when controlled via the
 * keyboard.
 */
#define TICKS_BETWEEN_CURSOR_MOV 35

BOOL   plotMouse = FALSE;
UINT16 oldCursX;
UINT16 oldCursY;
UINT32 cursorMovTime = UINT32_MAX;

/**
 * @brief The function that will render the mouse cursor within the VBL ISR.
 * @details It also handles any cursor movement from the keyboard.
 * 
 * @details Only does anything if the mouse cursor has been moved since the last
 * time a cursor has been rendered. It plots over the outdated cursor image to
 * remove it and plots a new image at the new location.
 */
void input_vbl(void)
{
	UINT16 *currVideoBase;

	if (kybdMouseMov != M_NONE && cursorMovTime == UINT32_MAX)
	{
		cursorMovTime = get_time() + TICKS_BETWEEN_CURSOR_MOV;
	}

	if (cursorMovTime >= get_time())
	{
		switch(kybdMouseMov)
		{
			case M_LEFT:
				setRelMousePos(-KEYBOARD_M_MOVE_DIST, 0);
				break;
			case M_RIGHT:
				setRelMousePos(+KEYBOARD_M_MOVE_DIST, 0);
				break;
			case M_UP:
				setRelMousePos(0, -KEYBOARD_M_MOVE_DIST);
				break;
			case M_DOWN:
				setRelMousePos(0, +KEYBOARD_M_MOVE_DIST);
				break;
			default:
				cursorMovTime = UINT32_MAX;
				break;
		}

		if (cursorMovTime != UINT32_MAX)
		{
			cursorMovTime += TICKS_BETWEEN_CURSOR_MOV;
		}
	}

	if (!(mouse.x == oldCursX && mouse.y == oldCursY))
	{
		currVideoBase = get_video_base();

		renderCursor(currVideoBase, oldCursX, oldCursY);
		renderCursor(currVideoBase, oldCursX = mouse.x, oldCursY = mouse.y);
	}
}

void hide_cursor(void)
{
	int    oldIpl;

	oldIpl = set_ipl(MASK_ALL_INTERRUPTS);
	
	if (plotMouse)
	{
		renderCursor(get_video_base(), oldCursX, oldCursY);
		vbl_unregister(input_vbl);

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
		vbl_register(input_vbl);

		oldCursX  = mouse.x;
		oldCursY  = mouse.y;
		plotMouse = TRUE;
	}
	set_ipl(oldIpl);
}

BOOL cursor_shown(void)
{
	return plotMouse;
}