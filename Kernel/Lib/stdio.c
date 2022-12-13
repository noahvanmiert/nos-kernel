#include "stdio.h"

#include "../Drivers/Vga/vga_driver.h"

static struct VgaWriter g_writer;


void k_io_init()
{
    g_writer = (struct VgaWriter) {
        .col = 0,
        .row = 0,
        .color_code = (uint8_t) vga_create_color_code(VGA_WHITE, VGA_BLACK),
        .buffer = (struct VgaBuffer *) VGA_MEMORY
    };
}


void kputc(char value)
{
    vga_write_char(&g_writer, value);
}


void kputs(const char *value)
{
    vga_write_string(&g_writer, value);
}


void outb(uint16_t port, uint8_t value)
{
    asm volatile ("outb %0, %1" :: "a"(value), "Nd"(port));
}

uint8_t inb(uint16_t port)
{
    uint8_t value;

    asm volatile("inb %1, %0"
                 : "=a"(value)
                 : "Nd"(port));

    return value;
}