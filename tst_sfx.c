/**
 * @file tst_sfx.c
 * @author Academia Team
 * @brief It is designed to test the functionality of the effects module.
 * 
 * @copyright Copyright Academia Team 2023
 */

#include <osbind.h>

#include "effects.h"
#include "psg.h"
#include "test.h"

void testPain();
void testDeath();
void testWalk();
void testTrain();
void testCollect();

/**
 * @brief Waits for enter to be pressed after a function call and causes all
 * sounds to stop playing.
 * @param func_call The function call to wait for.
 */
#define haltAfterEnter(func_call) \
	func_call; \
	Cconin(); \
	stop_sound()

int main()
{
	off_curs();
	stop_sound();

	run_test(testPain());
	run_test(testDeath());
	run_test(testWalk());
	run_test(testTrain());
	run_test(testCollect());

	stop_sound();
	on_curs();
}

/**
 * @brief Plays the Pain sound and waits for enter to continue.
 */
void testPain()
{
	haltAfterEnter(play_pain());
}

/**
 * @brief Plays the Death sound and waits for enter to continue.
 */
void testDeath()
{
	haltAfterEnter(play_death());
}

/**
 * @brief Plays the Walking sound and waits for enter to continue.
 */
void testWalk()
{
	haltAfterEnter(play_walk());
}

/**
 * @brief Plays the Train sound and waits for enter to continue.
 */
void testTrain()
{
	haltAfterEnter(play_train());
}

/**
 * @brief Plays the Collecting Collectables sound and waits for enter to
 * continue.
 */
void testCollect()
{
	haltAfterEnter(play_collect());
}