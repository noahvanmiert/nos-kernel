/*
    Made by Noah Van Miert
    12/12/2022

    NOS-KERNEL

    This file containts the entry point for the kernel.
*/

#include "Drivers/Vga/vga_driver.h"


extern void main() {
    struct VgaWriter writer = (struct VgaWriter) {
        .col = 0,
        .row = 0,
        .color_code = (uint8_t) vga_create_color_code(VGA_LIGHT_GREEN, VGA_BLACK),
        .buffer = (struct VgaBuffer *) VGA_MEMORY,
    };

    vga_write_string(&writer, "HELLO, FROM THE KERNEL!");
}