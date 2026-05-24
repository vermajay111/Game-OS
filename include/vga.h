#ifndef VGA_H
#define VGA_H

void vga_clear(unsigned char color);
void vga_put_pixel(int x, int y, unsigned char color);
void vga_draw_rect(int x, int y, int w, int h, unsigned char color);
void vga_fill_rect(int x, int y, int w, int h, unsigned char color);
void vga_draw_line(int x1, int x2, int y1, int y2, unsigned char color);
void vga_putchar(char c, int x, int y, unsigned char color);

#endif