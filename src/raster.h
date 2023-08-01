/**
 * @file raster.h
 * @author Academia Team
 * @brief Contains functions and macros designed to allow rasters to be
 * plotted to an area in memory for use by the Atari ST's monochrome screen.
 * 
 * @copyright Copyright Academia Team 2023
 */

#ifndef RASTER_H
#define RASTER_H

#include "bool.h"
#include "num_util.h"
#include "scrn.h"
#include "types.h"

/**
 * @brief The maximum value for the x coordinate (in pixels) for a 32-bit wide
 * raster image such that the entire image is still visible on the Atari ST's
 * monochrome screen.
 */
#define RAST32_MAX_VIS_X 608

/**
 * @brief A value for the x coordinate (in pixels) for a 32-bit wide raster
 * image such that the image would be horizontally centered on the Atari ST's
 * monochrome screen.
 */
#define RAST32_MID_VIS_X 304

/**
 * @brief The value for the x coordinate (in pixels) for a 32-bit wide raster
 * image such that half of the image is cropped off from the left.
 */
#define RAST32_LHALF_X -16

/**
 * @brief The value for the x coordinate (in pixels) for a 32-bit wide raster
 * image such that half of the image is cropped off from the right.
 */
#define RAST32_RHALF_X 624

/**
 * @brief The minimum value for the x coordinate (in pixels) for a 32-bit wide
 * raster image such that part of the image is still visible on the Atari ST's
 * monochrome screen.
 */
#define RAST32_MIN_X -31


/**
 * @brief The maximum value for the x coordinate (in pixels) for a 16-bit wide
 * raster image such that the entire image is still visible on the Atari ST's
 * monochrome screen.
 */
#define RAST16_MAX_VIS_X 624

/**
 * @brief The value for the x coordinate (in pixels) for a 16-bit wide raster
 * image such that half of the image is cropped off from the left.
 */
#define RAST16_LHALF_X -8

/**
 * @brief The value for the x coordinate (in pixels) for a 16-bit wide raster
 * image such that half of the image is cropped off from the right.
 */
#define RAST16_RHALF_X 632

/**
 * @brief A value for the x coordinate (in pixels) for a 16-bit wide raster
 * image such that the image would be horizontally centered on the Atari ST's
 * monochrome screen.
 */
#define RAST16_MID_VIS_X 312

/**
 * @brief The minimum value for the x coordinate (in pixels) for a 16-bit wide
 * raster image such that part of the image is still visible on the Atari ST's
 * monochrome screen.
 */
#define RAST16_MIN_X -15


/**
 * @brief The maximum value for the x coordinate (in pixels) for a 8-bit wide
 * raster image such that the entire image is still visible on the Atari ST's
 * monochrome screen.
 */
#define RAST8_MAX_VIS_X 632

/**
 * @brief A value for the x coordinate (in pixels) for a 8-bit wide raster
 * image such that the image would be horizontally centered on the Atari ST's
 * monochrome screen.
 */
#define RAST8_MID_VIS_X 316


/**
 * @brief The minimum value for the x coordinate (in pixels) for a 16-bit wide
 * raster image such that part of the image is still visible on the Atari ST's
 * monochrome screen.
 */
#define RAST8_MIN_X -7

/**
 * @brief A value for the y coordinate (in pixels) for a 32 px high raster
 * image such that the image would be vertically centered on the Atari ST's
 * monochrome screen.
 */
#define RAST32H_MID_VIS_Y 184

/**
 * @brief The maximum value for the y coordinate (in pixels) for a 32 px high
 * raster image such that the entire image is still visible on the Atari ST's
 * monochrome screen.
 */
#define RAST32H_MAX_VIS_Y 368

/**
 * @brief The value for the y coordinate (in pixels) for a 32 px high raster
 * image such that half of the image is cropped off from the top.
 */
#define RAST32H_THALF_Y -16

/**
 * @brief The value for the y coordinate (in pixels) for a 32 px high raster
 * image such that half of the image is cropped off from the bottom.
 */
#define RAST32H_BHALF_Y 384

/**
 * @brief The minimum value for the y coordinate (in pixels) for a 32 px high
 * raster image such that part of the image is still visible on the Atari ST's
 * monochrome screen.
 */
#define RAST32H_MIN_Y -31


/**
 * @brief A value for the y coordinate (in pixels) for a 16 px high raster
 * image such that the image would be vertically centered on the Atari ST's
 * monochrome screen.
 */
#define RAST16H_MID_VIS_Y 192

/**
 * @brief The maximum value for the y coordinate (in pixels) for a 16 px high
 * raster image such that the entire image is still visible on the Atari ST's
 * monochrome screen.
 */
#define RAST16H_MAX_VIS_Y 384

/**
 * @brief The value for the y coordinate (in pixels) for a 16 px high raster
 * image such that half of the image is cropped off from the top.
 */
