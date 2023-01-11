/*
 *	Made by Noah Van Miert
 *	12/12/2022
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


const char *reverse(const char *str, char *buffer, int len)
{
	int i;
	for (i = 0; i <= len; i++){
		buffer[i] = str[len - i];
	}
	buffer[i] = '\0';
	return buffer;
}

char toStringRes[128];


void kputi(int n)
{
	
	char* buffer = toStringRes;
	int base = 10;
	int m = n;
	int i = 0;
    
    if(n < 0){                 // Negative integers
        m = -n;
    }
	
    while(m != 0){
		buffer[i] = (char)((m % base)+ (m % base > 9 ? 55 : 48));
		m = m / base;
		i++;
	}
    
    if(n < 0){
        buffer[i] = '-';
        i++;
    }
    
    if(n == 0){
        buffer[i] = '0';
        i++;
    }
	
	buffer[i] = '\0';
	char revBuf[128];
	//asm volatile("1: jmp 1b");
	if (n<10){
	    kputs("0");
	    kputs(reverse(buffer, revBuf, i-1));
	} else {
	kputs(reverse(buffer, revBuf, i-1));}
}


/*
    outb() - Sends a byte to a given
    port.
*/
void outb(uint16_t port, uint8_t value)
{
    __asm__ volatile ("outb %0, %1" :: "a"(value), "Nd"(port));
}


/*
    inb() - Gets a byte from a given
    port.
*/
uint8_t inb(uint16_t port)
{
    uint8_t value;

    __asm__ volatile("inb %1, %0"
                 : "=a"(value)
                 : "Nd"(port));

    return value;
}
