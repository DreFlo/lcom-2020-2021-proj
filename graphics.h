#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_


#include <lcom/lcf.h>
#include <machine/int86.h>
#include <lcom/vbe.h>
#include <minix/driver.h>
#include <sys/mman.h>
#include <math.h>
#include "graphics_macros.h"
#include "xpms.h"

/**
 * @author André Flores
 * @defgroup graphics Graphics
 * Basic graphics functions used in the game
 * @{
 */

static char *video_mem;		            /** @brief Process (virtual) address to which VRAM is mapped */
static char *main_buffer;               /** @brief Main buffer with colour information */
static char *background_buffer;         /** @brief Buffer with the background */
static char *start_menu_buffer;         /** @brief Buffer with the start menu */
static char *pause_menu_buffer;         /** @brief Buffer with the pause menu */
static char *end_menu_buffer;           /** @brief Buffer with the end menu */

static size_t vram_size;                /** @brief Size of the buffers */
static unsigned h_res;	                /** @brief Horizontal resolution in pixels */
static unsigned v_res;	                /** @brief Vertical resolution in pixels */
static unsigned bits_per_pixel;         /** @brief Number of VRAM bits per pixel */
static unsigned bytes_per_pixel;        /** @brief Number of bytes of color information per pixel*/

static xpm_image_t cursor;              /** @brief Xpm image with the cursor */
static xpm_image_t L1, L2, L3, L4, L5;  /** @brief  Xpm images with the life graphics */

/**
 * @brief Our own vbe_get_mode_info()
 */
int vbe_get_mode_info_AT_HOME(in_port_t mode, vbe_mode_info_t * vbe_mode);

/**
 * @brief Colours a pixel at certain coordinates in a specified buffer
 * @param x x coordinate of the pixel
 * @param y y coordinate of the pixel
 * @param colour colour info of the pixel
 * @param mem_ptr pointer to start of the the buffer to be drawn to
 * @return Zero on success. Non-zero otherwise.
 */
int draw_pixel(uint16_t x, uint16_t y, uint32_t color, char* mem_ptr);

/**
 * @brief Draws an xpm map at certain coordinates to a spcified buffer
 * @param xpm xpm to be drawn
 * @param x x coordinate of the top-lef-most pixel of the the image in the buffer
 * @param y y coordinate of the top-lef-most pixel of the the image in the buffer
 * @param mem_ptr pointer to start of the the buffer to be drawn to
 */
void draw_xpm_(xpm_map_t xpm, uint16_t x, uint16_t y, char* mem_ptr);

/**
 * @brief Draws an xpm map at certain coordinates to the main buffer
 * @param x x coordinate of the top-lef-most pixel of the the image in the buffer
 * @param y y coordinate of the top-lef-most pixel of the the image in the buffer
 */
void draw_xpm(xpm_map_t xpm, uint16_t x, uint16_t y);

/**
 * @brief Draws an xpm map at certain coordinates to the background buffer
 * @param x x coordinate of the top-lef-most pixel of the the image in the buffer
 * @param y y coordinate of the top-lef-most pixel of the the image in the buffer
 */
void draw_to_background(xpm_map_t xpm, uint16_t x, uint16_t y);

/**
 * @brief Draws an xpm img at certain coordinates to the main buffer
 * @param x x coordinate of the top-lef-most pixel of the the image in the buffer
 * @param y y coordinate of the top-lef-most pixel of the the image in the buffer
 */
void draw_img(xpm_image_t * img, uint16_t x, uint16_t y);

/**
 * @brief Draws start menu to the main buffer
 */
void draw_start_menu();

/**
 * @brief Draws pause menu to the main buffer
 */
void draw_pause_menu();

/**
 * @brief Draws end menu to main buffer
 */
void draw_end_menu();

/**
 * @brief Draws cursor at certain coordinates to the main buffer
 */
void draw_cursor(uint16_t x, uint16_t y);

/**
 * @brief Loads background and menu images to certain buffers
 */
void load_background();

/**
 * @brief Loads background to main buffer
 */
void background_to_buffer();

/**
 * @brief Draws the grphics for a given number of lives on screen
 * @param no_lives number of lives
 */
void draw_lives(uint8_t no_lives);

/**
 * @brief Draws a given score on the screen
 * @param score score to be drawn
 */
void draw_score(uint8_t score);

/**
 * @brief Draws given time on the screen
 * @param sec Seconds value
 * @param min Minutes value
 * @param hour Hours value
 */
void draw_time(uint8_t sec, uint8_t min, uint8_t hour);

/**
 * @brief Loads main buffer to video memory
 */
void changeBuffer();

/**
 * @brief Clears main buffer
 */
void clearScreen();

/**
 * @}
 */

#endif //_GRAPHICS_H_
