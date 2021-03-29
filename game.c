#include "game.h"

game * create_game(char filepath[]) {
    game* Game = (game*) malloc(sizeof(game));

    Game->game_file = filepath;

    Game->xPos = 1;                                                     //Starting x position
    Game->yPos = 345;                                                   //Starting y position 345

    Game->p_x_speed = 3;                                                //Player speed x axis
    Game->p_y_speed = 15;                                               //Player speed y axis

    Game->g_state = MENU;                                               //Starting game state
    
    Game->entities[0] = create_entity(PLAYER, Game->xPos, Game->yPos);  //Create and add player
    /*
    Game->entities[1] = create_entity(ENEMY, 450, 345);

    Game->entities[1]->x_speed = -1;
    */
    Game->Mouse = (Mouse_p) malloc(sizeof(Mouse_p));

    Game->Mouse->x_pos = 0;
    Game->Mouse->y_pos = 0;

    Game->top_score = read_top_score(Game->game_file);
    Game->curr_score = 0;

    Game->new_top_score = false;

    Game->game_sec = 0;
    Game->game_min = 0;
    Game->game_hour = 0;
    
    Game->leave = false;

    return Game; 
}

void game_update_entities(game * G) {
    for (uint8_t i = 0; i < G->entity_no; i++) {
        update_entity_pos(G->entities[i]);
        update_entity_anim(G->entities[i]);
    }
}

void draw_game(game * G) {
    switch (G->g_state) {
    case MENU:
        draw_start_menu();
        draw_cursor(G->Mouse->x_pos, G->Mouse->y_pos);
        break;
    case PLAYING:
        background_to_buffer();
        for (uint8_t i = 0; i < G->entity_no; i++) draw_entity(G->entities[i]);
        draw_lives(G->entities[PLAYER]->lives);
        draw_score(G->curr_score);
        break;
    case D_BRIDGE:
        background_to_buffer();
        draw_xpm(INSTRUCTIONS, 250, 180);
        for (uint8_t i = 0; i < G->entity_no; i++) draw_entity(G->entities[i]);
        draw_lives(G->entities[PLAYER]->lives);
        draw_score(G->curr_score);
        break;
    case FINAL_MENU:
        draw_pause_menu();
        draw_cursor(G->Mouse->x_pos, G->Mouse->y_pos);
        break;
    default:
        break;
    }
}

void game_load_map(game * G, uint8_t map_no) {
    G->map_no = map_no;
    switch (map_no) {
        case 0:
            // Load map
            G->tile_map = create_tile_map(MAP_0);

            // Number of entities in the map
            G->entity_no = 2;

            // Set player attributes
            G->entities[PLAYER]->x_pos = 1;
            G->entities[PLAYER]->y_pos = 345;
            G->entities[PLAYER]->y_speed = 0;
            G->entities[PLAYER]->x_speed = 0;
            G->entities[PLAYER]->lives = 3;
            G->curr_score = 0;

            // Set enemies
            G->entities[1] = create_entity(ENEMY, 450, 345);
            G->entities[1]->x_speed = -1;

            G->curr_score = 0;
            G->new_top_score = false;

            break;
        case 1:
            // Load map
            G->tile_map = create_tile_map(MAP_1);

            // Number of entities in the map
            G->entity_no = 1;

            // Set player attributes
            G->entities[PLAYER]->x_pos = 1;

            // Set enemies
            destroy_entity(G->entities[1]);

            break;
        case 2:
            // Load map
            G->tile_map = create_tile_map(MAP_2);

            // Number of entities in the map
            G->entity_no = 1;

            // Set player attributes
            G->entities[PLAYER]->x_pos = 1;

            // Set enemies
            destroy_entity(G->entities[1]);

            break;
        case 3:
            // Load map
            G->tile_map = create_tile_map(MAP_3);

            // Number of entities in the map
            G->entity_no = 1;

            // Set player attributes
            //G->entities[PLAYER]->x_pos = 1;

            // Set enemies
            destroy_entity(G->entities[1]);

            break;
        case 4:
            // Load map
            G->tile_map = create_tile_map(MAP_4);

            // Number of entities in the map
            G->entity_no = 3;

            // Set player attributes
            G->entities[PLAYER]->x_pos = 1;

            // Set enemies
            destroy_entity(G->entities[1]);

            G->entities[1] = create_entity(ENEMY, 750, 101);
            G->entities[2] = create_entity(ENEMY, 600, 101);

            G->entities[1]->x_speed = -1;
            G->entities[2]->x_speed = 1;

            break;
        default:
            // Number of entities in the map
            G->entity_no = 1;

            // Set player attributes
            G->entities[PLAYER]->x_pos = 1;

            // Set enemies
            destroy_entity(G->entities[1]);

    }
    draw_to_background(BACKGROUND, 0, 0);
    draw_tile_map(&G->tile_map);
}

void destroy_game(game * G) {
    for (size_t i = 0; i < 10; i++) {
        destroy_entity(G->entities[i]);
    }
    free(G->entities);
    free(G->Mouse);
    free(G);
}
