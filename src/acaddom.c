/**
 * @file acaddom.c
 * @author Academia Team
 * @brief Contains the core functions required for Academia: Dreams of Madness.
 * 
 * @copyright Copyright Academia Team 2023
 */

#include <string.h>

#include "bool.h"
#include "events.h"
#include "input.h"
#include "in_vbl.h"
#include "ikbdcode.h"
#include "ints.h"
#include "model.h"
#include "raster.h"
#include "move.h"
#include "music.h"
#include "mus_vbl.h"
#include "psg.h"
#include "renderer.h"
#include "super.h"
#include "types.h"
#include "vector.h"
#include "vbl.h"

#define COPR_INFO                  "(C) 2023 Academia Team"
#define INFO_BAR_HEIGHT             48
#define INFO_BAR_ENTRY_HEIGHT       16
#define LICENSE_INFO               "Licensed under the GPL-2.0-only"
#define VER_INFO                   "v2023.06.27-NEXT"

/**
 * @brief The minimum number of ticks after which some of the async events can
 * begin.
*/
#define MIN_NUM_TICKS 14

#define MIN_NUM_TICKS_IN_SEC         5
#define MIN_NUM_TICKS_IN_0_8_SEC     4
#define MIN_NUM_TICKS_IN_0_6_SEC     3
#define NUM_TICKS_IN_0_5_SEC        35
#define NUM_TICKS_IN_TWO_SEC       140
#define SCRN_ALIGN                 256

typedef enum
{
	PRIMARY_SCREEN_BUFFER = 0,
	OTHER_SCREEN_BUFFER   = 1
} ScreenBufferChoice;

World  gameWorld;
BOOL   dead = FALSE;

UINT32 timeNow         =  0;

/* Holds the total number of clock ticks that must be reached before handling
synchronous events. */
UINT32 timeDesired     =  0;

UINT32 immunityTimer   = UINT32_MAX;
UINT32 playerMoveTimer = UINT32_MAX;
int    loopCounter     =  1;
int    deathCounter    =  1;
UINT8  gameStart       =  FALSE;

/**
 * @brief Temporarily pauses any game-related operations.
 */
#define game_pause() game_end()

/**
 * @brief Resumes any game-related operations.
 */
#define game_resume() game_start()

/**
 * @brief Sets the frame buffer start address if and only if it is not already
 * set to the desired address.
 * @details It also makes sure the frame buffer has been updated by pausing
 * until the next vertical sync.
 * @param base The desired frame buffer start address.
 */
#define update_video_base(base) \
	if ((UINT16 *)(base) != get_video_base()) \
	{ \
		set_video_base((UINT16 *)(base)); \
		vert_sync(); \
	}

void displayTitleScreen(UINT32 *screenBuffer, BOOL *exitPgrm, int *numPlayers);

/**
 * @brief Copies the contents of an entire screen buffer.
 * 
 * @param dest The destination of the copied screen buffer contents.
 * @param src The source of the copied screen buffer contents.
 */
#define dupScrnBuffer(dest, src) copyScrnBuffer(dest, src, 0, SCRN_MAX_Y)

void mainGameLoop(World *gameWorld, UINT32 *screenBuffer,
				  UINT32 *otherScreenBuffer, UINT32 *worldScreenBuffer,
				  BOOL *quitToTitleScrn, int *numPlayers, BOOL *dead);
void renderGame(ScreenBufferChoice *nextScreenBuffer, UINT32 *screenBuffer, 
				UINT32 *otherScreenBuffer, UINT32 *worldScreenBuffer,
				World *gameWorld);
void copyScrnBuffer(UINT8 *dest, const UINT8 * const src, int startRow,
					int endRow);
void processSync(World *gameWorld, BOOL *dead, UINT32 *timeNow, 
				 UINT32 *timeDesired, UINT32 *immunityTimer,
				 UINT32 *playerMoveTimer, int *loopCounter,
				 int *deathCounter);
void processAsync(BOOL *quitToTitleScrn, World *gameWorld);
void gameOverScreen(UINT32 *screenBuffer, BOOL *playAgain, World *gameWorld);
void prepGameOverScrn(UINT32 *screenBuffer, World *gameWorld,
					  Label *winnerLabel);

void game_end(void);
void game_start(void);
void sync_events_vbl(void);

