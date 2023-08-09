/**
 * @file vector.c
 * @author Academia Team
 * @brief Allows for the management and installation of ISR vectors.
 * 
 * @copyright Copyright 2023 Academia Team
 */

#include "bool.h"
#include "super.h"
#include "vector.h"

Vector install_vector(int num, Vector vector)
{
	const BOOL IS_SUPER = isSu();

	Vector orig;
	Vector *vectp = (Vector *)((long) num << 2);
	long oldSsp;
	
	if (!IS_SUPER) oldSsp = Su(0);

	orig = *vectp;
	*vectp = vector;

	if (!IS_SUPER) Su(oldSsp);
	return orig;
}