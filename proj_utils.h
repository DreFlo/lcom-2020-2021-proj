#ifndef _PROJ_UTILS_H_
#define _PROJ_UTILS_H_

#include <lcom/lcf.h>

/**
 * @author André Flores
 * @defgroup proj_utils Project Utilities
 * Basic utitlity functions for use in the project
 * @{
 */

/**
 * @brief Converts a BCD number to pure binary. Works with up to 2 digits.
 * @param bcd_no Number to be converted.
 * @return Converted number.
 */
uint8_t utils_bcd_to_bin(uint8_t bcd_no);

/**
 * @}
 */

#endif //_PROJ_UTILS_H_
