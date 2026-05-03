#include "vga.h"

void kernel_main(){
    vga_clear(0x02);
    //vga_draw_rect(10, 10, 100, 100, 0x001);
    //vga_fill_rect(10, 10, 100, 100, 0x00);
    vga_draw_line(1, 1, 100, 100, 0x001);
    while (1);
    
}           