UINT8	otherFrameBufferMEM[SCRN_BYTES + SCRN_ALIGN];
UINT8	worldFrameBufferMEM[SCRN_BYTES + SCRN_ALIGN];

/**
 * @brief Handles program loop.
 * @details Initializes all three frame buffers. Handles switching between the 
 * Title screen, game screen and Game Over screen. The player can only exit the
 * program from the Title screen. Leaving any other screen will return the
 * player to the Title screen. Only if the player has played the game and died
 * will the Game Over screen ever be shown.
 */
int main(int argc, char **argv)
{
	BOOL         quitToTitleScrn = FALSE;
	BOOL		 playAgain = FALSE;
	BOOL		 exitPgrm = FALSE;
	int 		 numPlayers;

	UINT32 const * screenBuffer = (UINT32 *)get_video_base();

	int otherFBOffset = (SCRN_ALIGN -
						(UINT32)(&otherFrameBufferMEM[0]) % SCRN_ALIGN);
	UINT32 const *otherScreenBuffer =
					(UINT32 *)(&otherFrameBufferMEM[otherFBOffset]);

	int worldFBOffset = (SCRN_ALIGN -
						(UINT32)(&worldFrameBufferMEM[0]) % SCRN_ALIGN);
	UINT32 const *worldScreenBuffer =
					(UINT32 *)(&worldFrameBufferMEM[worldFBOffset]);

	const Vector sysVbl  = vbl_init();
	const Vector sysKybd = initKybd();

	reg_music_vbl();

	while (!exitPgrm)
	{
		if (!playAgain)
		{
			displayTitleScreen(screenBuffer, &exitPgrm, &numPlayers);
		}
		else
		{
			playAgain = FALSE;
		}

		if (!exitPgrm)
		{
			mainGameLoop(&gameWorld, screenBuffer, otherScreenBuffer,
						 worldScreenBuffer, &quitToTitleScrn, &numPlayers,
						 &dead);

			if (!quitToTitleScrn && !isPlayerAlive(gameWorld.mainPlayer))
			{
				gameOverScreen(screenBuffer, &playAgain, &gameWorld);
			}
		}
	}

	set_video_base((UINT16 *)screenBuffer);
	vert_sync();

	unreg_music_vbl();
	restoreKybd(sysKybd);
	vbl_restore(sysVbl);
	stop_sound();

	return 0;
}

/**
 * @brief Displays the title screen for Academia Dreams of Madness.
 * @details Displays the games title "Academia Dreams of Madness" and three 
 * buttons "1-Player", "2-Player" and "FLEE". If the player quits the title 
 * screen by using either 'esc', 'q' or the "FLEE" button the exitPgrm flag is
 * set to TRUE.
 * 
 * @param screenBuffer The framebuffer to plot to.
 * @param exitPgrm Returns by reference TRUE if player quits the title screen. 
 * @param numPlayers Returns by reference 1 for 1-player mode and 2 for 2-player
 * mode.
 */
