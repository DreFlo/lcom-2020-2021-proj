#include "game_physics.h"

collision_type (check_entity_entity_collision)(Entity_p E1, Entity_p E2) {
    // if one of the entities is dead there is no collision
    if(E1->lives < 1 || E2->lives < 1) return NO_COLLISION;
    // check x position
    if (E1->x_pos <= E2->x_pos && E1->x_pos + E1->hitbox_width >= E2->x_pos) {
        // check y position
        if (E1->y_pos + E1->hitbox_height > E2->y_pos && E1->y_pos + E1->hitbox_height < E2->y_pos + E2->hitbox_height)
            return TOP_COLLISION;
        else if (E1->y_pos > E2->y_pos && E1->y_pos < E2->y_pos + E2->hitbox_height)
            return BOTTOM_COLLISION;
        else if (E1->y_pos + E1->hitbox_height <= E2->y_pos || E1->y_pos >= E2->y_pos + E2->hitbox_height)
            return NO_COLLISION;
        return LEFT_COLLISION;
    }
    else if (E1->x_pos >= E2->x_pos && E1->x_pos <= E2->x_pos + E2->hitbox_width) {
        // check y position
        if (E1->y_pos + E1->hitbox_height > E2->y_pos && E1->y_pos + E1->hitbox_height < E2->y_pos + E2->hitbox_height)
            return TOP_COLLISION;
        else if (E1->y_pos > E2->y_pos && E1->y_pos < E2->y_pos + E2->hitbox_height)
            return BOTTOM_COLLISION;
        else if (E1->y_pos + E1->hitbox_height <= E2->y_pos || E1->y_pos >= E2->y_pos + E2->hitbox_height)
            return NO_COLLISION;
        return RIGHT_COLLISION;
    }
    return NO_COLLISION;
}

collision_type (check_entity_tile_collison)(Entity_p E, tile_p T) {
    // if one the entity is dead or tile is of a certain type there is no collision
    if(T->type == TRANS || T->type == SPENT_COIN || (E->type == ENEMY && T->type == UNSPENT_COIN)) return NO_COLLISION;
    // check x position
    if (E->x_pos <= T->x && E->x_pos + E->hitbox_width >= T->x) {
        // check y position
        if (E->y_pos + E->hitbox_height > T->y && E->y_pos + E->hitbox_height < T->y + T->hitbox_height)
            return TOP_COLLISION;
        else if (E->y_pos >= T->y && E->y_pos <= T->y + T->hitbox_height && E->y_pos + E->hitbox_height > T->y + T->hitbox_height)
            return BOTTOM_COLLISION;
        else if (E->y_pos + E->hitbox_height <= T->y || E->y_pos >= T->y + T->hitbox_height)
            return NO_COLLISION;
        return LEFT_COLLISION;
    }
    else if (E->x_pos >= T->x && E->x_pos <= T->x + T->hitbox_width) {
        // check y position
        if (E->y_pos + E->hitbox_height > T->y && E->y_pos + E->hitbox_height < T->y + T->hitbox_height)
            return TOP_COLLISION;
        else if (E->y_pos >= T->y && E->y_pos <= T->y + T->hitbox_height && E->y_pos + E->hitbox_height > T->y + T->hitbox_height)
            return BOTTOM_COLLISION;
        else if (E->y_pos + E->hitbox_height <= T->y || E->y_pos >= T->y + T->hitbox_height)
            return NO_COLLISION;
        return RIGHT_COLLISION;
    }
    return NO_COLLISION;
}

void (handle_entity_collision)(Entity_p E1, Entity_p E2, collision_type T) {
    switch (T)
    {
    case TOP_COLLISION:
        E1->y_speed = -8;
        E2->lives--;
        E2->y_speed = 0;
        break;
    case BOTTOM_COLLISION:
        E2->y_speed = -8;
        E1->lives--;
        E1->y_speed = 0;
        break;
    case RIGHT_COLLISION:
        if(E1->type == PLAYER && E2->type == ENEMY) { 
            E1->lives--;
            E1->x_pos = E2->x_pos + E2->hitbox_width + 10;
            E1->y_speed = -8;
            E1->x_speed = 8;
        }
        else if(E1->type == ENEMY && E2->type == ENEMY) {
            // Change speed
            E1->x_speed = -E1->x_speed;
            E2->x_speed = -E2->x_speed;
        }
        break;
    case LEFT_COLLISION:
        if(E1->type == PLAYER && E2->type == ENEMY) { 
            E1->lives--;
            E1->x_pos = E2->x_pos - E1->hitbox_width - 10;
            E1->y_speed = -8;
            E1->x_speed = -8;
        }
        else if(E1->type == ENEMY && E2->type == ENEMY) {
            // Change speed
            E1->x_speed = -E1->x_speed;
            E2->x_speed = -E2->x_speed;
        }
        break;
    default:
        break;
    }
}

