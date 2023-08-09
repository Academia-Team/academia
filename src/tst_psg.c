/**
 * @file tst_psg.c
 * @author Academia Team
 * @brief It is designed to test the functionality of the psg module.
 * 
 * @copyright Copyright Academia Team 2023
 */

#include <limits.h>
#include <stdio.h>

#include "arg_list.h"
#include "input.h"
#include "psg.h"
#include "raster.h"
#include "super.h"
#include "test.h"
#include "tst_hndl.h"
#include "types.h"
#include "vector.h"

void psgTstMgr(void (*tstFunc)(ArgList *args));

void t1ReadWritePsg(ArgList *args);

void t1PlayTone(ArgList *args);
void t2PlayTone(ArgList *args);
void t3PlayTone(ArgList *args);

void t1PlayMTones(ArgList *args);
void t2PlayMTones(ArgList *args);
void t3PlayMTones(ArgList *args);

void t1PlayEnvelope(ArgList *args);
void t2PlayEnvelope(ArgList *args);

void t1PlayNoise(ArgList *args);
void t2PlayNoise(ArgList *args);

void testSetTone(Channel channel);
void testMultipleTones(Channel firstChannel, Channel secondChannel);
void outChannelInfo(Channel channel);

int main()
{
	TestSuiteID suiteID;

	suiteID = registerTestSuite("Test reading and writing values to PSG registers.",
								psgTstMgr);

	registerTestCase(suiteID,
					 "Write and Read from the A channel volume register", NULL,
					 t1ReadWritePsg);

	suiteID = registerTestSuite("Tests playing a tone on the Programmable Sound Generator",
								psgTstMgr);

	registerTestCase(suiteID, "Plays a tone using Channel A.", NULL,
					 t1PlayTone);

	registerTestCase(suiteID, "Plays a tone using Channel B.", NULL,
					 t2PlayTone);

	registerTestCase(suiteID, "Plays a tone using Channel C.", NULL,
					 t3PlayTone);
	
	suiteID = registerTestSuite("Tests playing multiple tones on the Programmable Sound Generator",
								psgTstMgr);

	registerTestCase(suiteID, "Plays two tones using Channel A and B.", NULL,
					 t1PlayMTones);

	registerTestCase(suiteID, "Plays two tones using Channel A and C.", NULL,
					 t2PlayMTones);

	registerTestCase(suiteID, "Plays two tones using Channel B and C.", NULL,
					 t2PlayMTones);

	suiteID = registerTestSuite("Tests envelope generation on the Programmable Sound Generator",
								psgTstMgr);

	registerTestCase(suiteID, "Plays a non-repeating envelope.", NULL,
					 t1PlayEnvelope);

	registerTestCase(suiteID, "Plays a repeating envelope.", NULL,
					 t2PlayEnvelope);

	suiteID = registerTestSuite("Tests noise generation on the Programmable Sound Generator",
								psgTstMgr);

	registerTestCase(suiteID, "Plays a noise.", NULL,
					 t1PlayNoise);

	registerTestCase(suiteID, "Plays a noise with a tone.", NULL,
					 t2PlayNoise);
	
	handleTests();

	return 0;
}

/**
 * @brief Sets up an environment for testing the Programmable Sound Generator.
 * @details It ensures that a test doesn't end until a key is pressed. Also
 * ensures all audio is reset before moving on to the next test.
 * 
 * @param tstFunc The function to test the PSG.
 */
void psgTstMgr(void (*tstFunc)(ArgList *args))
{
	ArgList args;
	Vector origKybd = initKybd();
	IKBD_Scancode scancode;

	initArgList(&args);

	tstFunc(&args);

	while ((scancode = getKey()) == NO_KEY);

	restoreKybd(origKybd);
	stop_sound();
}

/**
 * @brief Tests if values can be written and read to/from the PSG registers.
 * @details This is done by writing specific values and then seeing if the same
 * values can be read back again.
 * 
 * @param args Holds a list of arguments. (Unused)
 */
void t1ReadWritePsg(ArgList *args)
{
	const UINT8 INITIAL_VOLUME = 0;
	const UINT8 FINAL_VOLUME   = 31;

	UINT32      oldSsp;

	printf
	(
		"Going to write %u to register %i of the PSG (the volume of Channel A)\n",
		INITIAL_VOLUME,
		A_LEVEL_REG
	);

	doSu(write_psg(A_LEVEL_REG, INITIAL_VOLUME), oldSsp);

	oldSsp = Su(0);
	printf("Value read back: %u\n\n", read_psg(A_LEVEL_REG));
	Su(oldSsp);


	printf
	(
		"Going to write %u to register %i of the PSG (the volume of Channel A)\n",
		FINAL_VOLUME,
		A_LEVEL_REG
	);

	doSu(write_psg(A_LEVEL_REG, FINAL_VOLUME), oldSsp);

	oldSsp = Su(0);
	printf("Value read back: %u\n\n", read_psg(A_LEVEL_REG));
	Su(oldSsp);
}

