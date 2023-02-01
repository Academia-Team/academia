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
 * @note Requires super privileges.
 */
void play_pain();

/**
 * @brief Plays the death sound effect (a "wa wa wa" sound with each wa
 * decreasing in frequency every time).
 * @details It must be run three times in order to get the full sound effect.
 * Each call should be separated by an amount of time handled by the caller.
 * @note Only a 0.2sec delay between calls of the function have been tested.
 * 
 * @note Requires super privileges.
 */
void play_death();

/**
 * @brief Plays the walking sound effect (a "plucking" sound).
 * 
 * @note Requires super privileges.
 */
void play_walk();

/**
 * @brief Plays the train horn sound effect.
 * 
 * @note Requires super privileges.
 */
void play_train();

/**
 * @brief Plays the collecting a collectable sound effect (similar to the sound
 * when Mario collects a coin).
 * 
 * @note Requires super privileges.
 */
void play_collect();

/**
 * @brief Plays a deep beeping noise.
 * 
 * @note Requires super privileges.
 */
void play_beep();

#endif
