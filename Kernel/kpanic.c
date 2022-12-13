#include "kpanic.h"

#include "Drivers/Vga/vga_driver.h"
#include "Lib/stdio.h"

/*
    kpanic() - Panics the kernel.
*/
void kpanic(const char *msg) 
{
    struct VgaWriter writer = (struct VgaWriter) {
        .col = 0,
        .row = 0,
        .color_code = (uint8_t) vga_create_color_code(VGA_LIGHT_RED, VGA_BLACK),
        .buffer = (struct VgaBuffer *) VGA_MEMORY
    };

    vga_clear(&writer);

    vga_write_string(&writer, "KERNEL PANICKED: ");
    vga_write_string(&writer, msg);

    // Disables the flashing cursor
    outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);

    for(;;);
}