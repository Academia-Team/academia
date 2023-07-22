/**
 * @file tst_sfx.c
 * @author Academia Team
 * @brief It is designed to test the functionality of the effects module.
 * 
 * @copyright Copyright Academia Team 2023
 */

#include "effects.h"
#include "psg.h"
#include "super.h"
#include "test.h"

void testPain();
void testDeath();
void testWalk();
void testTrain();
void testCollect();
void testBeep();

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
	stop_sound();

	run_test(testPain());
	run_test(testDeath());
	run_test(testWalk());
	run_test(testTrain());
	run_test(testCollect());
	run_test(testBeep());

	stop_sound();
}

/**
 * @brief Plays the Pain sound and waits for enter to continue.
 */
void testPain()
{
	UINT32 oldSsp;

	haltAfterEnter(doSu(play_pain(), oldSsp));
}

/**
 * @brief Plays the Death sound and waits for enter to continue.
 */
void testDeath()
{
	UINT32 oldSsp;

	haltAfterEnter(doSu(play_death(), oldSsp));
}

/**
 * @brief Plays the Walking sound and waits for enter to continue.
 */
void testWalk()
{
	UINT32 oldSsp;

	haltAfterEnter(doSu(play_walk(), oldSsp));
}

/**
 * @brief Plays the Train sound and waits for enter to continue.
 */
void testTrain()
{
	UINT32 oldSsp;

	haltAfterEnter(doSu(play_train(), oldSsp));
}

/**
 * @brief Plays the Collecting Collectables sound and waits for enter to
 * continue.
 */
void testCollect()
{
	UINT32 oldSsp;

	haltAfterEnter(doSu(play_collect(), oldSsp));
}

/**
 * @brief Plays the beeping sound and waits for enter to continue.
 */
void testBeep()
{
	UINT32 oldSsp;

	haltAfterEnter(doSu(play_beep(), oldSsp));
}