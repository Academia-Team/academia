/**
 * @file psg.h
 * @author Academia Team
 * @brief Includes low-level functions and constants to interact with the
 * Atari ST's Programmable Sound Generator.
 * 
 * @copyright Copyright Academia Team 2023
 */

#ifndef PSG_H
#define PSG_H

#include "toggle.h"
#include "types.h"

#define MIN_PSG_REG_NUM  0
#define MAX_PSG_REG_NUM 15

#define MIN_CHANNEL_VAL A_CHANNEL
#define MAX_CHANNEL_VAL C_CHANNEL

#define MIN_ENVELOPE_SHAPE_VAL 0
#define MAX_ENVELOPE_SHAPE_VAL 15

#define MIN_TONAL_VAL 0
#define MAX_TONAL_VAL 4095

#define MIN_NOISE_TONAL_VAL 0
#define MAX_NOISE_TONAL_VAL 31

#define MIN_VOL_VAL 0
#define MAX_VOL_VAL 15

typedef enum
{
	A_CHANNEL = 0,
	B_CHANNEL = 1,
	C_CHANNEL = 2
} Channel;

typedef enum
{
	A_FINE_TONE_REG    =  0,
	A_ROUGH_TONE_REG   =  1,
	B_FINE_TONE_REG    =  2,
	B_ROUGH_TONE_REG   =  3,
	C_FINE_TONE_REG    =  4,
	C_ROUGH_TONE_REG   =  5,
	NOISE_FREQ_REG     =  6,
	MIXER_REG          =  7,
	A_LEVEL_REG        =  8,
	B_LEVEL_REG        =  9,
	C_LEVEL_REG        = 10,
	FINE_ENVELOPE_REG  = 11,
	ROUGH_ENVELOPE_REG = 12,
	SHAPE_ENVELOPE_REG = 13,
	PORT_A_REG         = 14,
	PORT_B_REG         = 15
} PsgReg;

/**
 * @brief Writes the given byte value (0-255) to the given PSG register (0-15)
 * @details If any invalid parameter is provided, nothing will be written to a
 * PSG register.
 * @note Requires super privileges.
 * 
 * @param reg The register to write to. (0-15)
 * @param val The byte to write to the register (0-255)
 */
void write_psg(PsgReg reg, UINT8 val);

/**
 * @brief Reads the current value stored in the PSG register.
 * 
 * @param reg The register to read from. (0-15)
 * @note Requires super privileges.
 * @return The byte value stored in the given register. If the given register is
 * invalid, zero will be returned.
 */
UINT8 read_psg(PsgReg reg);

/**
 * @brief Loads the tone registers (rough and fine) for the given channel
 * (0=A, 1=B, 2=C) with the given 12-bit tuning.
 * @details If any invalid parameter is provided, no tone registers will be
 * loaded.
 * @note Requires super privileges.
 * 
 * @param channel The channel to set the tone registers for. Any value outside
 * the valid range for channels (0=A, 1=B, 2=C) will be ignored.
 * @param tuning The value to use to set the rough and fine tones for a given
 * channel. The first 8-bits are used to set the fine tone while the next 4-bits
 * are used to set the rough tone. The remaining 4 bits are unused. The value
 * will be ignored if the given value is larger than 12-bits in magnitude or if
 * it is negative.
 */
void set_tone(Channel channel, int tuning);

/**
 * @brief Loads the volume register for the given channel.
 * @details If any invalid parameter is provided, no volume registers will be
 * loaded.
 * @note Requires super privileges.
 * 
 * @param channel The channel to set the volume registers for. Any value outside
 * the valid range for channels (0=A, 1=B, 2=C) will be ignored.
 * @param volume The value to set the volume to. Any value that is not within
 * the range (0-15) will be ignored.
 */
void set_volume(Channel channel, int volume);

/**
 * @brief Enables the currently set envelope to control the volume for the
 * specified channel.
 * @details The volume given will vary depending on what values the envelope
 * generator gives. Enabling the envelope for a specific channel will cause the
 * currently held volume settings for that channel to be lost. If any invalid
 * parameter is provided, no volume registers will be loaded.
 * @note Requires super privileges.
 * 
 * @param channel The channel to set the volume registers for. Any value outside
 * the valid range for channels (0=A, 1=B, 2=C) will be ignored.
 */
void enable_envelope(Channel channel);

/**
 * @brief Loads the noise register with the given tuning.
 * @details If the given tuning value is invalid, nothing will change.
 * @note Requires super privileges.
 * 
 * @param tuning The value to use to set the noise register. Only the first
 * 5-bits are used. If the given tuning value is larger than 5-bits in magnitude
 * or if it is negative, then it will be ignored.
 */
void set_noise(int tuning);

/**
 * @brief Loads the PSG envelope control registers with the given envelope shape
 * and 16-bit sustain.
 * @details If any invalid parameter is provided, no registers will be loaded.
 * @note Requires super privileges.
 * 
 * @param shape The lower four bits are used to control the shape of the
 * envelope. If more than the lowest four bits are set, or if the value is
 * negative, then the given shape will be invalid.
 * @param sustain The lower 8 bits are used to set the envelope fine tone while
 * the upper 8 bits are used to set the envelope rough tone.
 */
void set_envelope(int shape, UINT16 sustain);

/**
 * @brief Turns the given channel’s tone/noise signals on/off (0=off, 1=on).
 * @details If any invalid parameter is provided, nothing will be set. The
 * bits to set the signals in the registers are the complements of tone_on and
 * noise_on. Therefore, bits will be zeroed out in order to enable some of these
 * signals.
 * @note Requires super privileges.
 * 
 * @param channel The channel to set the signals for. Any value outside the
 * valid range for channels (0=A, 1=B, 2=C) will be ignored.
 * @param tone_on Enables/disables (1/0) the tone signal for the channel.
 * @param noise_on Enables/disables (1/0) the noise signal for the channel.
 */
void enable_channel(Channel channel, Toggle tone_on, Toggle noise_on);

/**
 * @brief Disables the given channel’s tone and noise signals.
 * @details If a invalid channel is provided, nothing will be disabled.
 * @note Requires super privileges.
 * 
 * @param channel The channel to set the signals for. Any value outside the
 * valid range for channels (0=A, 1=B, 2=C) will be ignored.
 */
#define disable_channel(channel) \
	set_volume(channel, 0); \
	enable_channel(channel, OFF, OFF)

/**
 * @brief Silences all PSG sound production.
 * @details Due to the way the PSG's registers work, the bits have to be set to
 * one in order to disable the channels.
 * @note Requires super privileges.
 */
void stop_sound();

#endif
