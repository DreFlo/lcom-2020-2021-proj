#include "tiles.h"

tile_t create_tile(tile_type T, uint16_t xp, uint16_t yp) {
    tile_t p;

    p.x = xp;
    p.y = yp;

    p.hitbox_width = 50;
    p.hitbox_height = 50;

    p.type = T;

    return p;
}

tile_map_t create_tile_map(tile_char_map_t char_map) {
    tile_map_t t_m;
    for(uint8_t i = 0; i < 12; i++) {
        for (uint8_t u = 0; u < 16; u++) {
            // Create tiles accoreding to character
            switch (char_map[i][u])
            {
            case 'g':
                t_m.map[i][u] = create_tile(MID_GROUND, 50 * u, 50 * i);
                break;
            case 't':
                t_m.map[i][u] = create_tile(TOP_GROUND, 50 * u, 50 * i);
                break;
            case 'p':
                t_m.map[i][u] = create_tile(PLATFORM, 50 * u, 50 * i);
                break;
            case 'c':
                t_m.map[i][u] = create_tile(UNSPENT_COIN, 50 * u, 50 * i);
                break;
            case 'x':
                t_m.map[i][u] = create_tile(UNSPENT_TOMATO, 50 * u, 50 * i);
                break;
            case 'e':
                t_m.map[i][u] = create_tile(END_FLAG, 50 * u, 50 * i);
                break;
            case 'b':
                t_m.map[i][u] = create_tile(BRIDGE, 50 * u, 50 * i);
                break;
            case 'f':
                t_m.map[i][u] = create_tile(END_FLAG, 50 * u, 50 * i);
                break;
            default:
                t_m.map[i][u] = create_tile(TRANS, 50 * u, 50 * i);
                break;
            }
        }
    }
    return t_m;
}

void draw_tile(tile_p p) {
    // Draw tile according to type
    switch (p->type) {
    case TOP_GROUND:
        draw_to_background(TOP_GROUND_TILE, p->x, p->y);
        break;
    case MID_GROUND:
        draw_to_background(MID_GROUND_TILE, p->x, p->y);
        break;
    case PLATFORM:
        draw_to_background(PLATFORM_TILE, p->x, p->y);
        break;
    case UNSPENT_COIN:
        draw_to_background(UNSPENT_COIN_TILE, p->x, p->y);
        break;
    case SPENT_COIN:
        draw_to_background(SPENT_COIN_TILE, p->x, p->y);
        break;
    case UNSPENT_TOMATO:
        draw_to_background(UNSPENT_TOMATO_TILE, p->x, p->y);
        break;
    case SPENT_TOMATO:
        draw_to_background(SPENT_TOMATO_TILE, p->x, p->y);
        break;
    case BRIDGE:
        draw_to_background(BRIDGE_TILE, p->x, p->y);
        break;
    case END_FLAG:
        draw_to_background(END_FLAG_TILE, p->x, p->y);
        break;
    default:
        return;
        break;
    }
}

void draw_tile_map(tile_map_p map_ptr) {
    for (uint8_t i = 0; i < 12; i++)
    {
        for (uint8_t u = 0; u < 16; u++) {
            draw_tile(&map_ptr->map[i][u]);
        }
    }
    
}
