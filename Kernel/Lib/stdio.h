#ifndef __STDIO_H_
#define __STDIO_H_

#include "stddef.h"
#include "stdint.h"

void k_io_init();
void kputc(char value);
void kputs(const char *value);

void outb(uint16_t port, uint8_t value);
uint8_t inb(uint16_t port);

#endif // __STDIO_H_