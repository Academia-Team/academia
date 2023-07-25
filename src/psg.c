/**
 * @file psg.c
 * @author Academia Team
 * @brief Includes low-level functions and constants to interact with the
 * Atari ST's Programmable Sound Generator.
 * 
 * @copyright Copyright Academia Team 2023
 */

#include "bool.h"
#include "num_util.h"
#include "psg.h"
#include "super.h"
#include "types.h"

void write_psg(PsgReg reg, UINT8 val)
{
	volatile UINT8* const REG_SELECT = 0xFFFF8800;
	volatile UINT8* const WRITE_PSG  = 0xFFFF8802;

	if (reg >= MIN_PSG_REG_NUM && reg <= MAX_PSG_REG_NUM)
	{
		*REG_SELECT = reg;
		*WRITE_PSG  = val;
	}
}

UINT8 read_psg(PsgReg reg)
{
	volatile UINT8* const REG_SELECT = 0xFFFF8800;
	volatile UINT8* const READ_PSG   = 0xFFFF8800;

	UINT8  psgData = 0;

	if (reg >= MIN_PSG_REG_NUM && reg <= MAX_PSG_REG_NUM)
	{
		*REG_SELECT = reg;
		psgData     = *READ_PSG;
	}

	return psgData;
}


void set_tone(Channel channel, int tuning)
{
	UINT8 fineTone;
	UINT8 roughTone;

	if (channel >= MIN_CHANNEL_VAL && channel <= MAX_CHANNEL_VAL &&
		tuning >= MIN_TONAL_VAL && tuning <= MAX_TONAL_VAL)
	{
		fineTone   = (UINT8)(tuning);
		roughTone  = (UINT8)(tuning >> 8);

		switch(channel)
		{
			case A_CHANNEL:
				write_psg(A_FINE_TONE_REG, fineTone);
				write_psg(A_ROUGH_TONE_REG, roughTone);
				break;
			case B_CHANNEL:
				write_psg(B_FINE_TONE_REG, fineTone);
				write_psg(B_ROUGH_TONE_REG, roughTone);
				break;
			case C_CHANNEL:
				write_psg(C_FINE_TONE_REG, fineTone);
				write_psg(C_ROUGH_TONE_REG, roughTone);
		}
	}
}

void set_volume(Channel channel, int volume)
{
	if (channel >= MIN_CHANNEL_VAL && channel <= MAX_CHANNEL_VAL &&
		volume >= MIN_VOL_VAL && volume <= MAX_VOL_VAL)
	{
		switch(channel)
		{
			case A_CHANNEL:
				write_psg(A_LEVEL_REG, volume);
				break;
			case B_CHANNEL:
				write_psg(B_LEVEL_REG, volume);
				break;
			case C_CHANNEL:
				write_psg(C_LEVEL_REG, volume);
		}
	}
}

void enable_envelope(Channel channel)
{
	const UINT8 ENABLE_VAR_VOL_MODE = 0x10;

	if (channel >= MIN_CHANNEL_VAL && channel <= MAX_CHANNEL_VAL)
	{
		switch(channel)
		{
			case A_CHANNEL:
				write_psg(A_LEVEL_REG, ENABLE_VAR_VOL_MODE);
				break;
			case B_CHANNEL:
				write_psg(B_LEVEL_REG, ENABLE_VAR_VOL_MODE);
				break;
			case C_CHANNEL:
				write_psg(C_LEVEL_REG, ENABLE_VAR_VOL_MODE);
		}
	}
}

void set_noise(int tuning)
{
	if (tuning >= MIN_NOISE_TONAL_VAL && tuning <= MAX_NOISE_TONAL_VAL)
	{
		write_psg(NOISE_FREQ_REG, (UINT8)(tuning & 0x1F));
	}
}

void set_envelope(int shape, UINT16 sustain)
{
	if (shape >= MIN_ENVELOPE_SHAPE_VAL && shape <= MAX_ENVELOPE_SHAPE_VAL)
	{
		write_psg(FINE_ENVELOPE_REG, (UINT8)(sustain));
		write_psg(ROUGH_ENVELOPE_REG, (UINT8)(sustain >> 8));
		write_psg(SHAPE_ENVELOPE_REG, (UINT8)(shape));
	}
}


void enable_channel(Channel channel, Toggle tone_on, Toggle noise_on)
{
	UINT8 mixerRegVal;

	if (channel >= MIN_CHANNEL_VAL && channel <= MAX_CHANNEL_VAL &&
		(tone_on == 0 || tone_on == 1) && (noise_on == 0 || tone_on == 1))
	{
		mixerRegVal = read_psg(MIXER_REG);

		switch(channel)
		{
			case A_CHANNEL:
				mixerRegVal &= 0366 /* -- --0 --0 */;
				mixerRegVal |= (UINT8)(!noise_on) << 3;
				mixerRegVal |= (UINT8)(!tone_on);
				break;

			case B_CHANNEL:
				mixerRegVal &= 0355 /* -- -0- -0- */;
				mixerRegVal |= (UINT8)(!noise_on) << 4;
				mixerRegVal |= (UINT8)(!tone_on)  << 1;
				break;

			case C_CHANNEL:
				mixerRegVal &= 0333 /* -- 0-- 0-- */;
				mixerRegVal |= (UINT8)(!noise_on) << 5;
				mixerRegVal |= (UINT8)(!tone_on)  << 2;
		}

		write_psg(MIXER_REG, mixerRegVal);
	}
}

void stop_sound()
{
	const BOOL IS_SUPER = isSu();
	UINT32 old_ssp;

	if (!IS_SUPER) old_ssp = Su(0);

	write_psg(A_LEVEL_REG, 0);
	write_psg(B_LEVEL_REG, 0);
	write_psg(C_LEVEL_REG, 0);
	write_psg(MIXER_REG, read_psg(MIXER_REG) | 0077);

	if (!IS_SUPER) Su(old_ssp);
}