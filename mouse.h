#ifndef _MOUSE_H_
#define _MOUSE_H_

#include "keyboard.h"
#include "macros_mouse.h"
#include "game.h"

/**
 * @author Diogo Faria
 * @defgroup mouse Mouse
 * Basic functions for use of the mouse
 * @{
 */

int mouse_subscribe_int(int *bit_no);
int mouse_unsubscribe_int();

/**
 * @brief Sends a mouse command and checks for answer
 * 
 * @param cmd command to send
 * @return int 0 if successful, -1 otherwise
 */
int mouse_cmd(uint8_t cmd);

/**
 * @brief Enables data reporting
 * 
 * @return int 0 if successful, -1 otherwise
 */
int mouse_enable_data_report();

/**
 * @brief Disables data reporting
 * 
 * @return int 0 if successful, -1 otherwise
 */
int mouse_disable_data_report();

/**
 * @brief Sets stream mode
 * 
 * @return int 0 if successful, -1 otherwise
 */
int mouse_set_stream_mode();

/**
 * @brief Handles mouse bytes
 * 
 * @param mouse_by struct to fill with mouse input information (updated by the function)
 */
void mouse_handle_bytes(struct packet* mouse_by);

/**
 * @brief Resets the counter used to check if there were the 3 necessary bytes for the mouse input
 * 
 */
void reset_counter();

/**
 * @brief Checks the progress of the line used to create the bridge in-game
 * 
 * @param Game pointer to the struct of the current game
 * @param bytes pointer to the struct that containes the mouse input information
 * @param event pointer to the struct of the mouse event
 * @param xi x position in which the line starts
 * @param yi y position in which the line starts
 * @param xf x position in which the line ends
 * @return int 0 if finished, -1 if in progress
 */
int check_line(game* Game, struct packet *bytes, struct mouse_ev* event, int16_t xi, int16_t yi, int16_t xf);

/**
 * @brief Checks if, while the mouse left button is pressed, the line is being draw in the correct direction
 * 
 * @param Game pointer to the struct of the current game
 * @param xi x position in which the line starts
 * @param yi y position in which the line starts
 * @param xf x position in which the line ends
 * @return int 0 if in boundaries, -1 otherwise
 */
int in_boundaries(game* Game, int16_t xi, int16_t yi, int16_t xf);

/**
 * @}
 */

#endif /* _MOUSE_H_ */
