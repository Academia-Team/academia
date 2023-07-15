/**
 * @file events.h
 * @author Academia Team
 * @brief Contains functions to handle all asynchronous, synchronous, and 
 * condition based events.
 * 
 * @copyright Copyright Academia Team 2023
 */

#ifndef EVENTS_H
#define EVENTS_H

#include "effects.h"
#include "model.h"
#include "move.h"

/**
 * @brief Handles all the tasks needed in the event where a player dies.
 * @details Needs to be run three times in order to complete all the tasks.
 * These tasks should be run each time only after a caller defined amount of
 * time has elapsed.
 * @note Only a 0.2sec delay between calls of the function have been tested.
 * 
 * @note Requires super privileges.
 */
#define handleDeath() play_death()

/**
 * @brief Checks if the given coordinates intersects with a button.
 * 
 * @param xCoord The x coordinate (in pixels starting at zero) to check for an
 * intersection with a button.
 * @param yCoord The y coordinate (in pixels starting at zero) to check for an
 * intersection with a button.
 * @param button The button object to check for an intersection.
 * 
 * @return TRUE if the coordinates intersect with the given button; false
 * otherwise.
*/
#define btnCollision(xCoord, yCoord, button) \
	(xCoord >= button.x && xCoord <= (button.x + button.width - 1) \
	&& yCoord >= button.y && yCoord <= (button.y + button.height - 1))

/**
 * @brief Checks if a hazard and a player have collided and handles it
 * accordingly.
 * @details Lives are reduced and immunity is set if it wasn't already set.
 * 
 * @param world The world to check for player-hazard collisions in.
 * @param player The player to check for hazard collision.
 * @return A integral value representing the number of seconds left of immunity.
 * This value will be negative if and only if no collision has occurred.
 * 
 * @note Requires super privileges.
 */
int handleHazardCollision(World* world, Player* player);

/**
 * @brief Add hazards to a world based off of a certain probability.
 * 
 * @param world The world to add hazards to.
 */
void repopulateWorld(World* world);

/**
 * @brief Updates the positions of all the cars in the world.
 * @details All cars which have left the bounds of the world will be removed.
 * 
 * @param world The world for which cars will be updated.
 */
void updateCar(World* world);

/**
 * @brief Updates the positions of all the Mr. Feathers in the world.
 * @details All Mr. Feathers which have left the bounds of the world will be
 * removed.
 * 
 * @param world The world for which Mr. Feathers will be updated.
 */
void updateFeathers(World* world);

/**
 * @brief Updates the positions of all the trains in the world.
 * @details All trains which have left the bounds of the world will be removed.
 * 
 * @param world The world for which trains will be updated.
 */
void updateTrain(World* world);

/**
 * @brief Randomly generate new hazards for a preexisting row.
 * @details All new hazards are placed in the first cell for a given row.
 * 
 * @param row The row for which hazards will be generated.
 */
void addHazard(Row* row);

/**
 * @brief Checks if an object and a border occupy the
 * same space.
 * 
 * @param x The x coordinate of the object to check.
 * @param y The y coordinate of the object to check.
 * @return A boolean value. TRUE if a collision has occurred; false otherwise.
 */
BOOL chkBorderCollision(int x, int y);

/**
 * @brief Checks if a collectable item and a player occupy the same space and
 * handles it accordingly.
 * 
 * @param world The World in which the player exists.
 * @param player The Player object to look for.
 * @return A boolean value. TRUE if a collision has occurred; false otherwise.
 * 
 * @note Requires super privileges.
 */
void handleCollectableCollision(World* world, Player* player);

/**
 * @brief Checks if hazards exist in a certain x and y coordinate.
 * 
 * @param world The World to check for a hazard in.
 * @param x The x coordinate which may contain a hazard.
 * @param y The y coordinate which may contain a hazard.
 * @return A boolean value. TRUE if a collision has occurred; false otherwise.
 */
BOOL chkHazardCollision(const World* const world, int x, int y);

/**
 * @brief Checks if a hedge and an object occupy the same space.
 * 
 * @param world The World in which the object exists.
 * @param x The x coordinate of the object to check.
 * @param y The y coordinate of the object to check.
 * @return A boolean value. TRUE if a collision has occurred; false otherwise.
 */
BOOL chkHedgeCollision(const World* const world, int x, int y);

/**
 * @brief Increment the position of moving hazards in a row.
 * @details The hazard is advanced by one tile in the direction of the given
 * row.
 * 
 * @param row The row in which hazards will be advanced.
 */
void moveHazard(Row* row);

/**
 * @brief Removes all hazards which have made it past the bounds of the row.
 * 
 * @param row The row to remove the hazards from.
 */
void removeHazard(Row* row);

/**
 * @brief Moves a player in a pre-set direction.
 * @details Will shift the world down if necessary. If there is an obstruction
 * in the player's way, the move will be cancelled.
 * 
 * @param world The World the player is in.
 * @param player The Player to move.
 * 
 * @note Requires super privileges.
 * @return FALSE if a move has been cancelled. True otherwise.
 */
BOOL movePlayer(World *world, Player* player);

/**
 * @brief Sets the direction the Player should move in.
 * 
 * @param world The World that the player belongs to.
 * @param player The Player to set the direction of.
 * @param dir The direction that the Player should move in.
 */
void setPlayerDir(Player* player, Direction dir);

/**
 * @brief Determines if the given direction opposes the direction of the next
 * scheduled player movement (if one exists).
 * 
 * @param player The player to check the future movement of.
 * @return TRUE if the given direction opposes future movement; FALSE otherwise.
 */
BOOL playerMoveOpposite(const Player * const player, Direction dir);

/**
 * @brief Shifts the entire world downwards such that a new row is generated
 * at the top.
 * @details The bottommost row is destroyed as part of the operation.
 * 
 * @param world The game world object.
 */
void shiftWorld(World* world);

/**
 * @brief Emits a beeping noise for when an unhandled key has been pressed.
 */
void handleInvalidKeyPress();

#endif 