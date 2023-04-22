/**
 * @file tst_mus.c
 * @author Academia Team
 * @brief It is designed to test the functionality of the music module.
 * 
 * @copyright Copyright Academia Team 2023
 */

#include <osbind.h>
#include <stdio.h>

#include "music.h"
#include "psg.h"
#include "test.h"
#include "types.h"

void playSong();
UINT32 getTime();

int main()
{
	off_curs();
	stop_sound();

	run_test(playSong());

	stop_sound();
	on_curs();
}

/**
 * @brief Tests the music module by playing a song until the 'q' key is pressed.
 */
void playSong()
{
	UINT32 timeMusUpdated;

	printf("Press q to stop playing the song\n");
	start_music();
	timeMusUpdated = getTime();
	
	do
	{
		update_music(getTime() - timeMusUpdated);
		timeMusUpdated = getTime();
	} while (Cconis() ? (Cnecin() & 0xFF) != 'q' : TRUE);
}

/**
 * @brief Returns the current time provided by the system clock.
 * 
 * @return The current system clock value as a UINT32.
 */
UINT32 getTime()
{
	UINT32 curTime;
	UINT32 *timer = (UINT32 *)0x462;
	UINT32 oldSsp;

	oldSsp = Super(0);
	curTime = *timer;
	Super(oldSsp);

	return curTime;
}