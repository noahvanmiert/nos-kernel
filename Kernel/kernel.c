/*
    Made by Noah Van Miert
    12/12/2022

    NOS-KERNEL

    This file containts the entry point for the kernel.
*/

#include "Lib/stdio.h"

extern void main() {
    k_io_init();

    kputs("Hello, World!?123456789010\n");
}