#define RAST16H_THALF_Y -8

/**
 * @brief The value for the x coordinate (in pixels) for a 16 px high raster
 * image such that half of the image is cropped off from the bottom.
 */
#define RAST16H_BHALF_Y 392

/**
 * @brief The minimum value for the y coordinate (in pixels) for a 16 px high
 * raster image such that part of the image is still visible on the Atari ST's
 * monochrome screen.
 */
#define RAST16H_MIN_Y -15


/**
 * @brief Plots a pixel at the given coordinates on the screen.
 * @details Nothing will be plotted if the given x and y value are out of
 * range. In other words, they cannot be negative or greater than the size
 * of the screen.
 * 
 * A pixel will always be plotted no matter what the colour of
 * the background is. If the background is black, a white pixel will be plotted
 * and vice versa.
 * 
 * @param base The location in memory to plot at.
 * @param x The column to plot a pixel (starting at pixel zero).
 * @param y The row to plot a pixel (starting at pixel zero).
 */
void plot_px(UINT8 *base, int x, int y);

/**
 * @brief Plots a horizontal line.
 * @details The horizontal line will be plotted from the pixels defined by
 * x1 and x2 inclusive. The y coordinate cannot reference a height on the
 * screen that is out of bounds (either negative or greater than the furthest
 * down pixel position). Otherwise, no line will be plotted on the screen.
 * 
 * If both x positions are out of range, but have opposing sign, then a line
 * will be plotted that takes up the entire length of the screen. However, if
 * only one of the x values are out of range, then it will adjust that value to
 * the closest on screen valid pixel position. In the case of a negative x
 * value, for instance, it will replace that value with a zero. Likewise, for a
 * value greater than the largest horizontal pixel position on screen, it will
 * replace that value with the largest valid pixel position. However, in the
 * case of both x values being out of range and having the same sign, no line
 * will be plotted. The x values can be specified in any order irregardless of
 * which value has greater magnitude. If they have the same magnitude, then a
 * singular point will be plotted on screen at the given x and y coordinates.
 * 
 * @param base The location in memory to plot at.
 * @param x1 The column to start plotting the line from (in pixels starting at
 * zero).
 * @param x2 The column to stop plotting the line from (in pixels starting at
 * zero).
 * @param y The row in which to plot the horizontal line (in pixels starting at
 * zero).
 */
void hline(UINT32 *base, int x1, int x2, int y);

/**
 * @brief Plots a 32-bit wide bitmap of any height.
 * @details The bitmap pointed to by the bitmap pointer will be plotted starting
 * at its top-left corner at the given x and y pixel coordinates. It is possible
 * to have a negative x and y coordinate, as even if the plotting begins in an
 * invalid region, something will still be drawn as long as the coordinates
 * aren't too far out of range. With a negative x coordinate, the image will
 * have part of its left side cropped out. A negative x coordinate is allowed
 * only until it causes all 32-bits to be lost from the image. In that case,
 * no image will be plotted at all. Likewise, a positive x coordinate which
 * is large enough to prevent all 32-bits of the image to be plotted will result
 * in the image being cropped from the right.
 * 
 * A negative y coordinate is allowed as long as the height of the image would
 * mean that at least part of the image would be plotted on screen. Any x values
 * or y values that exceed the size of the screen will also causes no image to
 * be plotted. Similarly, if a height is given that is below one, nothing will
 * be plotted. However, if the height exceeds the length of the screen, only
 * the portion of the image that fits the screen will be plotted.
 * 
 * If the destructive flag is set to false, then the given image will be
 * overlayed in the desired location. Otherwise, anything that was plotted
 * beforehand in the region where the image is supposed to be placed will be
 * destroyed.
 * 
 * @warning Extreme caution needs to be taken with the height parameter, as it
 * is impossible to confirm if it exceeds any upper bound. If a height is given
 * that is greater than the actual height of the bitmap, then it may corrupt
 * part of memory.
 * 
 * @param base The location in memory to plot at.
 * @param x The left-most column to begin to plot the raster (in pixels starting
 * at zero).
 * @param y The top-most row to begin to plot the raster (in pixels starting at
 * zero).
 * @param height The height of the bitmap. Must be one or greater.
 * @param bitmap The bitmap that is to be plotted on screen.
 * @param destructive When true, indicates that any pre-existing drawings in the
 * region where the bitmap is being placed should be destroyed. Otherwise, the
 * pixels that are already there will be kept and the bitmap will be overlayed
 * in the region.
 * @param blackScreen When true, indicates that the raster is to be printed on a
 * black background. This will do an XOR with the black screen resulting in the 
 * bitmap being shown in white on the black background.
 */
void plot_rast32(UINT32 *base, int x, int y, int height, const UINT32 *bitmap, 
				 BOOL destructive, BOOL blackScreen);