void displayTitleScreen(UINT32 *screenBuffer, BOOL *exitPgrm, int *numPlayers)
{
	const int X_TITLE           =  27;
	const int Y_TITLE           =  77;

	const int X_1P_BUTTON       = 178;
	const int Y_1P_BUTTON       = 269;
	const int HEIGHT_1P_BUTTON  =  40;
	const int WIDTH_1P_BUTTON   = 136;

	const int X_2P_BUTTON       = 324;
	const int Y_2P_BUTTON       = 269;
	const int HEIGHT_2P_BUTTON  =  40;
	const int WIDTH_2P_BUTTON   = 136;

	const int X_FLEE_BUTTON      = 178;
	const int Y_FLEE_BUTTON      = 319;
	const int HEIGHT_FLEE_BUTTON =  40;
	const int WIDTH_FLEE_BUTTON  = 282;

	const int BORDER_HEIGHT      =   3;
	const int BORDER_WIDTH       =   3;
	const int INFO_BAR_VSPACE    =   0;
	const int NUM_INFO_BAR_TEXT  =   3;
	const int Y_INFO_BAR_START   =   BORDER_HEIGHT;

	IKBD_Scancode kybdKey;
	BOOL          btnActivated 	= FALSE;
	BOOL          tabCycle     	= FALSE;
	BOOL          btnSelected  	= FALSE;
	BOOL          mouseUnselect = FALSE;
	BOOL		  useMouse      = TRUE;

	int          mouseX;
	int          mouseY;

	Menu         titleScrn;
	int          index;

	int          fleeBtnID;
	int          oneBtnID;
	int          twoBtnID;

	update_video_base(screenBuffer);

	initMenu(&titleScrn, FALSE, BORDER_WIDTH, BORDER_HEIGHT);

	oneBtnID = addButton(&titleScrn, X_1P_BUTTON, Y_1P_BUTTON,
						 HEIGHT_1P_BUTTON, WIDTH_1P_BUTTON, "1-Player");

	twoBtnID = addButton(&titleScrn, X_2P_BUTTON, Y_2P_BUTTON,
						 HEIGHT_2P_BUTTON, WIDTH_2P_BUTTON, "2-Player");

	fleeBtnID = addButton(&titleScrn, X_FLEE_BUTTON, Y_FLEE_BUTTON,
						 HEIGHT_FLEE_BUTTON, WIDTH_FLEE_BUTTON, "FLEE");

	addInfoBar(&titleScrn, Y_INFO_BAR_START, INFO_BAR_VSPACE,
			   NUM_INFO_BAR_TEXT, COPR_INFO, VER_INFO, LICENSE_INFO);

	renderMenu(screenBuffer, &titleScrn);
	renderTitle(screenBuffer, X_TITLE, Y_TITLE);

	*exitPgrm = FALSE;
	*numPlayers = 0;
	show_cursor();

	while (!btnActivated && !(*exitPgrm))
	{
		kybdKey = getKey();

		if (kybdKey != NO_KEY)
		{
			switch(kybdKey)
			{
				case IKBD_ESC_SCANCODE:
				case IKBD_Q_SCANCODE:
					*exitPgrm = TRUE;
					break;
				case IKBD_SPACE_SCANCODE:
				case IKBD_RETURN_SCANCODE:
				case IKBD_KP_ENTER_SCANCODE:
					btnActivated = (titleScrn.buttonSel != NO_BTN_SEL);
					break;
				case IKBD_TAB_SCANCODE:
					tabCycle = TRUE;
					break;
				default:
					handleInvalidKeyPress();
			}
		}

		if (tabCycle)
		{
			titleScrn.oldButtonSel = titleScrn.buttonSel;
			titleScrn.buttonSel    = (titleScrn.buttonSel + 1) %
									 titleScrn.buttonFillLevel;

			btnSelected = TRUE;
			tabCycle    = FALSE;
			useMouse    = FALSE;
			hide_cursor();
		}

		if(mouseMoved())
		{
			getMousePos(&mouseX, &mouseY);

			for (index = 0; index < titleScrn.buttonFillLevel && !btnSelected;
				 index++)
			{
				if (btnCollision(mouseX, mouseY, titleScrn.buttons[index]))
				{
					titleScrn.oldButtonSel = titleScrn.buttonSel;
					titleScrn.buttonSel    = index;
					btnSelected            = TRUE;

					titleScrn.buttons[titleScrn.oldButtonSel].selected = FALSE;
					titleScrn.buttons[titleScrn.buttonSel].selected    = TRUE;
				}
			}

			if (!btnSelected && titleScrn.buttonSel != NO_BTN_SEL)
			{
				titleScrn.oldButtonSel = titleScrn.buttonSel;
				titleScrn.buttonSel    = NO_BTN_SEL;
			}

			useMouse = TRUE;
			show_cursor();
		}

		btnActivated = (btnActivated || (mouseClick() && useMouse &&
						titleScrn.buttonSel != NO_BTN_SEL));
		
		/* Make sure buttons aren't re-rendered if button selection has not
		   changed. */
		if (!btnSelected && !mouseUnselect)
		{
			titleScrn.oldButtonSel = titleScrn.buttonSel;
		}

		if ((btnSelected || mouseUnselect) && useMouse)
		{
			hide_cursor();
		}

		renderMenu(screenBuffer, &titleScrn);

		if ((btnSelected || mouseUnselect) && useMouse)
		{
			show_cursor();
		}

		btnSelected   = FALSE;
		mouseUnselect = FALSE;
	}

	if (titleScrn.buttons[fleeBtnID].selected == TRUE) {*exitPgrm = TRUE;}
	if (titleScrn.buttons[oneBtnID].selected == TRUE) {*numPlayers = 1;}
	if (titleScrn.buttons[twoBtnID].selected == TRUE) {*numPlayers = 2;}
	hide_cursor();
}

