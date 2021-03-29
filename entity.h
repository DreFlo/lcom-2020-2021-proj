#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "asprite.h"
#include "i8042.h"

/**
 * @author André Flores
 * @author Diogo Faria
 * @defgroup entity Entity
 * Code for entities present in the game (Player and Enemies)
 * @{
 */

/**
 * @brief Represents the type of entity
 */
typedef enum {
    PLAYER, ENEMY
}entity_type;

/**
 * @brief Represents the player movements
 */
typedef enum{
    STATIONARY, MOVE, JUMP, DEAD
} entity_movement_state;

/**
 * @brief Represents the direction that the character is facing
 */
typedef enum{
    LEFT, RIGHT
} entity_direction;

/**
 * @brief Represents the different states in a movement;
 */
typedef enum{
    FIRST, SECOND, THIRD, FORTH, FIFTH, LAST
} entity_animation_frame;

/**
 * @brief Struct with all needed entity information
 */
typedef struct {
    entity_type type;                                                               /* Entity type */
    entity_direction dir;                                                           /* Direction the entity is facing */
    entity_movement_state mov_state;                                                /* State of entity movement */

    int entity_frame_no;                                                            /* Number of animation frames for the entity */
    uint8_t death_frame;                                                            /* Number of animation frame after death */

    entity_animation_frame anim_frame;                                              /* Enum specifying the current animation frame */ 

    AnimSprite *fwd_anim, *bwd_anim, *fwd_jump_anim, *bwd_jump_anim, *death_anim;   /* Pointers to entity's animations */

    int x_pos, y_pos;                                                               /* Entity's coordinates */
    uint8_t hitbox_width, hitbox_height;                                            /* Entity's hitbox size */
    int x_speed, y_speed;                                                           /* Entity's speed according to axis */

    uint8_t lives;                                                                  /* NUmber of entity lives */
} Entity, *Entity_p;

/**
 * @brief Creates entity of a specified type at position (x, y)
 * @param type Type of entity to be created
 * @param x_pos x coordinate of the entity to be created
 * @param y_pos y coordinated of the entity to be created
 * @return Pointer to the created entity
 */
Entity * create_entity(entity_type type, int x_pos, int y_pos);

/**
 * @brief Draws an entity at its position
 * @param entity Pointer to the entity to be drawn
 */
void draw_entity(Entity *entity);

/**
 * @brief Updates the position of an entity according to its speed
 * @param entity Pointer to the entity to be updated
 */
void update_entity_pos(Entity *entity);

/**
 * @brief Updates the animation of an entity according to its speed
 * @param entity Pointer to the entity to be updated
 */
void update_entity_anim(Entity_p entity);

/**
 * @brief Destroys an entity and frees memory
 * @param entity Pointer to the entity to be destroyed
 */
void destroy_entity(Entity_p entity);

/**
 * @}
 */

#endif //_ENTITY_H_