/**
 * @brief Plots a 32-bit wide alpha bitmap of any height.
 * @details The alpha bitmap pointed to by the bitmap pointer will be applied to
 * the screen starting at its top-left corner at the given x and y pixel 
 * coordinates. It is possible to have a negative x and y coordinate, as even if
 * the plotting begins in an invalid region, something will still be applied as 
 * long as the coordinates aren't too far out of range. With a negative x 
 * coordinate, the alpha will have part of its left side cropped out. A negative
 * x coordinate is allowed only until it causes all 32-bits to be lost from the 
 * alpha. In that case, no alpha will be plotted at all. Likewise, a positive x 
 * coordinate which is large enough to prevent all 32-bits of the alpha to be 
 * plotted will result in the alpha being cropped from the right.
 * 
 * A negative y coordinate is allowed as long as the height of the alpha would
 * mean that at least part of the alpha would be applied to the screen. Any x 
 * values or y values that exceed the size of the screen will also causes no 
 * alpha to be plotted. Similarly, if a height is given that is below one, 
 * nothing will be plotted. However, if the height exceeds the length of the 
 * screen, only the portion of the alpha that fits the screen will be plotted.
 * 
 * Note that for the alpha bitmap, all pixels which are black will set that 
 * region of the screen. All white parts of the bitmap will clear that region of
 * the screen. This allows removal of the background upon which a sprite is to
 * be printed so that the white parts of the sprite remain white.
 * 
 * @param base The location in memory to plot at.
 * @param x The left-most column to begin to plot the alpha raster (in pixels 
 * starting at zero).
 * @param y The top-most row to begin to plot the alpha raster (in pixels 
 * starting at zero).
 * @param height The height of the alpha bitmap. Must be one or greater.
 * @param bitmap The alpha bitmap that is to be plotted on screen.
 */
void plot_alpha(UINT32 *base, int x, int y, int height, const UINT32 *bitmap);

/**
 * @brief Plots a 16-bit wide bitmap of any height.
 * @details The bitmap pointed to by the bitmap pointer will be plotted starting
 * at its top-left corner at the given x and y pixel coordinates. It is possible
 * to have a negative x and y coordinate, as even if the plotting begins in an
 * invalid region, something will still be drawn as long as the coordinates
 * aren't too far out of range. With a negative x coordinate, the image will
 * have part of its left side cropped out. A negative x coordinate is allowed
 * only until it causes all 16-bits to be lost from the image. In that case,
 * no image will be plotted at all. Likewise, a positive x coordinate which
 * is large enough to prevent all 16-bits of the image to be plotted will result
 * in the image being cropped from the right.
 * 
 * A negative y coordinate is allowed as long as the height of the image would
 * mean that at least part of the image would be plotted on screen. Any x values
 * or y values that exceed the size of the screen will also causes no image to
 * be plotted. Similarly, if a height is given that is below one, nothing will
 * be plotted. However, if the height exceeds the length of the screen, only
 * the portion of the image that fits the screen will be plotted.
 * 
 * If the destructive flag is set to false, then the given image will be
 * overlayed in the desired location. Otherwise, anything that was plotted
 * beforehand in the region where the image is supposed to be placed will be
 * destroyed.
 * 
 * @warning Extreme caution needs to be taken with the height parameter, as it
 * is impossible to confirm if it exceeds any upper bound. If a height is given
 * that is greater than the actual height of the bitmap, then it may corrupt
 * part of memory.
 * 
 * @param base The location in memory to plot at.
 * @param x The left-most column to begin to plot the raster (in pixels starting
 * at zero).
 * @param y The top-most row to begin to plot the raster (in pixels starting at
 * zero).
 * @param height The height of the bitmap. Must be one or greater.
 * @param bitmap The bitmap that is to be plotted on screen.
 * @param destructive When true, indicates that any pre-existing drawings in the
 * region where the bitmap is being placed should be destroyed. Otherwise, the
 * pixels that are already there will be kept and the bitmap will be overlayed
 * in the region.
 * @param blackScreen When true, indicates that the raster is to be printed on a
 * black background. This will do an XOR with the black screen resulting in the 
 * bitmap being shown in white on the black background.
 */
void plot_rast16(UINT16 *base, int x, int y, int height, const UINT16 *bitmap,
				 BOOL destructive, BOOL blackScreen);

