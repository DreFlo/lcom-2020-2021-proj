#include "graphics.h"

int vbe_get_mode_info_AT_HOME(in_port_t mode, vbe_mode_info_t * vbe_mode) {
    mmap_t mem_map;
    reg86_t reg;
    // ALLOC
    if (lm_alloc(sizeof(*vbe_mode), &mem_map) == NULL) return 1;
    // MEMSET 0
    memset(&reg, 0, sizeof(reg));
    // CONF REG
    reg.intno = VBE_INTERRUPT;
    reg.ax = VBE_CALL | VBE_MODE_INFO;
    reg.cx = mode;
    reg.es = PB2BASE(mem_map.phys);
    reg.di = PB2OFF(mem_map.phys);
    // INT 86
    if (sys_int86(&reg) != 0) return 1;
    // WRITE MODE INFO
    (*vbe_mode) = *((vbe_mode_info_t *) mem_map.virt);
    // FREE
    if (lm_free(&mem_map)) return 0;
    return 1;
}

void* (vg_init)(uint16_t mode) {
    reg86_t r;
    vbe_mode_info_t vmi;
    struct minix_mem_range mr;
    int code;
    // MEMSET 0
    memset(&r, 0, sizeof(r));
    memset(&vmi, 0, sizeof(vmi));
    memset(&mr, 0, sizeof(mr));
    // SET VMI
    if (vbe_get_mode_info_AT_HOME(mode, &vmi) != 0) {
        printf("Error vbe_get_mode_info()\n");
        return NULL;
    }
    h_res = vmi.XResolution;
    v_res = vmi.YResolution;
    bits_per_pixel = vmi.BitsPerPixel;
    bytes_per_pixel = ceil(bits_per_pixel / 8);
    // ALLOW MEMORY MAPPING
    vram_size = h_res * v_res * bytes_per_pixel;
    mr.mr_base = vmi.PhysBasePtr;
    mr.mr_limit = mr.mr_base + vram_size;
    if( 0 != (code = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr))) {
        printf("sys_privctl (ADD_MEM) failed: %d\n", code);
        return NULL;
    }
    // MAP MEM
    video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vram_size);
    if(video_mem == MAP_FAILED) {
        printf("Error vm_map_phys()\n");
        return NULL;
    }
    // CONFIGURE VIDEO CARD
    r.intno = VBE_INTERRUPT;
    r.ax = VBE_CALL | VBE_SET_MODE;
    r.bx = VBE_LINEAR | mode;
    // CHANGE VBE MODE
    if (sys_int86(&r) != 0) {
        printf("Error sys_int86()\n");
        return NULL;
    }
    if (r.al != VBE_FUNC_SUP) {
        return NULL;
    }
    if (r.ah != VBE_SUCCESS_CALL) {
        return NULL;
    }
    // ALLOC BUFFERS
    main_buffer = (char *) malloc(vram_size);
    background_buffer = (char *) malloc(vram_size);
    start_menu_buffer = (char *) malloc(vram_size);
    pause_menu_buffer = (char *) malloc(vram_size);
    end_menu_buffer = (char *) malloc(vram_size);
    return video_mem;
}

int draw_pixel(uint16_t x, uint16_t y, uint32_t color, char* mem_ptr){
    switch (bytes_per_pixel)
    {
    case 1:
        memset(mem_ptr + y * h_res + x, color, 1);
        break;    
    default:
        memcpy(mem_ptr + ((y * h_res + x) * bytes_per_pixel), &color, bytes_per_pixel);
        break;
    }
    return 0;
}

void draw_xpm_(xpm_map_t xpm, uint16_t x, uint16_t y, char* mem_ptr) {
    uint8_t *map;
    xpm_image_t img;
    uint32_t colour;
    int subpixel = 0;
    map = xpm_load(xpm, XPM_8_8_8, &img);

    // FILL PIXELS
    for(unsigned int p = 0; p < img.height; p++){
        for(unsigned int i = 0; i < img.width; i++){
            if ((x + i) <= h_res && (y + p) <= v_res) {
                colour = ((map[subpixel + 2] << 16) & 0xFF0000) | ((map[subpixel + 1] << 8) & 0xFF00) | (map[subpixel] & 0xFF);

                if (colour != xpm_transparency_color(XPM_8_8_8)) {
                    draw_pixel(x + i, y + p, colour, mem_ptr);
                }
            }
            subpixel += 3;
        }
    }
}

void draw_xpm(xpm_map_t xpm, uint16_t x, uint16_t y) {
    draw_xpm_(xpm, x, y, main_buffer);
}

