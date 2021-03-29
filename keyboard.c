#include <lcom/lcf.h>
#include <minix/sysutil.h>
#include <minix/drivers.h>
#include "i8042.h"
#include "keyboard.h"
#include <stdint.h>

uint8_t scan_code;
int h_id = 1;
bool two;


int kbc_subscribe_int(int *kbd_hook_id){
    (*kbd_hook_id) = h_id;
    if (sys_irqsetpolicy(KBD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &h_id) != 0){
        printf("Error: sys_irqsetpolocy");
        return -1;
    }
    return 0;
}

int kbc_unsubscribe_int(){
    if (sys_irqrmpolicy(&h_id) != 0){
        printf("Error: sys_irqrmpolocy");
        return -1;
    }
    /*
    if (sys_irqdisable(&h_id) != 0){
        printf("Error: sys_irqrmpolocy");
        return -1;
    }
    */
    return 0;
}

void (kbc_ih)(){
    uint8_t status;
    int tries = 0;
    while (tries < 6){
        if (util_sys_inb(STAT_REG, &status) != 0){
            continue;
        }
        if (OBF & status){
            util_sys_inb(OUT_BUF, &scan_code);
            if ((status & (TIMEOUT | PARITY)) != 0){
                scan_code = 0;
                return;
            }
            else {
                return;
            }
        }
        tries++;
        break;
        tickdelay(micros_to_ticks(DELAY_US));
    }
}

int kbc_test_ibf(bool kbc){
    uint8_t status;
    while (true){
        if (util_sys_inb(STAT_REG, &status) != 0){
            return -1;
        }
        else{
            if (kbc){
                if ((status & IBF) == 0){
                    return 0;
                }
            }
            else{
                if (((status & IBF) && (status & AUX)) == 0){
                    return 0;
                }
            }
        }
        tickdelay(micros_to_ticks(DELAY_US));
    }
}

int kbc_command(uint8_t command, int arg, bool ret){
    uint32_t ret_value = 0;
    if (kbc_test_ibf(true) == 0){
        util_sys_inb(IN_BUF, &command);
        if (arg != -1){
            uint8_t arg1 = (arg & MSB);
            util_sys_inb(ARG, &arg1);
        }
        if (ret){
            sys_outb(OUT_BUF, ret_value);
            return ret_value;
        }
        return 0;
    }
    return -1;
}

int kbc_handle_bytes(uint8_t *bytes, bool *make, int *size){
    *make = true;
    if (scan_code == 0){ //Error
        return -1;
    }
    else if (scan_code == FIRST_OF_TWO_BYTES){
        bytes[0] = scan_code;
        two = true;
        return 1; //First byte of 2 filled
    }
    else if(two){
        bytes[1] = scan_code;
        two = false;
        if (scan_code & MAKECODE) {*make = false;}
        *size = 2;
        return 0; //Full scancode
    }
    else{
        printf("");
        bytes[0] = scan_code;
        if (scan_code & MAKECODE){
            *make = false;
        }
        *size = 1;
        return 0; //Full scancode
    }
}
