/**
 * @file vector.h
 * @author Academia Team
 * @brief Allows for the management and installation of ISR vectors.
 * 
 * @copyright Copyright 2023 Academia Team
 */

#ifndef VECTOR_H
#define VECTOR_H

typedef void (*Vector)();
Vector install_vector(int num, Vector vector);

#endif
