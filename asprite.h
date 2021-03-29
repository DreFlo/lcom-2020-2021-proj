/**
 *  @author Joao Cardoso (jcard@fe.up.pt) ????
 *  Added by pfs@fe.up.pt
 */

#ifndef _ASPRITE_H_
#define _ASPRITE_H_

#include <stdarg.h>
#include "graphics.h"

/** @defgroup animsprite AnimSprite
 * @{
 *
 * Animated Sprite related functions
 */

/** An Animated Sprite is a "sub-classing" of Sprites
 *  where each Sprite is manipulated using Sprite functions
 */
typedef struct {
    uint8_t frame_no;           /* Number of separate frames in the AnimSprite */
	xpm_map_t * frames;         /* Pointers to xpm_maps of the animation frames */
} AnimSprite;

/** 
 * @brief Creates an AnimSprite
 * @param no_pic Number of animation frames
 * @param frames Array with xpm maps for the animation frames 
 */
AnimSprite* create_asprite(unsigned no_pic, xpm_map_t frames[]);

/**
 * @brief Draws sprite's animation frame frame_no at position (x, y)
 * @param sprite AnimSprite to be drawn
 * @param frame_no Number of animation frame to be drawn
 * @param x x coordinate
 * @param y y coordinate
 */
void draw_asprite(AnimSprite *sprite, uint8_t frame_no, int x, int y);

/**
 * @brief Destroys argument AnimSprite
 * @param sp AnimSprite to be destroyed
 */
void destroy_asprite(AnimSprite * sp);

/** @} end of sprite */

#endif
