#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int hook_id = 0;
unsigned int timer_no_calls = 0;

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
    uint8_t st, ctrl, msb, lsb;
    uint16_t divisor = TIMER_FREQ / freq;

    timer_get_conf(timer, &st);
    ctrl = (timer << 6) | TIMER_LSB_MSB | (st & 0x0f);

    sys_outb(TIMER_CTRL, ctrl);

    util_get_LSB(divisor, &lsb);
    util_get_MSB(divisor, &msb);

    sys_outb(TIMER_0 + timer, lsb);
    sys_outb(TIMER_0 + timer, msb);
    return 0;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
    *bit_no = hook_id;
	if (sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id) != 0) {
		printf("Error sys_irqsetpolicy()");
		return 1;
	}
	return 0;
}

int (timer_unsubscribe_int)() {
    if (sys_irqrmpolicy(&hook_id) != 0) {
        printf("Error sys_irqrmpolicy()");
        return 1;
    }
    return 0;
}

void (timer_int_handler)() {
    timer_no_calls++;
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
	if (timer > 2) {
		return 1;
	}  
	uint32_t command = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer);
	if (sys_outb(TIMER_CTRL, command) != 0) {
		printf("Error sys_outb()");
		return 1;	
	}
	if (util_sys_inb(TIMER_0 + (int) timer, st) != 0) {
		printf("Error util_sys_inb()");
		return 1;
	}
	return 0;
}

int (timer_display_conf)(uint8_t timer, uint8_t st,
                        enum timer_status_field field) {
    union timer_status_field_val value;
    switch (field)
    {
    case tsf_all:
        value.byte = st;
        break;
    case tsf_initial:
        value.in_mode = (st & (BIT(5) | BIT(4))) >> 4;
        break;
    case tsf_mode:
        value.count_mode = (uint8_t) (st & (BIT(3) | BIT(2) | BIT(1))) >> 1;
        break;
    case tsf_base:
        value.bcd = (bool) st & TIMER_BCD;
        break;
    }
    if (timer_print_config(timer, field, value) != 0) {
        return 1;
    }
    return 0;
}