void (handle_tile_collision)(Entity_p E, tile_p T, collision_type C, int * score, game_state * state) {
    // increase player score if they hit an UNSPENT_COIN
    // no "physical" collision occurs
    if (E->type == PLAYER && T->type == UNSPENT_COIN && C != NO_COLLISION) {
        (*score) += 1;
        T->type = SPENT_COIN;
        draw_tile(T);
        return;
    }
    // if player hits unspent tomato their lives are set to 5
    else if (E->type == PLAYER && T->type == UNSPENT_TOMATO && C == BOTTOM_COLLISION) {
        E->lives = 5;
        T->type = SPENT_TOMATO;
        draw_tile(T);
    }
    else if (E->type == PLAYER && T->type == END_FLAG && C != NO_COLLISION) {
        (*state) = FINAL_MENU;
        reset_counter();
        return;
    }
    switch(C) {
    case TOP_COLLISION:
        E->y_speed = 0;
        E->y_pos = T->y - E->hitbox_height;
        break;
    case BOTTOM_COLLISION:
        if (E->y_speed < 0 || E->y_speed > 1) E->y_pos = T->y + T->hitbox_height;
        E->y_speed = 0;
        break;
    case LEFT_COLLISION:
        E->x_pos = T->x - E->hitbox_width - 1;
        switch (E->type)
        {
        case ENEMY:
            E->x_speed = - E->x_speed;            
            break;
        default:
            E->x_speed = 0;
            break;
        }
        break;
    case RIGHT_COLLISION:
        E->x_pos = T->x + T->hitbox_width + 1;
        switch (E->type)
        {
        case ENEMY:
            E->x_speed = - E->x_speed;            
            break;
        default:
            E->x_speed = 0;
            break;
        }
        break;
    default:
        break;
    }
}

void (game_entity_entity_collisions)(Entity_p entity_arr[], size_t size) {
    collision_type col;
    for (size_t i = 0; i < (size - 1); i++) {
        for (size_t u = (i + 1); u < size; u++) {
            // if there is a collison handles it and skips to the next entity to be checked
            if ((col = check_entity_entity_collision(entity_arr[i], entity_arr[u])) != NO_COLLISION) {
                handle_entity_collision(entity_arr[i], entity_arr[u], col);
                break;
            }
        }
    }
}

void (game_entity_tile_collisions)(Entity_p entity_arr[], size_t size, tile_map_p map, int * score, game_state * state) {
    collision_type col;
    Entity_p E;
    int x, y;
    // In the worst case scenario an entity will be in contact with 6 tiles
    // Only checks the six possible tiles an entity could be touching for collisions
    for (size_t i = 0; i < size; i++) {
        E = entity_arr[i];
        x = E->x_pos / 50;
        y = E->y_pos / 50;
        for (int u = 0; u < 3; u++) {
            for (int r = 0; r < 2; r++) {
                if (map->map[y + u][x + r].type != TRANS) {
                    if ((col = check_entity_tile_collison(E, &map->map[y + u][x + r])) != NO_COLLISION)
                        handle_tile_collision(E, &map->map[y + u][x + r], col, score, state);
                }
            }
        }
    }
}

void apply_gravity(game * G) {
    for (size_t i = 0; i < G->entity_no; i++) {
        G->entities[i]->y_speed += 1;
        update_entity_pos(G->entities[i]);
    }
}

void handle_physics(game * G) {
    apply_gravity(G);
    game_entity_entity_collisions(G->entities, G->entity_no);
    game_entity_tile_collisions(G->entities, G->entity_no, &G->tile_map, &G->curr_score, &G->g_state);
}