/**
 * @brief Plots a 8-bit wide bitmap of any height.
 * @details The bitmap pointed to by the bitmap pointer will be plotted starting
 * at its top-left corner at the given x and y pixel coordinates. It is possible
 * to have a negative x and y coordinate, as even if the plotting begins in an
 * invalid region, something will still be drawn as long as the coordinates
 * aren't too far out of range. With a negative x coordinate, the image will
 * have part of its left side cropped out. A negative x coordinate is allowed
 * only until it causes all 8-bits to be lost from the image. In that case,
 * no image will be plotted at all. Likewise, a positive x coordinate which
 * is large enough to prevent all 8-bits of the image to be plotted will result
 * in the image being cropped from the right.
 * 
 * A negative y coordinate is allowed as long as the height of the image would
 * mean that at least part of the image would be plotted on screen. Any x values
 * or y values that exceed the size of the screen will also causes no image to
 * be plotted. Similarly, if a height is given that is below one, nothing will
 * be plotted. However, if the height exceeds the length of the screen, only
 * the portion of the image that fits the screen will be plotted.
 * 
 * If the destructive flag is set to false, then the given image will be
 * overlayed in the desired location. Otherwise, anything that was plotted
 * beforehand in the region where the image is supposed to be placed will be
 * destroyed.
 * 
 * @warning Extreme caution needs to be taken with the height parameter, as it
 * is impossible to confirm if it exceeds any upper bound. If a height is given
 * that is greater than the actual height of the bitmap, then it may corrupt
 * part of memory.
 * 
 * @param base The location in memory to plot at.
 * @param x The left-most column to begin to plot the raster (in pixels starting
 * at zero).
 * @param y The top-most row to begin to plot the raster (in pixels starting at
 * zero).
 * @param height The height of the bitmap. Must be one or greater.
 * @param bitmap The bitmap that is to be plotted on screen.
 * @param destructive When true, indicates that any pre-existing drawings in the
 * region where the bitmap is being placed should be destroyed. Otherwise, the
 * pixels that are already there will be kept and the bitmap will be overlayed
 * in the region.
 * @param blackScreen When true, indicates that the raster is to be printed on a
 * black background. This will do an XOR with the black screen resulting in the 
 * bitmap being shown in white on the black background.
 */
void plot_rast8(UINT8 *base, int x, int y, int height, const UINT8 *bitmap,
				BOOL destructive, BOOL blackScreen);

/**
 * @brief Plots a black rectangular area at the given memory location.
 * @details The rectangular area's top-left corner will be defined by the given
 * x and y pixel coordinates. For simplicity of implementation, x and y cannot
 * be less than zero or greater than the size of the screen. As well, the length
 * and height cannot be less than zero. However, the length and height can be
 * greater than the length and height of the Atari ST's monochrome screen. In
 * the former case, the entire length of the screen will be used, while in the
 * latter case, the entire height of the screen will be used by the rectangular
 * area. If both exceed the screen size, then the rectangle will take up the
 * confines of the entire screen.
 * 
 * @param base The location in memory to plot at.
 * @param x The left-most column to start plotting the rectangle (in pixels
 * starting at zero).
 * @param length The number of rows that should make up the rectangular area.
 * Must be one or greater.
 * @param y The top-most row to start plotting the rectangle (in pixels
 * starting at zero).
 * @param height The number of columns that should make up the rectangular area.
 * Must be one or greater.
 */
void rect_area(UINT32 *base, int x, int length, int y, int height);

/**
 * @brief Clears a rectangular area at the given memory location.
 * @details The rectangular area's top-left corner will be defined by the given
 * x and y pixel coordinates. For simplicity of implementation, x and y cannot
 * be less than zero or greater than the size of the screen. As well, the length
 * and height cannot be less than zero. However, the length and height can be
 * greater than the length and height of the Atari ST's monochrome screen. In
 * the former case, the entire length of the screen will be used, while in the
 * latter case, the entire height of the screen will be used by the rectangular
 * area. If both exceed the screen size, then the entire screen will be cleared.
 * 
 * @param base The location in memory to plot at.
 * @param x The left-most column to start clearing the rectangular area (in
 * pixels starting at zero).
 * @param length The number of rows that should make up the rectangular area.
 * Must be one or greater.
 * @param y The top-most row to start clearing the rectangular area (in pixels
 * starting at zero).
 * @param height The number of columns that should make up the rectangular area.
 * Must be one or greater.
 */
void clr_area(UINT32 *base, int x, int length, int y, int height);

/**
 * @brief Sets all the pixels on the screen, thus setting the screen to black.
 * @param base The location in memory to plot at.
 * @author Marc Schroeder
 * @author Richard Johnston
 */
void fill_scrn(UINT32 *base);

/**
 * @brief Clears all the pixels on the screen, thus setting the screen to white.
 * @param base The location in memory to plot at.
 * @author Marc Schroeder
 */
void clr_scrn(UINT32 *base);

/** 
 * @return UINT16* Returns the current frame buffer start address.
 * 
 * @note The low 8-bits are always zero.
 */
UINT16 *get_video_base();

/**
 * @brief Sets the frame buffer start address to the desired address.
 * 
 * @param base The desired frame buffer start address.
 */
void set_video_base(UINT16 *base);

#endif