/**
 * @brief Manages the entire game including asynchronous events and rendering.
 * 
 * @param gameWorld The world object which holds all game data.
 * @param screenBuffer One of the framebuffers to plot to as part of triple
 * buffering.
 * @param otherScreenBuffer One of the framebuffers to plot to as part of triple
 * buffering.
 * @param worldScreenBuffer A framebuffer that holds a copy of all the cells
 * that make up the world.
 * @param quitToTitleScrn A boolean value returned by reference that governs
 * whether the program returns to the title screen or not (as opposed to going
 * to the Game Over screen).
 * @param numPlayers The number of players that are playing the game.
 * @param dead A boolean value indicating whether the player is dead (TRUE) or
 * not (FALSE).
 */
void mainGameLoop(World *gameWorld, UINT32 *screenBuffer,
				  UINT32 *otherScreenBuffer, UINT32 *worldScreenBuffer,
				  BOOL *quitToTitleScrn, int *numPlayers, BOOL *dead)
{
	ScreenBufferChoice nextScreenBuffer = OTHER_SCREEN_BUFFER;

	/* Needs to be set to an expected framebuffer; otherwise, if the current
	framebuffer is one that is being written to, strange graphical artifacts
	will appear. */
	update_video_base(screenBuffer);

	initWorld(gameWorld, *numPlayers);
	renderPlayArea(screenBuffer, gameWorld);
	dupScrnBuffer((UINT8 *)otherScreenBuffer, (UINT8 *)screenBuffer);
	renderWorld(worldScreenBuffer, gameWorld);

	game_start();
	start_music();
	*quitToTitleScrn = FALSE;
	
	while (!(*quitToTitleScrn) && !(*dead))
	{
		processAsync(quitToTitleScrn, gameWorld);

		if (rend_req())
		{
			renderGame(&nextScreenBuffer, screenBuffer, otherScreenBuffer, 
					   worldScreenBuffer, gameWorld);
		}
	}

	stop_music();
	game_end();
	
	*dead = FALSE;
}

/**
 * @brief Handles all asynchronous events.
 * @details This includes keyboard requests for movement and for quitting to the
 * title screen.
 * 
 * @param quitToTitleScrn A boolean value returned by reference that governs
 * whether the program returns to the title screen or not (as opposed to going
 * to the Game Over screen).
 * @param gameWorld The world object which holds all game data.
 */
void processAsync(BOOL *quitToTitleScrn, World *gameWorld)
{
	IKBD_Scancode kybdKey;
	Direction     dirRequest = M_NONE;

	kybdKey = getKey();

	if (kybdKey != NO_KEY)
	{
		switch(kybdKey)
		{
			case IKBD_ESC_SCANCODE:
				pause_music();
				game_pause();

				while ((kybdKey = getKey()) != IKBD_Q_SCANCODE &&
						kybdKey != IKBD_ESC_SCANCODE);
				
				if (kybdKey == IKBD_Q_SCANCODE)
				{
					*quitToTitleScrn = TRUE;
				}
				else
				{
					game_resume();
					resume_music();
				}

				break;
				
			case IKBD_Q_SCANCODE:
				*quitToTitleScrn = TRUE;
				break;
			case IKBD_UP_SCANCODE:
				dirRequest = M_UP;
				break;
			case IKBD_LEFT_SCANCODE:
				dirRequest = M_LEFT;
				break;
			case IKBD_RIGHT_SCANCODE:
				dirRequest = M_RIGHT;
				break;
			case IKBD_DOWN_SCANCODE:
				dirRequest = M_DOWN;
				break;
			default:
				handleInvalidKeyPress();
		}
	}

	if (dirRequest != M_NONE)
	{
		if (playerMoveOpposite(&gameWorld->mainPlayer, dirRequest))
		{
			resetMoveQueue(&gameWorld->mainPlayer.moveQueue);
		}
		else
		{
			setPlayerDir(&gameWorld->mainPlayer, dirRequest);
		}

		dirRequest = M_NONE;
	}
}

/**
 * @brief Handles all synchronous events related to the game.
 * 
 * @param gameWorld The world object which holds all game data.
 * @param dead A boolean value indicating whether the player is dead (TRUE) or
 * not (FALSE).
 * @param timeNow The current value given by a timer.
 * @param timeDesired The time that is desired before most of the synchronous
 * events occur.
 * @param immunityTimer The time that is desired before ending player damage
 * immunity.
 * @param playerMoveTimer The time that is desired before moving a player after
 * a movement request has been accepted.
 * @param loopCounter Keeps track of the number of iterations so that events
 * can occur at the proper times.
 * @param deathCounter The time that is desired before officially declaring a
 * player dead (as opposed to the process of dying).
 */
