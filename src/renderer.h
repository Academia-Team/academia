/**
 * @file renderer.h
 * @author Academia Team
 * @brief Contains functions to render everything in the model.
 * 
 * @copyright Copyright Academia Team 2023
 */

#ifndef RENDERER_H
#define RENDERER_H

#include "bool.h"
#include "font16.h"
#include "model.h"
#include "move.h"
#include "types.h"

/**
 * @brief The width of the font used when rendering a label.
 */
#define LABEL_FONT_WIDTH FONT16_WIDTH

/**
 * @brief The height of the font used when rendering a label.
 */
#define LABEL_FONT_HEIGHT FONT16_HEIGHT

/**
 * @brief Renders an updated version of the world cells.
 * @details When a world shift has occurred this is to be called to draw the 
 * updated cell positions and newly generated cells at the top row.
 * @note This is a wrapper function that solely calls renderWorld().
 * 
 * @param base The location in memory to plot at.
 * @param world The game world that is to be updated on the screen.
 */
#define renderUpdateWorld(base, world) renderWorld(base, world)

/**
 * @brief Renders an updated version of all the inhabitants in the world.
 * @details Is to be called when any score or lives have been updated, any 
 * hazards have moved, or if the player has moved. Any objects owned by
 * inhabitants, such as player lives and score boxes, will also be rendered.
 * 
 * @param base The location in memory to plot at.
 * @param world The game world that is to have all of its inhabitants updated on
 * the screen.
 */
void renderUpdate(UINT32* const base, const World* const world);

/**
 * @brief Renders the initial frame of the entire game play area. 
 * @details This includes the world border. Both player scores and lives if in 
 * two player mode otherwise just main player score and lives will be rendered 
 * to the screen. Game tiles and sprites. Also renders the "YOU:" and "OTHER:"
 * labels to the screen when game is in two player mode. 
 * 
 * @param base The location in memory to plot at.
 * @param world The game world that is to be rendered to the screen.
 */
void renderPlayArea(UINT32* const base, const World* const world);

/**
 * @brief Renders the world to the screen. 
 * @details The Game World constitutes all the cell-containing rows.
 * 
 * @param base The location in memory to plot at.
 * @param world The game world that is to be rendered to the screen.
 */
void renderWorld(UINT32* const base, const World* const world);

/**
 * @brief Renders a row to the screen.
 * @details Renders each cell of the row.
 * 
 * @param base The location in memory to plot at.
 * @param row The row that is to be rendered to the screen.
 */
void renderRow(UINT32* const base, const Row* const row);

/**
 * @brief Renders a cell to the screen.
 * @details Renders the cells sprite to the screen. (Road, Rail, Grass, Spike, 
 * or Hedge). Also renders a collectable sprite to the cell if the cell contains
 * a collectable. (A, B or C).
 * 
 * @param base The location in memory to plot at.
 * @param cell The cell that is to be rendered to the screen.
 * @param y The y pixel position of the row on screen.
 */
void renderCell(UINT32* const base, const Cell* const cell, int y);

/**
 * @brief Renders all the hazards for a given row to the screen.
 * @details Renders the sprite of a rows hazard(s) to the x position of the 
 * hazard and the y position of the row.
 * 
 * @param base The location in memory to plot at.
 * @param row The row that the hazards belong to that is to be rendered to the 
 * screen.
 */
void renderHazards(UINT32* const base, const Row* const row);

/**
 * @brief Renders main player, players scores and lives to the screen.
 * @details If in two player mode renders both players score and lives otherwise
 * just main player score and lives will be rendered to the screen. Also renders
 * the main players to the screen.
 * 
 * @param base The location in memory to plot at.
 * @param world The world that is to have its player(s) sprite, score, and lives
 * to the screen.
 */
void renderPlayers(UINT32* const base, const World* const world);

/**
 * @brief Renders the main players sprite to the screen.
 * @details Renders the worlds main players sprite to the screen with the 
 * players given direction. (North, South, East, West).
 * 
 * @param base The location in memory to plot at.
 * @param player The player that is have their sprite, score and lives rendered 
 * to the screen.
 */
void renderMainPlayer(UINT32* const base, const Player* const player);

/**
 * @brief Renders a label to the screen.
 * @details Renders the characters of a string as 16x16 text sprites at the 
 * labels x and y position on screen, top-left corner justified.
 * 
 * @param base The location in memory to plot at.
 * @param label The label that is to be rendered to the screen.
 * @param blackScreen Set to true if text is being rendered on black background.
 */
void renderLabel(UINT16* const base, const Label* const label,
				 BOOL blackScreen);

/**
 * @brief Renders a score to the screen.
 * @details Renders the score value (the actual number to be displayed), at the 
 * scores x and y position on screen, top-left corner justified.
 * 
 * @param base The location in memory to plot at.
 * @param Score The score of a player that is to be rendered to the screen.
 */
void renderScore(UINT16* const base, Score* const Score);

/**
 * @brief Renders lives to the screen.
 * @details Renders the lives value (the actual number to be displayed), at the 
 * lives x and y position on screen, top-left corner justified.
 * 
 * @param base The location in memory to plot at.
 * @param lives The lives of a player that is to be rendered to the screen.
 */
void renderLives(UINT16* const base, Lives* const lives);

/**
 * @brief Renders a title to the screen at the specified location.
 * @details If the x and y coordinates are negative, as long as it isn't too
 * negative, part of the title will still be displayed on screen. However, if
 * it is out of bounds to the right, nothing will be rendered.
 * @warning It makes an assumption that everything around the title is white, so
 * it will print it destructively in order to be more efficient. If the
 * background is not white, it will be damaged.
 * 
 * @param base The location in memory to plot at.
 * @param x The horizontal pixel location (starting at zero) to plot the
 * left-most pixel of the title.
 * @param y The vertical pixel location (starting at zero) to plot the top-most
 * pixel of the title.
 */
void renderTitle(UINT32* const base, int x, int y);

/**
 * @brief Renders "Game Over" to the screen at the specified location.
 * @details If the x and y coordinates are negative, as long as it isn't too
 * negative, part of the text will still be displayed on screen. However, if
 * it is out of bounds to the right, nothing will be rendered.
 * 
 * @param base The location in memory to plot at.
 * @param x The horizontal pixel location (starting at zero) to plot the
 * left-most pixel of the text.
 * @param y The vertical pixel location (starting at zero) to plot the top-most
 * pixel of the text.
 */
void renderGameOver(UINT32* const base, int x, int y);

/**
 * @brief Renders the cursor on the screen at the given x-y coordinates.
 * @note It xors the image onto the screen.
 * 
 * @param base The location in memory to plot at.
 * @param x The horizontal pixel location (starting at zero) to plot the
 * left-most pixel of the cursor.
 * @param y The vertical pixel location (starting at zero) to plot the top-most
 * pixel of the cursor.
 */
void renderCursor(UINT16* const base, int x, int y);

/**
 * @brief Renders a menu on the screen.
 * 
 * @param base The location in memory to plot at.
 * @param menu The menu to render.
 */
void renderMenu(UINT32* const base, Menu* menu);

#endif