/**
 * @brief Plays a tone using Channel A.
 * 
 * @param args Holds a list of arguments. (Unused)
 */
void t1PlayTone(ArgList *args)
{
	testSetTone(A_CHANNEL);
}

/**
 * @brief Plays a tone using Channel B.
 * 
 * @param args Holds a list of arguments. (Unused)
 */
void t2PlayTone(ArgList *args)
{
	testSetTone(B_CHANNEL);
}

/**
 * @brief Plays a tone using Channel C.
 * 
 * @param args Holds a list of arguments. (Unused)
 */
void t3PlayTone(ArgList *args)
{
	testSetTone(C_CHANNEL);
}

/**
 * @brief Plays two tones using Channel A and B.
 * 
 * @param args Holds a list of arguments. (Unused)
 */
void t1PlayMTones(ArgList *args)
{
	testMultipleTones(A_CHANNEL, B_CHANNEL);
}

/**
 * @brief Plays two tones using Channel A and C.
 * 
 * @param args Holds a list of arguments. (Unused)
 */
void t2PlayMTones(ArgList *args)
{
	testMultipleTones(A_CHANNEL, C_CHANNEL);
}

/**
 * @brief Plays two tones using Channel B and C.
 * 
 * @param args Holds a list of arguments. (Unused)
 */
void t3PlayMTones(ArgList *args)
{
	testMultipleTones(B_CHANNEL, C_CHANNEL);
}

/**
 * @brief Tests to make sure envelope generation is working.
 * @warning The tones emitted by this test are very high pitched.
 * 
 * @param args Holds a list of arguments. (Unused)
 */
void t1PlayEnvelope(ArgList *args)
{
	UINT32 oldSsp = Su(0);

	disable_channel(A_CHANNEL);
	set_tone(A_CHANNEL, 248);
	enable_channel(A_CHANNEL, ON, OFF);
	set_volume(A_CHANNEL, 11);

	Su(oldSsp);
	putchar('\n');

	doSu(outChannelInfo(A_CHANNEL), oldSsp);
	putchar('\n');
	getBKey();

	doSu(set_envelope(MAX_ENVELOPE_SHAPE_VAL, UINT16_MAX), oldSsp);
	printf
	(
		"The envelope is set to a shape parameter of 15 and a sustain of %u.\n",
		UINT16_MAX
	);
	puts("Press any key to enable the envelope for Channel A.");
	getBKey();

	doSu(enable_envelope(A_CHANNEL), oldSsp);
	puts("Press enter to use a different tone for Channel A.");
	getBKey();

	doSu(set_tone(A_CHANNEL, 0x264), oldSsp);
	doSu(set_envelope(MAX_ENVELOPE_SHAPE_VAL, ULONG_MAX), oldSsp);
}

/**
 * @brief Tests to make sure a repeating envelope can be stopped by the
 * disable_channel() function.
 *
 * @param args Holds a list of arguments. (Unused)
 */
void t2PlayEnvelope(ArgList *args)
{
	UINT32 oldSsp = Su(0);

	disable_channel(A_CHANNEL);
	set_tone(A_CHANNEL, 0x264);
	enable_channel(A_CHANNEL, ON, OFF);
	enable_envelope(A_CHANNEL);
	set_envelope(12, 0x0500);

	Su(oldSsp);

	puts("Press any key to hopefully stop the envelope.");
	getBKey();

	doSu(disable_channel(A_CHANNEL), oldSsp);
}

/**
 * @brief Tests to make sure noise generation works.
 * @note The values used were from section 5.2 of the YM2149 Application Manual
 * and were designed to make an explosion sound.
 * 
 * @param args Holds a list of arguments. (Unused)
 */
void t1PlayNoise(ArgList *args)
{
	UINT32 oldSsp = Su(0);

	disable_channel(A_CHANNEL);
	set_noise(0x1F);
	enable_channel(A_CHANNEL, OFF, ON);
	enable_envelope(A_CHANNEL);
	set_envelope(0x0, 0x3800);

	Su(oldSsp);
}

/**
 * @brief Tests to make sure noise generation and tone generation work
 * simultaneously.
 * @details The tonal values from the testNoise() and testMultipleTones()
 * functions were used so that the results could be better compared and
 * interpreted.
 * @note The noise values used were from section 5.2 of the YM2149 Application
 * Manual and were designed to make an explosion sound. However, due to the
 * introduction of the tone, it sounds more like a gunshot instead.
 * 
 * @param args Holds a list of arguments. (Unused)
 */
