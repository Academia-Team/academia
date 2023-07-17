/**
 * @file vector.c
 * @author Academia Team
 * @brief Allows for the management and installation of ISR vectors.
 * 
 * @copyright Copyright 2023 Academia Team
 */

#include "super.h"
#include "vector.h"

Vector install_vector(int num, Vector vector)
{
	Vector orig;
	Vector *vectp = (Vector *)((long) num << 2);
	long old_ssp = Su(0);

	orig = *vectp;
	*vectp = vector;

	Su(old_ssp);
	return orig;
}