void processSync(World *gameWorld, BOOL *dead, UINT32 *timeNow, 
				 UINT32 *timeDesired, UINT32 *immunityTimer,
				 UINT32 *playerMoveTimer, int *loopCounter,
				 int *deathCounter)
{
	*timeNow = get_time();

	if (*timeNow > *immunityTimer)
	{
		toggleImmunity(gameWorld->mainPlayer);
		*immunityTimer = UINT32_MAX;
	}

	if (*timeNow > *playerMoveTimer)
	{
		if (movePlayer(gameWorld, &gameWorld->mainPlayer))
		{
			if (handleHazardCollision(gameWorld, &gameWorld->mainPlayer) >= 0)
			{
				*immunityTimer = get_time() + NUM_TICKS_IN_TWO_SEC;
			}

			handleCollectableCollision(gameWorld, &gameWorld->mainPlayer);

			*playerMoveTimer = UINT32_MAX;
		}
	}

	if (*timeNow >= *timeDesired)
	{
		if (isPlayerAlive(gameWorld->mainPlayer))
		{
			updateTrain(gameWorld);

			if (*loopCounter == MIN_NUM_TICKS_IN_0_6_SEC)
			{
				updateFeathers(gameWorld);
			}

			if (*loopCounter == MIN_NUM_TICKS_IN_0_8_SEC)
			{
				updateCar(gameWorld);
			}

			if (*loopCounter == MIN_NUM_TICKS_IN_SEC)
			{
				repopulateWorld(gameWorld);
			}

			if (handleHazardCollision(gameWorld, &gameWorld->mainPlayer) >= 0)
			{
				*immunityTimer = get_time() + NUM_TICKS_IN_TWO_SEC;
			}

			if (playerMayMove(&gameWorld->mainPlayer) &&
				*playerMoveTimer == UINT32_MAX)
			{
				*playerMoveTimer = get_time() + NUM_TICKS_IN_0_5_SEC;
			}
		}
		else
		{
			if (*deathCounter > MIN_NUM_TICKS_IN_0_6_SEC)
			{
				*dead = TRUE;
				*immunityTimer = UINT32_MAX;
				*deathCounter = 1;
			}
			else
			{
				handleDeath();
				(*deathCounter)++;
			}
		}

		if (*loopCounter >= MIN_NUM_TICKS_IN_SEC)
		{
			*loopCounter = 1;
		}
		else
		{
			(*loopCounter)++;
		}

		*timeDesired = get_time() + MIN_NUM_TICKS;
	}
}

/**
 * @brief Handles the rendering of the game onto alternating screen buffers.
 * 
 * @param nextScreenBuffer The screen buffer that should be utilized on screen.
 * @param screenBuffer One of the framebuffers to plot to as part of triple
 * buffering.
 * @param otherScreenBuffer One of the framebuffers to plot to as part of triple
 * buffering.
 * @param worldScreenBuffer A framebuffer that holds a copy of all the cells
 * that make up the world.
 * @param gameWorld The world object which holds all game data.
 */
