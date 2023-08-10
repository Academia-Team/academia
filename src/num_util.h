/**
 * @file num_util.h
 * @author Academia Team
 * @brief Contains mathematical functions to interact with integral values.
 * 
 * @copyright Copyright Academia Team 2023
 */

#ifndef NUM_UTIL_H
#define NUM_UTIL_H

/**
 * @brief Returns 1 if the given integral value is even; 0 otherwise.
 */
#define isEven(val) ((val & 1) == 0)

/**
 * @brief Returns 1 if the given integral value is odd; 0 otherwise.
 */
#define isOdd(val) (!isEven(val))

/**
 * @brief Swaps the values contained in variables with each other.
 * @param swVal1 One of the variables whose value needs to be swapped.
 * @param swVal2 Another variable whose value needs to be swapped.
 */
#define swap(swVal1, swVal2) \
	swVal1  ^= swVal2; \
	swVal2  ^= swVal1; \
	swVal1  ^= swVal2

/**
 * @brief Generates an integral random number between 0 and rangeMax, inclusive.
 * 
 * @param rangeMax The max limit on the random number generator.
 * @return An integral number between 0 and rangeMax, inclusive.
 */
int random(int rangeMax);

/**
 * @brief Resets the rng to its original state.
 */
void resetRandom(void);

#endif