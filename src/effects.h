/**
 * @file effects.h
 * @author Academia Team
 * @brief Provides access to different sound effects.
 * 
 * @copyright Copyright Academia Team 2023
 */

#ifndef EFFECTS_H
#define EFFECTS_H

#include "psg.h"

#define PLAYER_SOUND_CHANNEL B_CHANNEL
#define OTHER_SOUND_CHANNEL  C_CHANNEL

#define NUM_NOTES_IN_DEATH_SFX 3

/**
 * @brief Plays the pain sound effect (an ooh sound).
 */
void play_pain(void);

/**
 * @brief Plays the death sound effect (a "wa wa wa" sound with each wa
 * decreasing in frequency every time).
 * @details It must be run three times in order to get the full sound effect.
 * Each call should be separated by an amount of time handled by the caller.
 * @note Only a 0.2sec delay between calls of the function have been tested.
 */
void play_death(void);

/**
 * @brief Plays the walking sound effect (a "plucking" sound).
 */
void play_walk(void);

/**
 * @brief Plays the train horn sound effect.
 */
void play_train(void);

/**
 * @brief Plays the collecting a collectable sound effect (similar to the sound
 * when Mario collects a coin).
 */
void play_collect(void);

/**
 * @brief Plays a deep beeping noise.
 */
void play_beep(void);

#endif
