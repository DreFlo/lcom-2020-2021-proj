#ifndef _PHYSICS_H_
#define _PHYSICS_H_

#include "game.h"
#include "entity.h"
#include "tiles.h"
#include "game.h"
#include "mouse.h"

/**
 * @author André Flores
 * @defgroup game_physics Physics
 * All physics used in the game, including collisions.
 * @{
 */

/**
 * @brief Lists the various collision types
 */
typedef enum {
    NO_COLLISION, TOP_COLLISION, BOTTOM_COLLISION, LEFT_COLLISION, RIGHT_COLLISION
} collision_type;

/**
 * @brief Checks if there was a collision between two entities
 * @param E1 Pointer to the first of the two entities to check
 * @param E2 Pointer to the second of the two entities to check
 * @return The type of collision that occurred according to E1
 */
collision_type check_entity_entity_collision(Entity_p E1, Entity_p E2);

/**
 * @brief Checks if there was a collision between an entity and a tile
 * @param E Pointer to the entity to check
 * @param T Pointer to tile to check
 * @return The type of collision that occurred according to the entity
 */
collision_type check_entity_tile_collison(Entity_p E, tile_p T);

/**
 * @brief Handles a collision between two entities
 * @param E1 Pointer to the first entity
 * @param E2 Pointer to the second entity
 * @param C Type of collision that occurred according to the first entity
 */
void handle_entity_entity_collision(Entity_p E1, Entity_p E2, collision_type C);

/**
 * @brief Handles a collision between an entity and a tile
 * @param E Pointer the the entity
 * @param T Pointer to the tile
 * @param C Type of collision that occurred according to the entity
 * @param score Pointer to a score to be updated if a PLAYER entity collides with an  UNSPENT_COIN tile
 */
void handle_entity_tile_collision(Entity_p E, tile_p T, collision_type C, int * score, game_state * state);

/**
 * @brief Handles all entity to entity collisions in a game
 * @param entity_arr Pointer to the first element of an array of Entity pointers
 * @param size Number of entities in the array
 */
void game_entity_entity_collisions(Entity_p entity_arr[], size_t size);

/**
 * @brief Handles all entity to tile collsions in a game
 * @param entity_arr Pointer to the first element of an array of Entity pointers
 * @param size Number of entities in the array
 * @param map Pointer to a tile_map with the tiles to be checked collisions
 * @param score Pointer to a score to be updated if a PLAYER entity collides with an  UNSPENT_COIN tile 
 */
void game_entity_tile_collisions(Entity_p entity_arr[], size_t size, tile_map_p map, int * score, game_state * state);

/**
 * @brief Applies accelaration to all entities in the game
 * @param G Pointer to the game
 */
void apply_gravity(game * G);

/**
 * @brief Handles all physics in the game (including collisions)
 * @param G Pointer to the game
 */ 
void handle_physics(game * G);

/**
 * @}
 */

#endif //_PHYSICS_H_
