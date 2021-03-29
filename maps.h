#ifndef _MAPS_H_
#define _MAPS_H_

/**
 * @author André Flores
 * @defgroup maps Maps
 * Arrays used to create maps in the game
 * @{
 */

/**
 * @brief An array of 16 characters that make up row of tiles
 */
typedef char const tile_char_row_t[16];

/**
 * @brief An array of 12 tile_char_row_t that make a tile map
 */
typedef tile_char_row_t const tile_char_map_t[12];

static tile_char_map_t const MAP_0 = {
{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
{' ', ' ', ' ', ' ', ' ', ' ', 'p', 'p', 'p', 'p', ' ', ' ', ' ', ' ', ' ', ' '},
{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 't', 't', 't'},
{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 't', 'g', 'g', 'g'},
{' ', ' ', ' ', ' ', 't', ' ', ' ', ' ', ' ', ' ', 't', 't', 'g', 'g', 'g', 'g'},
{' ', ' ', ' ', 't', 'g', 'c', 'c', 'c', 'c', 'c', 'g', 'g', 'g', 'g', 'g', 'g'},
{'t', 't', 't', 'g', 'g', 't', 't', 't', 't', 't', 'g', 'g', 'g', 'g', 'g', 'g'},
{'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g'},
{'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g'},
{'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g'},
};

static tile_char_map_t const MAP_1 = {
{' ', ' ', ' ', ' ', ' ', ' ', 'c', 'c', 'c', 'c', ' ', ' ', ' ', ' ', ' ', ' '},
{' ', ' ', ' ', ' ', ' ', ' ', 'p', 'p', 'p', 'p', ' ', ' ', ' ', ' ', ' ', ' '},
{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'p', 'p', 'p', 'p', ' ', ' ', ' ', ' '},
{'t', 't', 't', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
{'g', 'g', 'g', 't', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'c', ' ', ' ', ' ', ' '},
{'g', 'g', 'g', 'g', 't', 'c', ' ', ' ', ' ', 'c', ' ', 'p', ' ', 't', 't', 't'},
{'g', 'g', 'g', 'g', 'g', 'p', ' ', ' ', ' ', 'p', ' ', ' ', ' ', 'c', 'x', 'g'},
{'g', 'g', 'g', 'g', 'g', ' ', ' ', 'c', ' ', ' ', ' ', ' ', ' ', 'c', 'c', 'g'},
{'g', 'g', 'g', 'g', 'g', ' ', ' ', 'p', ' ', ' ', ' ', ' ', ' ', 'c', 'c', 'g'},
{'g', 'g', 'g', 'g', 'g', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'c', 'c', 'g'},
{'g', 'g', 'g', 'g', 'g', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 't', 't', 'g'},
};

static tile_char_map_t const MAP_2 = {
{'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g'},
{' ', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g'},
{' ', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g'},
{' ', ' ', ' ', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g'},
{' ', ' ', ' ', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g'},
{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'g', 'g'},
{'t', 't', 't', 't', 'b', ' ', ' ', ' ', ' ', ' ', ' ', 'b', 't', 't', 'g', 'g'},
{'g', 'g', 'g', 'g', 'g', ' ', ' ', ' ', ' ', ' ', ' ', 'g', 'g', 'g', 'g', 'g'},
{'g', 'g', 'g', 'g', 'g', ' ', ' ', ' ', ' ', ' ', ' ', 'g', 'g', 'g', 'g', 'g'},
{'g', 'g', 'g', 'g', 'g', ' ', ' ', ' ', ' ', ' ', ' ', 'g', 'g', 'g', 'g', 'g'},
{'g', 'g', 'g', 'g', 'g', ' ', ' ', ' ', ' ', ' ', ' ', 'g', 'g', 'g', 'g', 'g'},
{'g', 'g', 'g', 'g', 'g', ' ', ' ', ' ', ' ', ' ', ' ', 'g', 'g', 'g', 'g', 'g'},
};

static tile_char_map_t const MAP_3 = {
{'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g'},
{' ', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g'},
{' ', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g'},
{' ', ' ', ' ', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g'},
{' ', ' ', ' ', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g'},
{' ', ' ', ' ', ' ', ' ', 'c', 'c', 'c', 'c', 'c', 'c', ' ', ' ', ' ', ' ', ' '},
{'t', 't', 't', 't', 'b', 'p', 'p', 'p', 'p', 'p', 'p', 'b', 't', 't', 't', 't'},
{'g', 'g', 'g', 'g', 'g', ' ', ' ', ' ', ' ', ' ', ' ', 'g', 'g', 'g', 'g', 'g'},
{'g', 'g', 'g', 'g', 'g', ' ', ' ', ' ', ' ', ' ', ' ', 'g', 'g', 'g', 'g', 'g'},
{'g', 'g', 'g', 'g', 'g', ' ', ' ', ' ', ' ', ' ', ' ', 'g', 'g', 'g', 'g', 'g'},
{'g', 'g', 'g', 'g', 'g', ' ', ' ', ' ', ' ', ' ', ' ', 'g', 'g', 'g', 'g', 'g'},
{'g', 'g', 'g', 'g', 'g', ' ', ' ', ' ', ' ', ' ', ' ', 'g', 'g', 'g', 'g', 'g'},
};

static tile_char_map_t const MAP_4 = {
{'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g'},
{'g', 'g', ' ', ' ', ' ', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g'},
{' ', 'g', ' ', 't', ' ', ' ', 'g', ' ', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'g'},
{' ', 'g', ' ', 'g', ' ', ' ', 'g', ' ', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'g'},
{' ', 'g', ' ', 'g', ' ', ' ', 'g', ' ', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'g'},
{' ', ' ', ' ', 'g', 't', ' ', 'g', ' ', 't', 'c', 'c', 'c', 'c', 'c', 'c', 'g'},
{'t', 't', 't', 'g', 'g', ' ', 'g', ' ', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g'},
{'g', 'g', 'g', 'g', 'g', ' ', 'g', ' ', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g'},
{'g', 'g', 'g', 'g', 'g', ' ', 'g', ' ', ' ', ' ', 'g', 'g', 'g', 'g', ' ', ' '},
{'g', 'g', 'g', 'g', 'g', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'f'},
{'g', 'g', 'g', 'g', 'g', ' ', ' ', ' ', 't', ' ', ' ', ' ', ' ', ' ', 't', 't'},
{'g', 'g', 'g', 'g', 'g', 't', 't', 't', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g'},
};

/**
 * @}
 */

#endif //_MAPS_H_
