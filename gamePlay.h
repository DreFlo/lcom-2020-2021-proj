#ifndef _GAMEPLAY_H_
#define _GAMEPLAY_H_

#include "game_physics.h"
#include "devices.h"
#include "i8042.h"
#include "i8254.h"
#include "tiles.h"
#include "rtc.h"

/**
 * @author Diogo Faria
 * @defgroup gameplay Gameplay
 * Functions that handle the overall gameplay
 * @{
 */

/**
 * @brief Handles the overall game, by handling the inturrupts from the keyboard, mouse and timer
 * @param Game pointer to the struct of the current game
 */
void ih(game* Game);

/**
 * @brief Only function needed to be called to run a game
 * @param filepath Filepath of the top score file
 */
void game_func(char filepath[]);

/**
 * @}
 */

#endif /* _GAMEPLAY_H_  */
