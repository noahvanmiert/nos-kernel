/*
    Made by Noah Van Miert
    12/12/2022

    NOS-KERNEL

    This file containts the entry point for the kernel.
*/

#include "lib/stdio.h"
#include "arch/x86/interrupts/idt.h"
#include "arch/x86/interrupts/isr.h"
#include "kpanic.h"

#ifdef _KERNEL_VERBOSE_MODE
#define _kernel_init_msg(msg) kputs(msg)
#else
#define _kernel_init_msg(msg)
#endif


static void _kernel_init() 
{
    k_io_init();
    x86_idt_init();
    x86_isr_init();

	_kernel_init_msg("kernel initialisation: OK\n");
}


extern int main() {
    _kernel_init();
 
    kputs("Welcome to nos-os!\n");

	return 0;
}