void renderGame(ScreenBufferChoice *nextScreenBuffer, UINT32 *screenBuffer, 
				UINT32 *otherScreenBuffer, UINT32 *worldScreenBuffer,
				World *gameWorld)
{
	const BOOL IS_SUPER = isSu();

	UINT32 oldSsp;
	int    oldIpl;
	BOOL   RENDER_CELLS;
	BOOL   COPY_CELLS;
	
	if (!IS_SUPER) oldSsp = Su(0);
	oldIpl = set_ipl(MASK_ALL_INTERRUPTS);
	if (!IS_SUPER) Su(oldSsp);

	RENDER_CELLS = gameWorld->renderCells;
	COPY_CELLS   = gameWorld->copyCells;

	if (RENDER_CELLS)
	{
		renderUpdateWorld(worldScreenBuffer, gameWorld);
	}

	if (*nextScreenBuffer == PRIMARY_SCREEN_BUFFER)
	{
		if (COPY_CELLS || RENDER_CELLS)
		{
			copyScrnBuffer((UINT8 *)screenBuffer, (UINT8 *)worldScreenBuffer,
						   getTopBorderHeight(gameWorld->numPlayers),
						   BOTTOM_BORDER - 1);
			renderUpdate((UINT32 *)screenBuffer, gameWorld);
		}

		set_video_base((UINT16 *)screenBuffer);
		*nextScreenBuffer = OTHER_SCREEN_BUFFER;
	}
	else if (*nextScreenBuffer == OTHER_SCREEN_BUFFER)
	{
		if (COPY_CELLS || RENDER_CELLS)
		{
			copyScrnBuffer((UINT8 *)otherScreenBuffer,
						   (UINT8 *)worldScreenBuffer,
						   getTopBorderHeight(gameWorld->numPlayers),
						   BOTTOM_BORDER - 1);
			renderUpdate((UINT32 *)otherScreenBuffer, gameWorld);
		}

		set_video_base((UINT16 *)otherScreenBuffer);
		*nextScreenBuffer = PRIMARY_SCREEN_BUFFER;
	}

	if (COPY_CELLS || RENDER_CELLS)
	{
		if (*nextScreenBuffer == PRIMARY_SCREEN_BUFFER)
		{
			copyScrnBuffer((UINT8 *)screenBuffer, (UINT8 *)otherScreenBuffer, 0,
						   SCRN_MAX_Y);
		}
		else
		{
			copyScrnBuffer((UINT8 *)otherScreenBuffer, (UINT8 *)screenBuffer, 0,
						   SCRN_MAX_Y);
		}

		gameWorld->copyCells   = FALSE;
		gameWorld->renderCells = FALSE;
	}

	if (!IS_SUPER) oldSsp = Su(0);
	set_ipl(oldIpl);
	if (!IS_SUPER) Su(oldSsp);
	vert_sync();
}

/**
 * @brief Copies all the data from one screen buffer to another starting and
 * ending at the given rows.
 * 
 * @param destScreenBuffer The buffer to copy to.
 * @param srcScreenBuffer The buffer to copy from.
 * @param startRow The Row to start copying from (starting at zero).
 * @param endRow The last Row to copy from (starting at zero).
 */
void copyScrnBuffer(UINT8 *dest, const UINT8 * const src, int startRow,
					int endRow)
{
	const int COPY_OFFSET      = startRow * SCRN_LEN_BYTES;
	const int NUM_ROWS_TO_COPY = endRow - startRow + 1;
	const int BYTES_TO_COPY    = NUM_ROWS_TO_COPY * SCRN_LEN_BYTES;

	memcpy(dest + COPY_OFFSET, src + COPY_OFFSET, BYTES_TO_COPY);
}

/**
 * @brief Displays the game over screen for Academia Dreams of Madness.
 * @details Displays a "GAME OVER" message, the players score and 2 buttons,
 * "RETREAT" and "PLAY AGAIN". If the player quits the game over screen by using
 * either 'esc', 'q' or the "retreat" button the playAgain flag is set to FALSE.
 * If the playAgain flag is TRUE the player has selected the "PLAY AGAIN"
 * button.
 * 
 * @param screenBuffer The framebuffer to plot to.
 * @param playAgain Returns by reference FALSE if the game is to return to the 
 * title screen state.
 * @param gameWorld The world object which holds all game data.
 */
