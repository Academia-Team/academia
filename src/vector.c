/**
 * @file vector.c
 * @author Academia Team
 * @brief Allows for the management and installation of ISR vectors.
 * 
 * @copyright Copyright 2023 Academia Team
 */

#include <osbind.h>
#include "vector.h"

Vector install_vector(int num, Vector vector)
{
	Vector orig;
	Vector *vectp = (Vector *)((long) num << 2);
	long old_ssp = Super(0);

	orig = *vectp;
	*vectp = vector;

	Super(old_ssp);
	return orig;
}