void draw_to_background(xpm_map_t xpm, uint16_t x, uint16_t y) {
    draw_xpm_(xpm, x, y, background_buffer);
}

void draw_img(xpm_image_t * img, uint16_t x, uint16_t y) {
    int subpixel = 0;
    uint32_t colour;

    for(unsigned int p = 0; p < img->height; p++){
        for(unsigned int i = 0; i < img->width; i++){
            colour = ((img->bytes[subpixel + 2] << 16) & 0xFF0000) | ((img->bytes[subpixel + 1] << 8) & 0xFF00) | (img->bytes[subpixel] & 0xFF);

            if (colour != xpm_transparency_color(XPM_8_8_8)) {
                draw_pixel(x + i, y + p, colour, main_buffer);
            }
            subpixel += 3;
        }
    }
}

void draw_start_menu() {
    memcpy(main_buffer, start_menu_buffer, vram_size);
}

void draw_pause_menu() {
    memcpy(main_buffer, pause_menu_buffer, vram_size);
}

void draw_end_menu() {
    memcpy(main_buffer, end_menu_buffer, vram_size);
}

void draw_cursor(uint16_t x, uint16_t y) {
    draw_img(&cursor, x, y);
}

void load_background() {
    draw_xpm_(BACKGROUND, 0, 0, background_buffer);

    draw_xpm_(BACKGROUND, 0, 0, start_menu_buffer);
    draw_xpm_(TITLE_BOX, 100, 50, start_menu_buffer);
    draw_xpm_(START_BOX, 250, 244, start_menu_buffer);
    draw_xpm_(QUIT_BOX, 250, 384, start_menu_buffer);

    draw_xpm_(BACKGROUND, 0, 0, pause_menu_buffer);
    draw_xpm_(TITLE_BOX, 100, 50, pause_menu_buffer);
    draw_xpm_(CONTINUE_BOX, 250, 200, pause_menu_buffer);
    draw_xpm_(RESTART_BOX, 250, 290, pause_menu_buffer);
    draw_xpm_(QUIT_BOX, 250, 384, pause_menu_buffer);

    draw_xpm_(BACKGROUND, 0, 0, end_menu_buffer);
    draw_xpm_(TITLE_BOX, 100, 50, end_menu_buffer);
    draw_xpm_(RESTART_BOX, 250, 239, end_menu_buffer);
    draw_xpm_(QUIT_BOX, 250, 384, end_menu_buffer);

    xpm_load(CURSOR, XPM_8_8_8, &cursor);
    xpm_load(ONE_LIFE, XPM_8_8_8, &L1);
    xpm_load(TWO_LIVES, XPM_8_8_8, &L2);
    xpm_load(THREE_LIVES, XPM_8_8_8, &L3);
    xpm_load(FOUR_LIVES, XPM_8_8_8, &L4);
    xpm_load(FIVE_LIVES, XPM_8_8_8, &L5);
}

void background_to_buffer() {
    memcpy(main_buffer, background_buffer, vram_size);
}

void draw_lives(uint8_t no_lives) {
    no_lives %= 6;
    switch (no_lives) {
        case 0:
            break;
        case 1:
            draw_img(&L1, 0, 0);
            break;
        case 2:
            draw_img(&L2, 0, 0);
            break;
        case 3:
            draw_img(&L3, 0, 0);
            break;
        case 4:
            draw_img(&L4, 0, 0);
            break;
        case 5:
            draw_img(&L5, 0, 0);
            break;
        default:
            break;
    }
}

void draw_score(uint8_t score) {
    if (score < 100) {
        draw_xpm(SCORE_DIGITS[score % 10], 752, 0);
        draw_xpm(SCORE_DIGITS[score / 10], 704, 0);
    }
}

void draw_time(uint8_t sec, uint8_t min, uint8_t hour) {
    draw_xpm(TIME_DIGITS[sec % 10], 755, 527);
    draw_xpm(TIME_DIGITS[sec / 10], 710, 527);
    draw_xpm(TIME_SEP, 665, 527);
    draw_xpm(TIME_DIGITS[min % 10], 620, 527);
    draw_xpm(TIME_DIGITS[min / 10], 575, 527);
    draw_xpm(TIME_SEP, 530, 527);
    draw_xpm(TIME_DIGITS[hour % 10], 485, 527);
    draw_xpm(TIME_DIGITS[hour / 10], 440, 527);
}

void changeBuffer(){
    memcpy(video_mem, main_buffer, vram_size);
}

void clearScreen(){
    memset(main_buffer, 0, vram_size);
}
