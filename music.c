/**
 * @file music.c
 * @author Academia Team
 * @brief Provides the ability to manage the playback of music.
 * 
 * @copyright Copyright Academia Team 2023
 */

#include <osbind.h>
#include <stdlib.h>

#include "bool.h"
#include "ints.h"
#include "music.h"
#include "psg.h"
#include "types.h"

int curSongPos = 0;

/**
 * @brief The amount of time remaining till the next note in a song should be
 * played.
 */
UINT32 musHoldTimeRemaining = UINT32_MAX;

BOOL musDisabled = TRUE;
BOOL musPaused   = TRUE;

typedef enum
{
	A_FLAT  = 268,
	A_SHARP = 284,
	B_FLAT  = 253,
	C_FLAT  = 478,
	C_SHARP = 451,
	D_FLAT  = 426,
	D_SHARP = 402,
	E_FLAT  = 379,
	F_FLAT  = 358,
	F_SHARP = 338,
	G_FLAT  = 319,
	G_SHARP = 301,
} Notes;

typedef enum
{
	OCT7 = -3,
	OCT6 = -2,
	OCT5 = -1,
	OCT4 =  0,
	OCT3 =  1,
	OCT2 =  2,
	OCT1 =  3
} Octave;
typedef struct
{
	Notes    note;
	Octave   octave;
	UINT32   duration;
} NoteInfo;

const NoteInfo song[NUM_NOTES_IN_SONG] =
	{
		{B_FLAT,  OCT2, 210},
		{A_SHARP, OCT1, 210},
		{C_SHARP, OCT2, 210},
		{A_FLAT,  OCT3, 210},
		{B_FLAT,  OCT2, 140},
		{A_SHARP, OCT1, 140},
		{C_SHARP, OCT2, 140},
		{A_FLAT,  OCT3, 140},
		{B_FLAT,  OCT2,  70},
		{A_SHARP, OCT1,  70},
		{C_SHARP, OCT2,  70},
		{A_FLAT,  OCT3,  70},
		{B_FLAT,  OCT2,  35},
		{A_SHARP, OCT1,  35},
		{C_SHARP, OCT2,  35},
		{A_FLAT,  OCT3,  70},
		{C_SHARP, OCT4,  70},
		{B_FLAT,  OCT2,  70},
		{F_SHARP, OCT4, 140},
		{A_FLAT,  OCT1, 140},
		{G_SHARP, OCT3, 140}
	};

/**
 * @brief Loads the given note into the PSG and sets the time to hold it
 * accordingly.
 * @note Requires super privileges.
 * 
 * @param noteInfo The information pertaining to the note to be loaded into the
 * PSG.
 */
void load_note(NoteInfo* noteInfo)
{
	disable_channel(MUSIC_CHANNEL);

	if (noteInfo->octave >= 0)
	{
		set_tone(MUSIC_CHANNEL, noteInfo->note << noteInfo->octave);
	}
	else
	{
		set_tone(MUSIC_CHANNEL, noteInfo->note >> abs(noteInfo->octave));
	}

	enable_channel(MUSIC_CHANNEL, ON, OFF);
	set_volume(MUSIC_CHANNEL, MUSIC_VOLUME);

	musHoldTimeRemaining = noteInfo->duration;
}

void start_music()
{
	int oldSsp  = Super(0);
	int origIpl = set_ipl(MASK_ALL_INTERRUPTS);

	curSongPos  = 0;
	musPaused   = FALSE;

	set_ipl(origIpl);
	Super(oldSsp);
}

void pause_music()
{
	int oldSsp  = Super(0);
	int origIpl = set_ipl(MASK_ALL_INTERRUPTS);

	musPaused   = TRUE;

	set_ipl(origIpl);
	Super(oldSsp);
}

void resume_music()
{
	int oldSsp  = Super(0);
	int origIpl = set_ipl(MASK_ALL_INTERRUPTS);

	musPaused   = FALSE;

	set_ipl(origIpl);
	Super(oldSsp);
}

void stop_music()
{
	int oldSsp  = Super(0);
	int origIpl = set_ipl(MASK_ALL_INTERRUPTS);

	curSongPos  = 0;
	musPaused   = TRUE;

	set_ipl(origIpl);
	Super(oldSsp);
}

void update_music(UINT32 time_elapsed)
{
	if (!musPaused)
	{
		if (time_elapsed >= musHoldTimeRemaining)
		{
			curSongPos = (curSongPos + 1) % NUM_NOTES_IN_SONG;
			load_note(&song[curSongPos]);
		}
		else if (musDisabled)
		{
			load_note(&song[curSongPos]);
			musDisabled = FALSE;
		}
		else
		{
			musHoldTimeRemaining -= time_elapsed;
		}
	}
	else
	{
		if (!musDisabled)
		{
			disable_channel(MUSIC_CHANNEL);
			musDisabled = TRUE;
		}
	}
}