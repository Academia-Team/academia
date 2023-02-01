/**
 * @file music.h
 * @author Academia Team
 * @brief Provides the ability to manage the playback of music.
 * 
 * @copyright Copyright Academia Team 2023
 */

#ifndef MUSIC_H
#define MUSIC_H

#include <osbind.h>

#include "psg.h"
#include "types.h"

#define MUSIC_CHANNEL     A_CHANNEL
#define MUSIC_VOLUME      11
#define NUM_NOTES_IN_SONG 21

/**
 * @brief Loads the first note from a song into the PSG.
 */
void start_music();

/**
 * @brief Temporarily halts the playback of music upon the next call to
 * update_music().
 */
void pause_music();

/**
 * @brief Resumes the playback of music upon the next call to update_music().
 */
void resume_music();

/**
 * @brief Halts the playback of music upon the next call to update_music().
 */
void stop_music();

/**
 * @brief Provides the PSG with the next note from a song.
 * @details The song is only advanced if and only if the time elapsed is greater
 * than the duration the current note is supposed to be held for.
 * @note Requires super privileges.
 * 
 * @param time_elapsed The time elapsed since the last call to the function
 * (or any other equivalent functions that affect the playing of music).
 */
void update_music(UINT32 time_elapsed);

#endif
