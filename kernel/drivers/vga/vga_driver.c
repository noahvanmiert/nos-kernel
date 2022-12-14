/*
    Made by Noah Van Miert
    12/12/2022

    NOS-KERNEL

    This file containts the definitions of the 
    vga driver functions.
*/

#include "vga_driver.h"
#include "../../lib/string.h"
#include "../../lib/stddef.h"


extern void outb(uint16_t port, uint8_t value);
extern uint8_t inb(uint16_t port);


/*
    create_color_code() - Generates a colorcode from a given
    foreground and background.
*/
inline uint8_t vga_create_color_code(enum VgaColor foreground, enum VgaColor background)
{
    return ((uint8_t) background << 4) | (uint8_t) foreground;
}


/*
    vga_reset() - Resets the row and col of the 
    writer object.

    NOTE: if you want to clear the screen you should
    use the vga_clear function.
*/
void vga_reset(struct VgaWriter *writer)
{
    writer->col = 0;
    writer->row = 0;
}


/*
    vga_clear() - Clears the screen and
    resets the writer object.
*/
void vga_clear(struct VgaWriter *writer)
{
    for (size_t i = 0; i < VGA_BUFFER_HEIGHT; i++) {
        for (size_t j = 0; j < VGA_BUFFER_WIDTH; j++) {
            vga_write_char_at(writer, j, i, ' ');
        }
    }

    writer->col = 0;
    writer->row = 0;    
}


/*
    vga_newline() - Sets the writers object so
    it prints the next character at the first
    column of the next row.
*/
void vga_newline(struct VgaWriter *writer)
{
    writer->row++;
    writer->col = 0;
}


/*
    vga_tab() - Sets the writer object so
    it prints the next character 4 spaces 
    from the location it is now.
*/
inline void vga_tab(struct VgaWriter *writer)
{
    writer->col += 4;
}


/*
    vga_vtab() - Same as the vga_tab function
    but is the simulate a vertical tab instead
    of a horizontal one.
*/
void vga_vtab(struct VgaWriter *writer)
{
    uint8_t s = writer->col;
    vga_newline(writer);
    writer->col = s;
}


/*
    vga_write_char_at() - Just writes a given
    character at the given location.
    
    NOTE: x should be smalled then VGA_BUFFER_WIDTH
          and y should be smaller than VGA_BUFFER_HEIGHT
*/
void vga_write_char_at(struct VgaWriter *writer, size_t x, size_t y, char chr)
{
    if (x < VGA_BUFFER_WIDTH && y < VGA_BUFFER_HEIGHT) {
        writer->buffer->chars[x + (y * 80)] = (struct VgaChar) {
            .chr = chr,
            .color_code = writer->color_code
        };
    }
}


/*
    vga_write_char() - Just writes a given character to
    the next location in the video memory.
*/
void vga_write_char(struct VgaWriter *writer, char chr)
{   
    /*
        If character is a '\0' return, this
        normaly doesn't happend but to be safe
        I've added this
     */
    if (unlikely(chr == '\0')) return;

    /* 
        Check if this is a special character
        if so we handle it and after that we return
     */
    switch (chr) {
        case '\n': {
            vga_newline(writer);
            return;
        }

        case '\t': {
            vga_tab(writer);
            return;
        }

        case '\v': {
            vga_vtab(writer);
            return;
        }
    }

    /*
        Check if the current col is still on the
        screen else put a newline first.
    */
    if (writer->col >= VGA_BUFFER_WIDTH)
        vga_newline(writer);

    /*
        For now we will just clear the screen when it's
        full.
    */
    if (writer->col >= VGA_BUFFER_WIDTH && writer->row >= VGA_BUFFER_HEIGHT)
        vga_clear(writer);

    uint16_t pos = writer->col + (writer->row * 80);

    /*
        Now write the character to the video memory
        located at 0xb8000.
    */
    writer->buffer->chars[pos] = (struct VgaChar) {
        .chr = chr,
        .color_code = writer->color_code
    };

    outb(0x3d4, 0x0f);
    outb(0x3d5, (uint8_t) (pos & 0xff));
    outb(0x3d4, 0x0e);
    outb(0x3d5, (uint8_t) ((pos >> 8) & 0xff));

    writer->col += 1;
}


/*
    vga_write_string - Prints a string by calling 
    vga_write_char for every character in the string.
*/
void vga_write_string(struct VgaWriter *writer, const char *str)
{   
    /*
        Just go trough every character 
        and print it.
    */
    for (size_t i = 0; i < strlen(str); i++)
        vga_write_char(writer, str[i]);
}