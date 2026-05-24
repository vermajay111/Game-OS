#include "vga.h"
#include "math.h"
#include "font.h"
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200
#define VIDEO_MEMORY ((unsigned char*)0xA0000)

void vga_clear(unsigned char color){
    for (int pixels = 0; pixels <= SCREEN_HEIGHT * SCREEN_WIDTH; pixels++){
        VIDEO_MEMORY[pixels] = color;
    }
}

void vga_put_pixel(int x, int y, unsigned char color){
    if ( x >= 0 && x <= SCREEN_WIDTH && y >= 0 && y <= SCREEN_HEIGHT){
        VIDEO_MEMORY[y*SCREEN_WIDTH + x] = color;
    }
}

void vga_draw_rect(int x, int y, int w, int h, unsigned char color){
    for (int width = 0; width <= w; width++){
        vga_put_pixel(x + width, y, color);
        vga_put_pixel(x + width, y + h, color);
    }
    for (int height = 0; height <= h; height++){
        vga_put_pixel(x, y + height, color);
        vga_put_pixel(x + w, y + height, color);
    }
}

void vga_fill_rect(int x,int y, int w, int h, unsigned char color){
    for(int height = 0; height < h - 1; height++){
        for (int width = 0; width < w -1; width++){
            vga_put_pixel(x+1 + width, y+1 + height, color);
        }
    }
}

void vga_draw_line(int x0, int y0, int x1, int y1, unsigned char color) {
    int dx = abs(x1 - x0);
    int dy = -abs(y1 - y0);

    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;

    int err = dx + dy;

    while (1) {
        vga_put_pixel(x0, y0, color);

        if (x0 == x1 && y0 == y1) break;

        int e2 = 2 * err;

        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}


void vga_putchar(char c, int x, int y, unsigned char color){
    const unsigned char* glyph = font8x8_basic[(int)c];

    for (int row = 0; row < 8; row++){
        for (int col = 0; col < 8; col++){
            if (glyph[row] & (1 << (col))){
                vga_put_pixel(x + col, y +row, color);
            }
        }
    }
}