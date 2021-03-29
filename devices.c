#include "devices.h"

bool beg = true;

void timer(game* Game){
    switch(Game->g_state){
    case MENU: 
        draw_start_menu();
        draw_time(Game->game_sec, Game->game_min, Game->game_hour);
        draw_cursor(Game->Mouse->x_pos, Game->Mouse->y_pos);
        break;
    case PLAYING:
        handle_physics(Game);
        game_update_entities(Game);
        draw_game(Game);
        if ((Game->entities[PLAYER]->lives == 0) && (Game->entities[PLAYER]->death_frame >= 5)){
            Game->g_state = FINAL_MENU;
            reset_counter();
            sleep(1);
            break;
        }
        if (Game->entities[PLAYER]->x_pos > 800) game_load_map(Game, Game->map_no + 1);
        if (Game->map_no == 2){
            if ((Game->entities[PLAYER]->x_pos > 200 && Game->entities[PLAYER]->x_pos <= 250) && Game->entities[PLAYER]->y_pos > 240){
                Game->g_state = D_BRIDGE;
                Game->Mouse->x_pos = 215;
                Game->Mouse->y_pos = 325;
                draw_cursor(Game->Mouse->x_pos, Game->Mouse->y_pos);
                Game->entities[PLAYER]->x_speed = 0;
                Game->entities[PLAYER]->y_speed = 0;
                reset_counter();
            }
        }
        break;
    case D_BRIDGE:
        draw_game(Game);
        draw_cursor(Game->Mouse->x_pos, Game->Mouse->y_pos);
        break;
    case PAUSE_MENU:
        draw_pause_menu();
        draw_time(Game->game_sec, Game->game_min, Game->game_hour);
        draw_cursor(Game->Mouse->x_pos, Game->Mouse->y_pos);
        break;
    case FINAL_MENU:
        if (Game->curr_score > Game->top_score && Game->entities[PLAYER]->mov_state != DEAD) {
            write_top_score(Game->curr_score, Game->game_file);
            Game->top_score = Game->curr_score;
            Game->new_top_score = true;
        }
        draw_end_menu();
        draw_time(Game->game_sec, Game->game_min, Game->game_hour);
        if (Game->new_top_score) draw_xpm(NEW_RECORD, 0, 0);
        draw_cursor(Game->Mouse->x_pos, Game->Mouse->y_pos);
        break;
    case END:
        draw_xpm(GAME_OVER, 0, 0);
        changeBuffer();
        sleep(1);
        Game->leave = true;
        break;
    }
    changeBuffer();
}

void keyboard(game* Game){
    int size;
    bool make;
    if (kbc_handle_bytes(Game->kbd_bytes, &make, &size) == 0){
        if (size == 1){
            switch(Game->kbd_bytes[0]){
                case D_MAKE:
                    if (beg){
                        beg = false;
                        Game->entities[0]->x_speed = Game->p_x_speed;
                    }
                    Game->last_read = Game->kbd_bytes[0];
                    break;

                case D_BREAK:
                    beg = true;
                    Game->last_read = Game->kbd_bytes[0];
                    Game->entities[0]->x_speed = 0;
                    break;

                case A_MAKE:
                    if (beg){
                        Game->entities[0]->x_speed = -Game->p_x_speed;
                        beg = false;
                    }
                    Game->last_read = Game->kbd_bytes[0];
                    break;

                case A_BREAK:
                    beg = true;
                    Game->last_read = Game->kbd_bytes[0];
                    Game->entities[0]->x_speed = 0;
                    break;

                case SPACE_MAKE:
                    if (Game->entities[PLAYER]->y_speed >= 0) {
                        Game->entities[0]->y_speed = - Game->p_y_speed;
                    }
                    break;

                case ESC:
                    Game->g_state = PAUSE_MENU;
                    reset_counter();
                break;

                default:
                break;
            }
        }
    }
}

void mouse(game* Game){
    struct mouse_ev* event = mouse_detect_event(&Game->Mouse->mouse_bytes);
    
    Game->Mouse->x_pos += Game->Mouse->mouse_bytes.delta_x;
    Game->Mouse->y_pos -= Game->Mouse->mouse_bytes.delta_y;
    if(Game->Mouse->x_pos < 0){
        Game->Mouse->x_pos = 0;
    }
    else if(Game->Mouse->x_pos > 770){
        Game->Mouse->x_pos = 770;
    }
    
    if(Game->Mouse->y_pos < 0){
        Game->Mouse->y_pos = 0;
    }
    else if (Game->Mouse->y_pos > 565){
        Game->Mouse->y_pos = 565;
    }

    if(Game->g_state == D_BRIDGE){
        if(check_line(Game, &Game->Mouse->mouse_bytes, event, 200, 300, 550) == 0){
            Game->g_state = PLAYING;
            game_load_map(Game, Game->map_no + 1);
        }
    }
    else{
        if(event->type == LB_PRESSED){
            uint16_t x_pos = Game->Mouse->x_pos + 10;
            uint16_t y_pos = Game->Mouse->y_pos;
            if(x_pos >= 250 && x_pos <= 550){   
                if ((Game->g_state == MENU) && (y_pos >= 244 && y_pos <= 319)){ //START
                    Game->g_state = PLAYING;
                }
                else if ((Game->g_state == FINAL_MENU) && (y_pos >= 239 && y_pos <= 314)){ //RESTART
                    game_load_map(Game, 0);
                    Game->g_state = PLAYING;
                }
                else if((Game->g_state == PAUSE_MENU) && (y_pos >= 200 && y_pos <= 275)){ //CONTINUE
                    Game->g_state = PLAYING;
                }
                else if ((Game->g_state == PAUSE_MENU) && (y_pos >= 290 && y_pos <= 365)){ //RESTART
                    game_load_map(Game, 0);
                    Game->g_state = PLAYING;
                }
                else if (y_pos >= 384 && y_pos <= 459){ //END
                    Game->g_state = END;
                }
            }
        }
    }
}
