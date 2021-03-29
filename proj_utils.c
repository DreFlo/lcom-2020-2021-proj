#include "proj_utils.h"

uint8_t utils_bcd_to_bin(uint8_t bcd_no) {
    return (bcd_no / 0x10) * 10 + (bcd_no % 0x10);
}
