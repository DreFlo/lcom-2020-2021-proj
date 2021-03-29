#include "entity.h"

Entity * create_entity(entity_type t, int x, int y) {
    Entity * entity = malloc(sizeof(Entity));

    entity->x_pos = x;
    entity->y_pos = y;

    entity->type = t;
    entity->dir = RIGHT;
    entity->mov_state = STATIONARY;

    entity->entity_frame_no = 5;
    entity->death_frame = 0;

    entity->anim_frame = FIRST;

    entity->x_speed = 0;
    entity->y_speed = 0;
    switch (t)
    {
    case PLAYER:
        entity->type = PLAYER;
        entity->hitbox_width = 42;
        entity->hitbox_height = 57;
        entity->entity_frame_no = 0;

        entity->lives = 3;

        entity->fwd_anim = create_asprite(5, PC_FWD);
        entity->fwd_jump_anim = create_asprite(5, PC_FWD_JUMP);
        entity->bwd_anim = create_asprite(5, PC_BWD);
        entity->bwd_jump_anim = create_asprite(5, PC_BWD_JUMP);
        entity->death_anim = create_asprite(5, PC_DEATH);
        break;
    case ENEMY:
        entity->type = ENEMY;
        entity->hitbox_width = 36;
        entity->hitbox_height = 57;
        entity->entity_frame_no = 0;

        entity->lives = 1;

        entity->fwd_anim = create_asprite(5, ENEMY_FWD);
        entity->bwd_anim = create_asprite(5, ENEMY_BWD);
        entity->fwd_jump_anim = create_asprite(5, ENEMY_FWD);
        entity->bwd_jump_anim = create_asprite(5, ENEMY_BWD);
        entity->death_anim = create_asprite(5, ENEMY_BWD);
        break;
    default:
        break;
    }
    return entity;
}

void draw_entity(Entity * entity) {
    //if (entity->lives < 1) return;   
    switch (entity->dir)
    {
    case RIGHT:
        switch (entity->mov_state)
        {
        case STATIONARY:
            draw_asprite(entity->fwd_anim, 0, entity->x_pos, entity->y_pos);
            break;
        case MOVE:
            draw_asprite(entity->fwd_anim, entity->anim_frame, entity->x_pos, entity->y_pos);
            break;
        case JUMP:
            draw_asprite(entity->fwd_jump_anim, entity->anim_frame, entity->x_pos, entity->y_pos);
            break;
        default:
            if (entity->death_frame >= 5) return;
            else if (entity->lives < 1 &&entity->death_frame < 5) {
                draw_asprite(entity->death_anim, entity->anim_frame, entity->x_pos, entity->y_pos);
                if (entity->type == PLAYER) tickdelay(micros_to_ticks(DELAY_US * 3));
                return;
            } 
            break;
        }
        break;
    default:
        switch (entity->mov_state)
        {
        case STATIONARY:
            draw_asprite(entity->bwd_anim, 0, entity->x_pos, entity->y_pos);
            break;
        case MOVE:
            draw_asprite(entity->bwd_anim, entity->anim_frame, entity->x_pos, entity->y_pos);
            break;
        case JUMP:
            draw_asprite(entity->bwd_jump_anim, entity->anim_frame, entity->x_pos, entity->y_pos);
            break;        
        default:
            if (entity->death_frame >= 5) return;
            else if (entity->lives < 1 &&entity->death_frame < 5) {
                draw_asprite(entity->death_anim, entity->anim_frame, entity->x_pos, entity->y_pos);
                if (entity->type == PLAYER) tickdelay(micros_to_ticks(DELAY_US * 3));
                return;
            } 
            break;
        }
        break;
    }
}

void update_entity_pos(Entity *entity) {
    if (entity->lives >= 1) {
        entity->x_pos += entity->x_speed;
        entity->y_pos += entity->y_speed;
        if (entity->x_pos < 0) {
            entity->x_pos = 1;
            entity->x_speed = 0;
        }
        if (entity->y_pos < 0) {
            entity->y_pos = 1;
            entity->y_speed = 0;
        }
    }
    if (entity->y_pos > 600) entity->lives = 0;
}

void update_entity_anim(Entity_p entity) {
    if (entity->lives < 1) {
        if (entity->mov_state != DEAD) {
            entity->mov_state = DEAD;
            entity->anim_frame = FIRST;
            entity->death_frame = 1;
        }
        else {
            entity->anim_frame = (entity->anim_frame + 1) % 5;
            if (entity->death_frame < 6) entity->death_frame++;
        }
        return;
    }

    if (entity->x_speed == 0 && entity->y_speed == 0) {
        entity->mov_state = STATIONARY;
        return;
    }

    if (entity->x_speed > 0) {
        entity->mov_state = MOVE;
        if (entity->dir == LEFT) {
            entity->dir = RIGHT;
            entity->anim_frame = FIRST;
        }
        else {
            entity->anim_frame = (entity->anim_frame + 1) % 5;
        }
    }

    else if (entity->x_speed < 0) {
        entity->mov_state = MOVE;
        if (entity->dir == RIGHT) {
            entity->dir = LEFT;
            entity->anim_frame = FIRST;
        }
        else {
            entity->anim_frame = (entity->anim_frame + 1) % 5;
        }
    }

    if (entity->y_speed != 0) {
        entity->mov_state = JUMP;
        entity->anim_frame = FIRST;
    }

    

    /*
    if (entity->lives < 1 && entity->anim_frame == FIFTH)
        return;
    else if(entity->anim_frame != FIFTH){
        entity->anim_frame++;
    }
    else{
        entity->anim_frame = FIRST;
    }
    */
}

void destroy_entity(Entity_p entity) {
    destroy_asprite(entity->fwd_anim);
    destroy_asprite(entity->fwd_jump_anim);
    destroy_asprite(entity->bwd_anim);
    destroy_asprite(entity->bwd_jump_anim);
    destroy_asprite(entity->death_anim);
}