void gameOverScreen(UINT32 *screenBuffer, BOOL *playAgain, World *gameWorld)
{
	const int       X_PLAY_AGAIN_BUTTON      = 150;
	const int       Y_PLAY_AGAIN_BUTTON      = 281;
	const int       HEIGHT_PLAY_AGAIN_BUTTON =  40;
	const int       WIDTH_PLAY_AGAIN_BUTTON  = 340;

	const int       X_RETREAT_BUTTON         = 150;
	const int       Y_RETREAT_BUTTON         = 329;
	const int       HEIGHT_RETREAT_BUTTON    =  40;
	const int       WIDTH_RETREAT_BUTTON     = 340;

	const int       X_GAME_OVER              =  82;
	const int       Y_GAME_OVER              =  53;

	Label 			winner;
	IKBD_Scancode 	kybdKey;
	BOOL 			btnActivated    = FALSE;
	BOOL 			tabCycle        = FALSE;
	BOOL 			quitToTitleScrn = FALSE;
	BOOL            btnSelected     = FALSE;
	BOOL         	mouseUnselect 	= FALSE;
	BOOL		 	useMouse    	= TRUE;

	int             mouseX;
	int             mouseY;

	Menu            goverScrn;
	int             index;

	int             paBtnID;

	update_video_base(screenBuffer);

	initMenu(&goverScrn, TRUE, 0, 0);

	paBtnID = addButton(&goverScrn, X_PLAY_AGAIN_BUTTON, Y_PLAY_AGAIN_BUTTON,
						HEIGHT_PLAY_AGAIN_BUTTON, WIDTH_PLAY_AGAIN_BUTTON,
						"PLAY AGAIN");

	addButton(&goverScrn, X_RETREAT_BUTTON, Y_RETREAT_BUTTON,
			  HEIGHT_RETREAT_BUTTON, WIDTH_RETREAT_BUTTON, "RETREAT");

	renderMenu(screenBuffer, &goverScrn);
	renderGameOver(screenBuffer, X_GAME_OVER, Y_GAME_OVER);

	prepGameOverScrn(screenBuffer, gameWorld, &winner);
	show_cursor();

	while (!btnActivated && !quitToTitleScrn)
	{
		kybdKey = getKey();

		if (kybdKey != NO_KEY)
		{
			switch(kybdKey)
			{
				case IKBD_ESC_SCANCODE:
				case IKBD_Q_SCANCODE:
					quitToTitleScrn = TRUE;
					break;
				case IKBD_SPACE_SCANCODE:
				case IKBD_RETURN_SCANCODE:
				case IKBD_KP_ENTER_SCANCODE:
					btnActivated = (goverScrn.buttonSel != NO_BTN_SEL);
					break;
				case IKBD_TAB_SCANCODE:
					tabCycle = TRUE;
					break;
				default:
					handleInvalidKeyPress();
			}
		}

		if (tabCycle)
		{
			goverScrn.oldButtonSel = goverScrn.buttonSel;
			goverScrn.buttonSel    = (goverScrn.buttonSel + 1) %
									 goverScrn.buttonFillLevel;

			btnSelected = TRUE;
			tabCycle    = FALSE;
			useMouse    = FALSE;
			hide_cursor();
		}

		if(mouseMoved())
		{
			getMousePos(&mouseX, &mouseY);

			for (index = 0; index < goverScrn.buttonFillLevel && !btnSelected;
				 index++)
			{
				if (btnCollision(mouseX, mouseY, goverScrn.buttons[index]))
				{
					goverScrn.oldButtonSel = goverScrn.buttonSel;
					goverScrn.buttonSel    = index;
					btnSelected            = TRUE;

					goverScrn.buttons[goverScrn.oldButtonSel].selected = FALSE;
					goverScrn.buttons[goverScrn.buttonSel].selected    = TRUE;
				}
			}

			if (!btnSelected && goverScrn.buttonSel != NO_BTN_SEL)
			{
				goverScrn.oldButtonSel = goverScrn.buttonSel;
				goverScrn.buttonSel    = NO_BTN_SEL;
			}

			useMouse = TRUE;
			show_cursor();
		}

		btnActivated = (btnActivated || (mouseClick() && useMouse &&
						goverScrn.buttonSel != NO_BTN_SEL));
		
		/* Make sure buttons aren't re-rendered if button selection has not
		   changed. */
		if (!btnSelected && !mouseUnselect)
		{
			goverScrn.oldButtonSel = goverScrn.buttonSel;
		}

		if ((btnSelected || mouseUnselect) && useMouse)
		{
			hide_cursor();
		}

		renderMenu(screenBuffer, &goverScrn);

		if ((btnSelected || mouseUnselect) && useMouse)
		{
			show_cursor();
		}

		btnSelected   = FALSE;
		mouseUnselect = FALSE;
	}

	*playAgain = (goverScrn.buttons[paBtnID].selected == TRUE &&
				  !quitToTitleScrn);
	hide_cursor();
}

/**
 * @brief Initializes and renders all the initial objects required by the Game
 * Over Screen.
 * 
 * @param screenBuffer The framebuffer to plot to.
 * @param gameWorld The world object which holds all game data.
 * @param winnerLabel The label that contains a declaration of a winner (for
 * 2-player only). Returned by reference.
 */
