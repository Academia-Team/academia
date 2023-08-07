/**
 * @file tst_rast.c
 * @author Academia Team
 * @brief Contains constants and functions designed to help test raster
 * functions.
 * 
 * @copyright Copyright Academia Team 2023
 */

#ifndef TST_RAST_H
#define TST_RAST_H

#include "arg_list.h"
#include "bool.h"

#define CLEAR_ON  TRUE
#define CLEAR_OFF FALSE

#define DESTRUCT_ON  TRUE
#define DESTRUCT_OFF FALSE

#define BLACK_SCREEN_ON  TRUE
#define BLACK_SCREEN_OFF FALSE

#define GRID_DOTS_ON  TRUE
#define GRID_DOTS_OFF FALSE

/**
 * @brief Sets up a blank white screen for testing the raster functions.
 * 
 * @param tstFunc The function to test the raster functions.
 */
void rastTstWhite(void (*tstFunc)(ArgList *args));

/**
 * @brief Sets up a blank white screen for testing the raster functions and
 * configures the functions such that any existing imagery doesn't get
 * destroyed.
 * 
 * @param tstFunc The function to test the raster functions.
 */
void rastTstWhitePerserve(void (*tstFunc)(ArgList *args));

/**
 * @brief Sets up a white screen with uniformly distributed dots for testing the
 * raster functions.
 * 
 * @param tstFunc The function to test the raster functions.
 */
void rastGDTstWhite(void (*tstFunc)(ArgList *args));

/**
 * @brief Sets up a blank black screen for testing the raster functions.
 * 
 * @param tstFunc The function to test the raster functions.
 */
void rastTstBlack(void (*tstFunc)(ArgList *args));

/**
 * @brief Sets up a blank black screen for testing the raster functions and
 * configures the functions such that any existing imagery doesn't get
 * destroyed.
 * 
 * @param tstFunc The function to test the raster functions.
 */
void rastGDTstBlack(void (*tstFunc)(ArgList *args));

/**
 * @brief Sets up a black screen with uniformly distributed dots for testing the
 * raster functions.
 * 
 * @param tstFunc The function to test the raster functions.
 */
void rastTstBlackPerserve(void (*tstFunc)(ArgList *args));

#endif
