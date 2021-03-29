#ifndef _FILE_H_
#define _FILE_H_

#include <lcom/lcf.h>

/**
 * @author André Flores
 * @defgroup files Files
 * All code pertaining to reading and writing files in the game
 * @{
 */

/**
 * @brief Reads the top score from a file
 * @param filepath Filepath of the file to be read
 * @returns The top score
 */
int read_top_score(char filepath[]);

/**
 * @brief Writes new top score to file
 * @param new_score New top score
 */
void write_top_score(int new_score, char filepath[]);

/**
 * @}
 */

#endif //_FILE_H_
