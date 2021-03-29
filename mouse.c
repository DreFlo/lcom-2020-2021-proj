
#include "mouse.h"

int m_hook_id = 3;
uint8_t bytes[3];
extern int counter;

int mouse_subscribe_int(int *bit_no){
    (*bit_no) = m_hook_id;
    if (sys_irqsetpolicy(MOUSE_IRQ, IRQ_EXCLUSIVE | IRQ_REENABLE, &m_hook_id) != 0){
        printf("Error: sysirqsetpolocy\n");
        return -1;
    }
    return 0;
}

int mouse_unsubscribe_int(){
    if (sys_irqrmpolicy(&m_hook_id) != 0){
        printf("Error: sys_irqrmpolocy");
        return -1;
    }
    return 0;
}

void (mouse_ih)(){
    uint8_t status;
    int tries = 0;
    while (tries < 5){
        if (util_sys_inb(STAT_REG, &status) != 0){
            continue;
        }
        if ((status & (TIMEOUT | PARITY)) != 0){
            uint8_t disc_byte;
            util_sys_inb(OUT_BUF, &disc_byte);
            return;
        }
        else {  
            util_sys_inb(OUT_BUF, &bytes[counter]);
            counter++;
            return;
        }
        tries++;
        tickdelay(micros_to_ticks(DELAY_US));
    }
    printf("Too many tries in mouse_ih");
}

int mouse_cmd(uint8_t cmd){
    uint8_t ans;
    int tries = 5;
    while(tries > 0){
        if (kbc_command(MOUSE_CONTROL_REG, WRITE_BYTE_TO_MOUSE, false) != 0){
            return -1;
        }
        kbc_command(MOUSE_IBF, cmd, false);
        ans = kbc_command(MOUSE_OBF, -1, true);
        if (ans == ACK){
            return 0;
        }
        else if (ans == NACK){
            tries--;
            continue;
        }
        return -1;
    }
    return -1;
}

int mouse_enable_data_report(){
    return mouse_cmd(ENABLE_DATA_REPORTING);
}

int mouse_disable_data_report(){
    return mouse_cmd(DISABLE_DATA_REPORTING);
}

int mouse_set_stream_mode(){
    return mouse_cmd(SET_STREAM_MODE);
}

void mouse_handle_bytes(struct packet* mouse_by){
    mouse_by->bytes[0] = bytes[0];
    mouse_by->bytes[1] = bytes[1];
    mouse_by->bytes[2] = bytes[2];
    
    mouse_by->rb = (bytes[0] & RB);
    mouse_by->mb = (bytes[0] & MB);
    mouse_by->lb = (bytes[0] & LB);
    mouse_by->x_ov = (bytes[0] & XOVFL);
    mouse_by->y_ov = (bytes[0] & YOVFL);

    mouse_by->delta_x = (uint16_t) bytes[1];
    if (mouse_by->bytes[0] & XMSB){
        mouse_by->delta_x |= (0xFF00);
    }

    mouse_by->delta_y = (uint16_t) bytes[2];
    if(mouse_by->bytes[0] & YMSB){
        mouse_by->delta_y |= (0xFF00);
    }
}

int state = INIT;

int check_line(game* Game, struct packet *bytes, struct mouse_ev* event, int16_t xi, int16_t yi, int16_t xf){
    if(state == INIT){
        if(event->type == LB_PRESSED){ //Start movement
            if((Game->Mouse->x_pos >= xi && Game->Mouse->x_pos <= xi + 50) && (Game->Mouse->y_pos >= yi && Game->Mouse->y_pos <= yi + 50)){ //Inside Beg Tile
                state = LINE;
            }
        }

    }
    else if (state == LINE){
        if (event->type == MOUSE_MOV){ //Line movement
            if ((in_boundaries(Game, xi, yi, xf) != 0) || (event->delta_x < 0 && abs(event->delta_x) > TOLERANCE)){ //Outisde Boundaries or Backwards move
                Game->Mouse->x_pos = xi + 15;
                Game->Mouse->y_pos = yi + 25;
                state = INIT;
            }
        }
        else if (event->type == LB_RELEASED){ //Finish Line
            if((Game->Mouse->x_pos >= xf && Game->Mouse->x_pos <= xf + 50) && (Game->Mouse->y_pos >= yi && Game->Mouse->y_pos <= yi + 50)){ //Done
                return 0;
            }
            else{
                Game->Mouse->x_pos = xi + 15;
                Game->Mouse->y_pos = yi + 25;
                state = INIT;
            }
        }
        else{
            Game->Mouse->x_pos = xi + 15;
            Game->Mouse->y_pos = yi + 25;
            state = INIT;
        }
    }
    return -1;
}

int in_boundaries(game* Game, int16_t xi, int16_t yi, int16_t xf){
    if (Game->Mouse->x_pos < xi){
        return -1;
    }
    else if (Game->Mouse->x_pos > xf + 50){
        return -1;
    }
    else if (Game->Mouse->y_pos < yi){
        return -1;
    }
    else if (Game->Mouse->y_pos > yi + 50){
        return -1;
    }
    else{
        return 0;
    }
}


void reset_counter(){
    counter = 0;
}
