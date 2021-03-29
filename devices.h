#ifndef _DEVICES_H_
#define _DEVICES_H_

#include "keyboard.h"
#include "i8042.h"
#include "game_physics.h"
#include "mouse.h"

/**
 * @author Diogo Faria
 * @defgroup devices Devices
 * Functions that alter the game with input and interrupts from certain devices
 * @{
 */

extern unsigned int timer_no_calls;

/**
 * @brief Handles the drawings of the game state in each timer interrupt
 * 
 * @param Game pointer to the struct of the current game
 */
void timer(game* Game);

/**
 * @brief Handles keyboard inputs
 * 
 * @param Game pointer to the struct of the current game
 */
void keyboard(game* Game);

/**
 * @brief Handles the mouse inputs
 * 
 * @param Game pointer to the struct of the current game
 */
void mouse(game* Game);

/**
 * @}
 */

#endif /* _DEVICES_H_  */
