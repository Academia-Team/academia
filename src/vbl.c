/**
 * @file vbl.c
 * @author Academia Team
 * @brief Manages the Vertical Blank ISR.
 * 
 * @copyright Copyright 2023 Academia Team
 */

#include "bool.h"
#include "types.h"
#include "vbl.h"

#define UNSET_CURS_X  -1
#define UNSET_CURS_Y  -1
#define MIN_NUM_TICKS 14

UINT32 timeNow         =  0;
UINT32 timeDesired     =  0;
UINT32 immunityTimer   = -1;
UINT32 playerMoveTimer = -1;
UINT32 vertTimer       =  0;
UINT16 oldCursX        =  UNSET_CURS_X;
UINT16 oldCursY        =  UNSET_CURS_Y;
UINT16 loopCounter     =  1;
UINT16 deathCounter    =  1;
UINT16 rendReq         =  FALSE;
UINT8  gameStart       =  FALSE;
UINT8  plotMouse       =  FALSE;

UINT32 get_time(void)
{
	return vertTimer;
}