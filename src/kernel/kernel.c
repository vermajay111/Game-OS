#include "vga.h"

void kernel_main(){
    vga_clear(0x02);
    //vga_draw_rect(10, 10, 100, 100, 0x001);
    //vga_fill_rect(10, 10, 100, 100, 0x00);
    //vga_draw_line(1, 1, 100, 100, 0x001);
    vga_putchar('G', 100, 100, 0x001);
    vga_putchar('A', 108, 100, 0x001);
    vga_putchar('M', 116, 100, 0x001);
    vga_putchar('E', 124, 100, 0x001);

    vga_putchar('O', 140, 100, 0x001);
    vga_putchar('S', 148, 100, 0x001);


    while (1);
    
}           