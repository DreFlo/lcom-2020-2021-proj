#ifndef _GAME_H_
#define _GAME_H_

#include <lcom/lcf.h>
#include "entity.h"
#include "tiles.h"
#include "file.h"
#include "graphics.h"

/**
 * @author Diogo Faria
 * @author André Flores
 * @defgroup game Game
 * Game structure and functions
 * @{
 */

/**
 * @brief Contains the mouse information
 */
typedef struct{
    int16_t x_pos;                              /* Mouse cursor x position */
    int16_t y_pos;                              /* Mouse cursor y position */
    struct packet mouse_bytes;                  /* Mouse bytes */
} *Mouse_p;

/**
 * @brief Represents the game state
 * 
 */
typedef enum{
    MENU, PLAYING, PAUSE_MENU, FINAL_MENU, END, D_BRIDGE
} game_state;

/**
 * @brief Contains the information of the current game
 * 
 */
typedef struct{
    uint8_t kbd_bytes[2];                       /* Scancode bytes */
    char * game_file;                        /* Filepath of the top score file */
    
    uint16_t xPos;                              /* Player x position */
    uint16_t yPos;                              /* Player y position */

    int p_x_speed, p_y_speed;                   /* Player speed */

    game_state g_state;                         /* Game state */

    size_t entity_no;                           /* Number of entities in current map */
    Entity_p entities[10];                      /* Array with pointers to all the entities in the current map */

    tile_map_t tile_map;                        /* Current tile map for the game */

    Mouse_p Mouse;                              /* Mouse information for the game */
    
    bool leave;                                 /* Whether to leave the game or not */

    int top_score;                              /* Top ever achieved score achieved in the game */
    int curr_score;                             /* Current game score */

    bool new_top_score;                         /* Whether there was a new top score achieved or not */

    uint8_t game_sec;                           /* Real time seconds */
    uint8_t game_min;                           /* Real time mins */
    uint8_t game_hour;                          /* Real time hour */

    uint8_t map_no;                             /* Number of current map */

    uint8_t last_read;                          /* Last scancode to be read */
} game;

/**
 * @brief Creates a game at start state
 * @param filepath Filepath of the top score file
 * @return Pointer to the game that was created
 */
game * create_game(char filepath[]);

/**
 * @brief Updates all entites in a game
 * @param G Pointer to the game to be updated
 */
void game_update_entities(game * G);

/**
 * @brief Draws game to the main buffer
 * @param G Pointer to the game to be drawn
 */
void draw_game(game * G);

/**
 * @brief Changes current game map
 * @param G Pointer to the game to be changed
 * @param map_no Number of the map to be loaded
 */
void game_load_map(game * G, uint8_t map_no);

/**
 * @brief Destroys a game and frees memory
 * @param G Pointer to the game to be destroyed
 */
void destroy_game(game * G);

/**
 * @}
 */

#endif //_GAME_H_
