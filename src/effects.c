/**
 * @file effects.c
 * @author Academia Team
 * @brief Provides different sound effects.
 * 
 * @copyright Copyright Academia Team 2023
 */

#include "effects.h"

UINT8 deathNotesRemaining = NUM_NOTES_IN_DEATH_SFX;

void play_pain(void)
{
	disable_channel(PLAYER_SOUND_CHANNEL);
	set_tone(PLAYER_SOUND_CHANNEL, 1388);
	enable_channel(PLAYER_SOUND_CHANNEL, ON, OFF);
	enable_envelope(PLAYER_SOUND_CHANNEL);
	set_envelope(MAX_ENVELOPE_SHAPE_VAL, 0x0700);
}

void play_death(void)
{
	switch(deathNotesRemaining)
	{
		case 3:
			disable_channel(PLAYER_SOUND_CHANNEL);
			set_tone(PLAYER_SOUND_CHANNEL, 1352);
			enable_channel(PLAYER_SOUND_CHANNEL, ON, OFF);
			enable_envelope(PLAYER_SOUND_CHANNEL);
			set_envelope(0, 0x1000);
			deathNotesRemaining--;
			break;
		case 2:
			disable_channel(PLAYER_SOUND_CHANNEL);
			set_tone(PLAYER_SOUND_CHANNEL, 1704);
			enable_channel(PLAYER_SOUND_CHANNEL, ON, OFF);
			enable_envelope(PLAYER_SOUND_CHANNEL);
			set_envelope(0, 0x1500);
			deathNotesRemaining--;
			break;
		case 1:
			disable_channel(PLAYER_SOUND_CHANNEL);
			set_tone(PLAYER_SOUND_CHANNEL, 3824);
			enable_channel(PLAYER_SOUND_CHANNEL, ON, OFF);
			enable_envelope(PLAYER_SOUND_CHANNEL);
			set_envelope(0, 0x1000);
			deathNotesRemaining = NUM_NOTES_IN_DEATH_SFX;
	}
}

void play_walk(void)
{
	disable_channel(PLAYER_SOUND_CHANNEL);
	set_tone(PLAYER_SOUND_CHANNEL, 1032);
	enable_channel(PLAYER_SOUND_CHANNEL, ON, OFF);
	enable_envelope(PLAYER_SOUND_CHANNEL);
	set_envelope(9, 0x0400);
}

void play_train(void)
{
	disable_channel(OTHER_SOUND_CHANNEL);
	set_tone(OTHER_SOUND_CHANNEL, 306);
	set_noise(0x01);
	enable_channel(OTHER_SOUND_CHANNEL, ON, ON);
	enable_envelope(OTHER_SOUND_CHANNEL);
	set_envelope(4, 0x25FF);
}

void play_collect(void)
{
	disable_channel(PLAYER_SOUND_CHANNEL);
	set_tone(PLAYER_SOUND_CHANNEL, 0xF0);
	enable_channel(PLAYER_SOUND_CHANNEL, ON, OFF);
	enable_envelope(PLAYER_SOUND_CHANNEL);
	set_envelope(9, 0x1700);
}

void play_beep(void)
{
	disable_channel(PLAYER_SOUND_CHANNEL);
	set_tone(PLAYER_SOUND_CHANNEL, 3408);
	enable_channel(PLAYER_SOUND_CHANNEL, ON, OFF);
	enable_envelope(PLAYER_SOUND_CHANNEL);
	set_envelope(MAX_ENVELOPE_SHAPE_VAL, 0x0400);
}