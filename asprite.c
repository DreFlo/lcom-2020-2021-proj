#include "asprite.h"
#include <lcom/xpm.h>

// PROB NOT WORKING
AnimSprite * (create_asprite)(unsigned no_pic, xpm_map_t array[]) {
    AnimSprite *asp = malloc(sizeof(AnimSprite));
    asp->frame_no = no_pic;
    asp->frames = array;   
    return asp;
}

void (draw_asprite)(AnimSprite *sprite, uint8_t frame_no, int x, int y){
    frame_no %= 5;
    draw_xpm(sprite->frames[frame_no], x, y);
}

void destroy_asprite(AnimSprite * sp) {
    free(sp);
}
