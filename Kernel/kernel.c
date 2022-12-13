/*
    Made by Noah Van Miert
    12/12/2022

    NOS-KERNEL

    This file containts the entry point for the kernel.
*/

#include "Lib/stdio.h"
#include "Idt/idt.h"
#include "kpanic.h"


extern void main() {
    idt_init();
    k_io_init();

    kputs("Welcome to nos-os!\n");
}