void prepGameOverScrn(UINT32 *screenBuffer, World *gameWorld,
					  Label *winnerLabel)
{
	const int       Y_WINNER_LABEL           = 160;
	const int       X_TIED_LABEL             = 240;
	const int       X_YOU_LABEL              = 240;
	const int       X_OTHER_LABEL            = 224;

	const int       X_1P_SCORE_POS           = 262;
	const int       Y_1P_SCORE_POS           = 166;
	const int       X_1P_SCORE_LABEL         = 150;
	const int       Y_1P_SCORE_LABEL         = 166;

	const int       X_MP_1P_SCORE_POS        = 262;
	const int       Y_MP_1P_SCORE_POS        = 200;
	const int       X_MP_1P_SCORE_LABEL      = 150;
	const int       Y_MP_1P_SCORE_LABEL      = 200;

	const int       X_MP_2P_SCORE_POS        = 262;
	const int       Y_MP_2P_SCORE_POS        = 232;
	const int       X_MP_2P_SCORE_LABEL      = 150;
	const int       Y_MP_2P_SCORE_LABEL      = 232;

	if (gameWorld->numPlayers == 1)
	{
		gameWorld->mainPlayer.score.x = X_1P_SCORE_POS;
		gameWorld->mainPlayer.score.y = Y_1P_SCORE_POS;
		gameWorld->mainPlayer.score.label.x = X_1P_SCORE_LABEL;
		gameWorld->mainPlayer.score.label.y = Y_1P_SCORE_LABEL;

		renderLabel((UINT16 *)screenBuffer, &gameWorld->mainPlayer.score.label,
					TRUE);
		renderScore((UINT16 *)screenBuffer, &gameWorld->mainPlayer.score);
	}
	else
	{
		gameWorld->mainPlayer.score.x = X_MP_1P_SCORE_POS;
		gameWorld->mainPlayer.score.y = Y_MP_1P_SCORE_POS;
		gameWorld->mainPlayer.score.label.x = X_MP_1P_SCORE_LABEL;
		gameWorld->mainPlayer.score.label.y = Y_MP_1P_SCORE_LABEL;

		renderLabel((UINT16 *)screenBuffer, &gameWorld->mainPlayer.score.label,
					TRUE);
		renderScore((UINT16 *)screenBuffer, &gameWorld->mainPlayer.score);

		gameWorld->otherPlayer.score.x = X_MP_2P_SCORE_POS;
		gameWorld->otherPlayer.score.y = Y_MP_2P_SCORE_POS;
		gameWorld->otherPlayer.score.label.x = X_MP_2P_SCORE_LABEL;
		gameWorld->otherPlayer.score.label.y = Y_MP_2P_SCORE_LABEL;

		renderLabel((UINT16 *)screenBuffer, &gameWorld->otherPlayer.score.label,
					TRUE);
		renderScore((UINT16 *)screenBuffer, &gameWorld->otherPlayer.score);

		if (gameWorld->mainPlayer.score.value > gameWorld->otherPlayer.score.value) 
		{
			initLabel(winnerLabel, X_YOU_LABEL, Y_WINNER_LABEL, "WINNER: YOU");
		}
		else if (gameWorld->mainPlayer.score.value < gameWorld->otherPlayer.score.value) 
		{
			initLabel(winnerLabel, X_OTHER_LABEL, Y_WINNER_LABEL,
					  "WINNER: OTHER");
		}
		else
		{
			initLabel(winnerLabel, X_TIED_LABEL, Y_WINNER_LABEL, "WINNER: TIE");
		}
		renderLabel((UINT16 *)screenBuffer, winnerLabel, TRUE);
	}
}

/**
 * @brief Handles the cleanup after a game ends.
 */
void game_end(void)
{
	int    oldIpl;

	oldIpl = set_ipl(MASK_ALL_INTERRUPTS);

	if (gameStart)
	{
		vbl_unregister(sync_events_vbl);
		gameStart = FALSE;
	}
	set_ipl(oldIpl);
}

/**
 * @brief Sets the appropriate values for the start of a game.
 */
void game_start(void)
{
	int    oldIpl;

	oldIpl = set_ipl(MASK_ALL_INTERRUPTS);

	if (!gameStart)
	{
		vbl_register(sync_events_vbl);

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
}

/**
 * @brief The function that handles synchronous events within the VBL ISR.
 */
void sync_events_vbl(void)
{
	processSync(&gameWorld, &dead, &timeNow, &timeDesired, &immunityTimer,
				&playerMoveTimer, &loopCounter, &deathCounter);
}