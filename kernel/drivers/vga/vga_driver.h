/*
 *	Made by Noah Van Miert
 *	12/12/2022
*/

#ifndef __VGA_DRIVER_H_
#define __VGA_DRIVER_H_

#include "../../lib/stdint.h"

#define VGA_MEMORY        (char *) 0xb8000

#define VGA_BUFFER_WIDTH  80
#define VGA_BUFFER_HEIGHT 25


enum VgaColor {
    VGA_BLACK,
    VGA_BLUE,
    VGA_GREEN,
    VGA_CYAN,
    VGA_RED,
    VGA_MAGENTA,
    VGA_BROWN,
    VGA_LIGHT_GREY,
    VGA_DARK_GRAY,
    VGA_LIGTH_BLUE,
    VGA_LIGHT_GREEN,
    VGA_LIGHT_CYAN,
    VGA_LIGHT_RED,
    VGA_PINK,
    VGA_YELLOW,
    VGA_WHITE
};


struct VgaChar {
    char chr;
    uint8_t color_code;
};


struct VgaBuffer {
    struct VgaChar chars[VGA_BUFFER_WIDTH * VGA_BUFFER_HEIGHT];
};


struct VgaWriter {
    size_t col;
    size_t row;
    uint8_t color_code;
    struct VgaBuffer *buffer;
};


uint8_t vga_create_color_code(enum VgaColor foreground, enum VgaColor background);

void vga_reset(struct VgaWriter *writer);
void vga_clear(struct VgaWriter *writer);

void vga_newline(struct VgaWriter *writer);
void vga_tab(struct VgaWriter *writer);

void vga_write_char_at(struct VgaWriter *writer, size_t x, size_t y, char chr);

void vga_write_char(struct VgaWriter *writer, char chr);
void vga_write_string(struct VgaWriter *writer, const char *str);


#endif
