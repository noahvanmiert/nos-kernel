/*
    Made by Noah Van Miert
    12/12/2022

    NOS-KERNEL
*/


#include "stdio.h"

#include "../drivers/vga/vga_driver.h"

static struct VgaWriter g_writer;


/*
    k_io_init() - Initializes the kernels
    vga writer.

    NOTE: should always be called at
    the start of the main function.
*/
void k_io_init()
{
    g_writer = (struct VgaWriter) {
        .col = 0,
        .row = 0,
        .color_code = (uint8_t) vga_create_color_code(VGA_WHITE, VGA_BLACK),
        .buffer = (struct VgaBuffer *) VGA_MEMORY
    };
}


/*
    kputc() - Prints a given character
    to the screen.
*/
void kputc(char value)
{
    vga_write_char(&g_writer, value);
}


/*
    kputs() - Prints a given string to
    the screen.
*/
void kputs(const char *value)
{
    vga_write_string(&g_writer, value);
}


/*
    outb() - Sends a byte to a given
    port.
*/
void outb(uint16_t port, uint8_t value)
{
    asm volatile ("outb %0, %1" :: "a"(value), "Nd"(port));
}


/*
    inb() - Gets a byte from a given
    port.
*/
uint8_t inb(uint16_t port)
{
    uint8_t value;

    asm volatile("inb %1, %0"
                 : "=a"(value)
                 : "Nd"(port));

    return value;
}