void t2PlayNoise(ArgList *args)
{
	UINT32 oldSsp = Su(0);

	disable_channel(A_CHANNEL);
	set_tone(A_CHANNEL, 0x264);
	set_noise(0x1F);
	enable_channel(A_CHANNEL, ON, ON);
	enable_envelope(A_CHANNEL);
	set_envelope(0x0, 0x3800);

	Su(oldSsp);
}

/**
 * @brief Tests to make sure tones are set properly and that basic PSG
 * functions, such as enable/disable_channel() work.
 * @details This is done by using a tonal value of 248 for the given channel and
 * checking to see if the appropriate tone is outputted.
 * @note The tonal value for the channel was gathered from Tutorial 5.
 * 
 * @param channel The channel to test setting a tone in.
 */
void testSetTone(Channel channel)
{
	UINT32 oldSsp;

	if (channel >= MIN_CHANNEL_VAL && channel <= MAX_CHANNEL_VAL)
	{
		oldSsp = Su(0);

		printf("Mixer register before disabling: %u\n", read_psg(MIXER_REG));
		disable_channel(channel);
		printf("Mixer register after disabling: %u\n", read_psg(MIXER_REG));
		set_tone(channel, 248);
		enable_channel(channel, ON, OFF);
		printf("Mixer register after enabling: %u\n", read_psg(MIXER_REG));
		set_volume(channel, 11);
		putchar('\n');

		outChannelInfo(channel);

		Su(oldSsp);

		putchar('\n');
	}
	else
	{
		puts("The channel provided is invalid.");
	}
}

/**
 * @brief Tests to make sure multiple tones can be played at the same time in
 * different channels using the PSG functions.
 * @details This is done by using a tonal value of 248 for the first channel and
 * a tonal value of 0x264 (Fine tone: 100; Course tone: 2) for the second
 * channel. Both channels are enabled at the same time with the same volume to
 * see if any of the functions used prevents one of the tones from being
 * produced by the PSG. Then, the first channel is disabled while the second
 * channel continues on to ensure that disabling one channel doesn't disable any
 * others.
 * @note The tonal value for the first channel was gathered from Tutorial 5
 * while the value for the second channel was something that I stumbled upon
 * during the tutorial.
 * 
 * @param firstChannel One of the channels to play a tone in. Cannot be the same
 * as the secondChannel.
 * @param secondChannel One of the channels to play a tone in. Cannot be the
 * same as the firstChannel.
 */
void testMultipleTones(Channel firstChannel, Channel secondChannel)
{
	UINT32 oldSsp;

	if (firstChannel >= MIN_CHANNEL_VAL && secondChannel <= MAX_CHANNEL_VAL
		&& secondChannel >= MIN_CHANNEL_VAL && secondChannel <= MAX_CHANNEL_VAL
		&& firstChannel != secondChannel)
	{
		oldSsp = Su(0);

		disable_channel(firstChannel);
		disable_channel(secondChannel);
		set_tone(firstChannel, 248);
		set_tone(secondChannel, 0x264);
		enable_channel(firstChannel, ON, OFF);
		enable_channel(secondChannel, ON, OFF);
		set_volume(firstChannel, 11);
		set_volume(secondChannel, 11);

		Su(oldSsp);

		doSu(outChannelInfo(firstChannel), oldSsp);
		putchar('\n');

		doSu(outChannelInfo(secondChannel), oldSsp);
		putchar('\n');

		getBKey();

		doSu(disable_channel(firstChannel), oldSsp);

		doSu(outChannelInfo(secondChannel), oldSsp);
		putchar('\n');
	}
	else
	{
		puts("The given channel values were invalid.");
	}
}

/**
 * @brief Outputs the register information for the given channel.
 * @details The information includes the current fine tone, rough tone, and
 * volume.
 * 
 * @param channel The channel to output the information of.
 */
void outChannelInfo(Channel channel)
{
	switch(channel)
	{
		case A_CHANNEL:
			puts("A channel:");
			printf("Fine Tone: %i\n", read_psg(A_FINE_TONE_REG));
			printf("Rough Tone: %i\n", read_psg(A_ROUGH_TONE_REG));
			printf("Volume: %i\n", read_psg(A_LEVEL_REG));
			break;
		case B_CHANNEL:
			puts("B channel:");
			printf("Fine Tone: %i\n", read_psg(B_FINE_TONE_REG));
			printf("Rough Tone: %i\n", read_psg(B_ROUGH_TONE_REG));
			printf("Volume: %i\n", read_psg(B_LEVEL_REG));
			break;
		case C_CHANNEL:
			puts("C channel:");
			printf("Fine Tone: %i\n", read_psg(C_FINE_TONE_REG));
			printf("Rough Tone: %i\n", read_psg(C_ROUGH_TONE_REG));
			printf("Volume: %i\n", read_psg(C_LEVEL_REG));
			break;
	}
}