
#include "gamePlay.h"

int counter = 0;

void ih(game* Game){
    uint8_t t_bit_no = 0;
    int ipc_status, kbd_irq_set, timer_irq_set, mouse_irq_set, r, kbc_bit_no = 0, mouse_bit_no = 0;
    //struct packet mouse_by;
    message msg;
    vg_init(VBE_D_600p);

    timer_subscribe_int(&t_bit_no);
    timer_irq_set = BIT(t_bit_no);

    kbc_subscribe_int(&kbc_bit_no);
    kbd_irq_set = BIT(kbc_bit_no);
    
    //mouse_set_stream_mode();
    mouse_enable_data_report();
    mouse_subscribe_int(&mouse_bit_no);
    mouse_irq_set = BIT(mouse_bit_no);
    load_background();
    game_load_map(Game, 0);
    timer_set_frequency(0, 30);
    while (!(Game->leave)){
        if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
            printf("driver_receive failed with: %d", r);
            continue;
        }
        if (is_ipc_notify(ipc_status)){ 
            switch (_ENDPOINT_P(msg.m_source)){
                case HARDWARE:
                    if (msg.m_notify.interrupts & kbd_irq_set){
                        kbc_ih();
                        if (Game->g_state == PLAYING){
                            keyboard(Game);
                        }
                    }
                    
                    if (msg.m_notify.interrupts & mouse_irq_set){
                        mouse_ih();
                        if ((Game->g_state != PLAYING && Game->g_state != END) && (counter == 3)){
                            mouse_handle_bytes(&Game->Mouse->mouse_bytes);
                            mouse(Game);
                            counter = 0;
                        }
                        
                    }
                    
                    if (msg.m_notify.interrupts & timer_irq_set){
                        timer(Game);
                        if (timer_no_calls % 30 == 0) rtc_get_time(&Game->game_sec, &Game->game_min, &Game->game_hour);
                        timer_int_handler();
                    }
                    break;
                default:
                    break;
            }
        }
    }
    mouse_unsubscribe_int();
    kbc_unsubscribe_int();
    mouse_disable_data_report();
    timer_unsubscribe_int();
    vg_exit();
}

void game_func(char filepath[]) {
    game* Game = create_game(filepath);
    ih(Game);
    destroy_game(Game);
}
