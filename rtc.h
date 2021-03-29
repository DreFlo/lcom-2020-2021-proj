#ifndef _RTC_H_
#define _RTC_H_

#include <lcom/lcf.h>
#include "proj_utils.h"

/**
 * @author André Flores
 * @defgroup rtc RTC
 * Basic functions for use of the RTC
 * @{
 */

#define RTC_ADDR_REG 0x70                           /** @brief RTC address register */
#define RTC_DATA_REG 0x71                           /** @brief RTC data register */
#define RTC_SEC_ADDR 0                              /** @brief RTC seconds' address */
#define RTC_MIN_ADDR 2                              /** @brief RTC minutes' address */
#define RTC_HOUR_ADDR 4                             /** @brief RTC hours' address */

static uint8_t bcd_sec, bcd_min, bcd_hour;          /** @brief RTC second, minute and hour values in BCD */
static unsigned int rtc_no_calls = 0;               /** @brief Number of calls to the RTC */

/**
 * @brief Updates the time saved in static variables. Should be called once every second.
 */
void rtc_update_time();

/**
 * @brief Gets time from rtc saves values in the parameters' addresses in binary
 * @param sec Pointer to the seconds' address
 * @param min Pointer to the minutes' address
 * @param hour Pointer to the hours' address
 */
void rtc_get_time(uint8_t * sec, uint8_t * min, uint8_t * hour);

/**
 * @}
 */

#endif //_RTC_H_
