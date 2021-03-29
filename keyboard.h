#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <lcom/lcf.h>
#include <stdint.h>

#include "i8042.h"

/**
 * @author Diogo Faria
 * @defgroup keyboard Keyboard
 * Basic functions for use of the keyboard
 * @{
 */


int kbc_subscribe_int(int *kbd_hook_id);
int kbc_unsubscribe_int();

/**
 * @brief Tests input buffer
 * 
 * @param kbc true if testing for keyboard, false if for mouse
 * @return int 0 if successful, -1 otherwise
 */
int kbc_test_ibf(bool kbc);

/**
 * @brief Writes a command byte
 * 
 * @param command Command to write
 * @param arg Argument for the command if needed, else -1
 * @param ret true if there's a return value, false otherwise
 * @return int return value or 0 if successful, -1 otherwise
 */
int kbc_command(uint8_t command, int arg, bool ret);

/**
 * @brief Handles the keyboard bytes
 * 
 * @param bytes array of bytes to handle
 * @param make true if makecode, false otherwise (value updated by the function)
 * @param size full scancode size (value updated by the function)
 * @return int 0 if successful, 1 if it was the first byte of a two byte scancode or -1 otherwise
 */
int kbc_handle_bytes(uint8_t *bytes, bool *make, int *size);

/**
 * @}
 */

#endif /*KEYBOARD_H*/
