/**
 * @file tst_psg.c
 * @author Academia Team
 * @brief It is designed to test the functionality of the psg module.
 * 
 * @copyright Copyright Academia Team 2023
 */

#include <limits.h>
#include <osbind.h>
#include <stdio.h>

#include "psg.h"
#include "raster.h"
#include "test.h"
#include "types.h"

void testReadWritePsg();
void testSetTone(Channel channel);
void testMultipleTones(Channel firstChannel, Channel secondChannel);
void outChannelInfo(Channel channel);
void testEnvelope();
void testRepeatingEnvelope();
void testNoise();
void testNoiseWTone();

int main()
{
	off_curs();
	stop_sound();
	
	run_test(testReadWritePsg());
	run_test(testSetTone(A_CHANNEL));
	run_test(testSetTone(B_CHANNEL));
	run_test(testSetTone(C_CHANNEL));
	run_test(testMultipleTones(A_CHANNEL, B_CHANNEL));
	run_test(testMultipleTones(B_CHANNEL, C_CHANNEL));
	run_test(testMultipleTones(A_CHANNEL, C_CHANNEL));
	run_test(testEnvelope());
	run_test(testRepeatingEnvelope());
	run_test(testNoise());
	run_test(testNoiseWTone());

	stop_sound();
	on_curs();
}

/**
 * @brief Tests if values can be written and read to/from the PSG registers.
 * @details This is done by writing specific values and then seeing if the same
 * values can be read back again.
 */
void testReadWritePsg()
{
	const UINT8 INITIAL_VOLUME = 0;
	const UINT8 FINAL_VOLUME   = 31;

	printf
	(
		"Going to write %u to register %i of the PSG (the volume of Channel A)\n",
		INITIAL_VOLUME,
		A_LEVEL_REG
	);

	write_psg(A_LEVEL_REG, INITIAL_VOLUME);

	printf("Value read back: %u\n\n", read_psg(A_LEVEL_REG));


	printf
	(
		"Going to write %u to register %i of the PSG (the volume of Channel A)\n",
		FINAL_VOLUME,
		A_LEVEL_REG
	);

	write_psg(A_LEVEL_REG, FINAL_VOLUME);

	printf("Value read back: %u\n\n", read_psg(A_LEVEL_REG));

	Cconin();
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
	if (channel >= MIN_CHANNEL_VAL && channel <= MAX_CHANNEL_VAL)
	{
		printf("Mixer register before disabling: %u\n", read_psg(MIXER_REG));
		disable_channel(channel);
		printf("Mixer register after disabling: %u\n", read_psg(MIXER_REG));
		set_tone(channel, 248);
		enable_channel(channel, ON, OFF);
		printf("Mixer register after enabling: %u\n", read_psg(MIXER_REG));
		set_volume(channel, 11);
		putchar('\n');

		outChannelInfo(channel);
		putchar('\n');
		Cconin();

		disable_channel(channel);
	}
	else
	{
		puts("The channel provided is invalid.");
		Cconin();
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
	if (firstChannel >= MIN_CHANNEL_VAL && secondChannel <= MAX_CHANNEL_VAL
		&& secondChannel >= MIN_CHANNEL_VAL && secondChannel <= MAX_CHANNEL_VAL
		&& firstChannel != secondChannel)
	{
		disable_channel(firstChannel);
		disable_channel(secondChannel);
		set_tone(firstChannel, 248);
		set_tone(secondChannel, 0x264);
		enable_channel(firstChannel, ON, OFF);
		enable_channel(secondChannel, ON, OFF);
		set_volume(firstChannel, 11);
		set_volume(secondChannel, 11);

		outChannelInfo(firstChannel);
		putchar('\n');

		outChannelInfo(secondChannel);
		putchar('\n');

		Cconin();

		disable_channel(firstChannel);

		outChannelInfo(secondChannel);
		putchar('\n');

		Cconin();

		disable_channel(secondChannel);
	}
	else
	{
		puts("The given channel values were invalid.");
		Cconin();
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

/**
 * @brief Tests to make sure envelope generation is working.
 * @warning The tones emitted by this test are very high pitched.
 */
void testEnvelope()
{
	disable_channel(A_CHANNEL);
	set_tone(A_CHANNEL, 248);
	enable_channel(A_CHANNEL, ON, OFF);
	set_volume(A_CHANNEL, 11);
	putchar('\n');

	outChannelInfo(A_CHANNEL);
	putchar('\n');
	Cconin();

	set_envelope(MAX_ENVELOPE_SHAPE_VAL, UINT16_MAX);
	printf
	(
		"The envelope is set to a shape parameter of 15 and a sustain of %u.\n",
		UINT16_MAX
	);
	puts("Press any key to enable the envelope for Channel A.");
	Cconin();

	enable_envelope(A_CHANNEL);
	puts("Press enter to use a different tone for Channel A.");
	Cconin();

	set_tone(A_CHANNEL, 0x264);
	set_envelope(MAX_ENVELOPE_SHAPE_VAL, ULONG_MAX);
	Cconin();

	disable_channel(A_CHANNEL);
}

/**
 * @brief Tests to make sure a repeating envelope can be stopped by the
 * disable_channel() function.
 */
void testRepeatingEnvelope()
{
	disable_channel(A_CHANNEL);
	set_tone(A_CHANNEL, 0x264);
	enable_channel(A_CHANNEL, ON, OFF);
	enable_envelope(A_CHANNEL);
	set_envelope(12, 0x0500);
	Cconin();

	disable_channel(A_CHANNEL);
}

/**
 * @brief Tests to make sure noise generation works.
 * @note The values used were from section 5.2 of the YM2149 Application Manual
 * and were designed to make an explosion sound.
 */
void testNoise()
{
	disable_channel(A_CHANNEL);
	set_noise(0x1F);
	enable_channel(A_CHANNEL, OFF, ON);
	enable_envelope(A_CHANNEL);
	set_envelope(0x0, 0x3800);
	Cconin();

	disable_channel(A_CHANNEL);
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
 */
void testNoiseWTone()
{
	disable_channel(A_CHANNEL);
	set_tone(A_CHANNEL, 0x264);
	set_noise(0x1F);
	enable_channel(A_CHANNEL, ON, ON);
	enable_envelope(A_CHANNEL);
	set_envelope(0x0, 0x3800);
	Cconin();

	disable_channel(A_CHANNEL);
}