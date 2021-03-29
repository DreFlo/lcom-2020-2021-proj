#ifndef _TILES_H_
#define _TILES_H_

#include <lcom/lcf.h>
#include "graphics.h"
#include "maps.h"

/**
 * @author André Flores
 * @defgroup tiles Tiles
 * Tile structure and functions for use in the game
 * @{
 */

/**
 * @brief Lists the different types of tiles
 */
typedef enum {
    TOP_GROUND, MID_GROUND, PLATFORM, TRANS, UNSPENT_COIN, SPENT_COIN, UNSPENT_TOMATO, SPENT_TOMATO, BRIDGE, END_FLAG
} tile_type;

/**
 * @brief Struct with all needed tile information
 */
typedef struct {
    
    tile_type type;                             /* Type of tile */

    uint16_t x, y;                              /* Tile's x and y coordinates */

    uint16_t hitbox_width, hitbox_height;       /* Tile's hitbox */
}tile_t, *tile_p;

/**
 * @brief Struct with all tiles in a fulscreen map
 */
typedef struct {
    tile_t map[12][16];                         /* Map of the tiles */
} tile_map_t, *tile_map_p;

/**
 * @brief Creates a tile of a specified type at a specified position
 * @returns Tile
 */
tile_t create_tile(tile_type T, uint16_t xp, uint16_t yp);

/**
 * @brief Creates a tile map according to an array characters
 * @returns Tile map
 */
tile_map_t create_tile_map(tile_char_map_t char_map);

/**
 * @brief Draws a tile to the background buffer
 */
void draw_tile(tile_p p);

/**
 * @brief Draws a tile map to the backgroud buffer
 */
void draw_tile_map(tile_map_p map_ptr);

/**
 * @}
 */

#endif //_TILES_H_
