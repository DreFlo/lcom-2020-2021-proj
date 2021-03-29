#include "rtc.h"

void rtc_update_time() {
    sys_outb(RTC_ADDR_REG, RTC_SEC_ADDR);
    util_sys_inb(RTC_DATA_REG, &bcd_sec);

    if ((bcd_sec < 0x02) || (rtc_no_calls == 0)) {        
        sys_outb(RTC_ADDR_REG, RTC_MIN_ADDR);
        util_sys_inb(RTC_DATA_REG, &bcd_min);

        if ((bcd_min < 0x02) || (rtc_no_calls == 0)) {        
            sys_outb(RTC_ADDR_REG, RTC_HOUR_ADDR);
            util_sys_inb(RTC_DATA_REG, &bcd_hour);       
        }
    }

    rtc_no_calls++;
}

void rtc_get_time(uint8_t * sec, uint8_t * min, uint8_t * hour) {
    rtc_update_time();
    (*sec) = utils_bcd_to_bin(bcd_sec);
    (*min) = utils_bcd_to_bin(bcd_min);
    (*hour) = utils_bcd_to_bin(bcd_hour);
}
