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


extern void main() {
    /*
        Initialize the kernel.
    */
    k_io_init();
    x86_idt_init();
    x86_isr_init();
    
    kputs("Welcome to nos-os!\n");
}