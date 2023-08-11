/**
 * @file mus_vbl.c
 * @author Academia Team
 * @brief Enables the VBL ISR to load a note automatically every time it runs.
 * 
 * @copyright Copyright Academia Team 2023
 */

#include "bool.h"
#include "music.h"
#include "mus_vbl.h"
#include "vbl.h"

/**
 * @brief The function that will play the next note within the VBL ISR.
 */
void music_vbl(void)
{
	/* The time elapsed will always be one tick when run inside the VBL ISR
	since the ISR always increments the time elapsed by one. */
	update_music(1);
}

BOOL reg_music_vbl(void)
{
	return vbl_register(music_vbl);
}

BOOL unreg_music_vbl(void)
{
	return vbl_unregister(music_vbl);
}