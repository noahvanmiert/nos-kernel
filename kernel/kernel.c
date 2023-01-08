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

// #define _KERNEL_VERBOSE_MODE 1

static void _kernel_init() 
{
    k_io_init();
    x86_idt_init();
    x86_isr_init();
    
#if _KERNEL_VERBOSE_MODE
    kputs("kernel initialisation: OK\n");
#endif
}


extern int main() {
    _kernel_init();
    
    kputs("Welcome to nos-os!\n");

	return 0;
}
