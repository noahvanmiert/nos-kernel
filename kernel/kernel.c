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

static char verbose_mode = true;

static void _kernel_init() 
{
    k_io_init();
    x86_idt_init();
    x86_isr_init();
    
    if (verbose_mode)
        kputs("kernel initialisation: OK\n");
}


extern void main() {
    _kernel_init();
    
    asm("int $0x17");

    kputs("Welcome to nos-os!\n");
}