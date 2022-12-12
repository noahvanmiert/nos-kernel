/*
    Made by Noah Van Miert
    12/12/2022

    NOS-KERNEL

    This file containts the entry point for the kernel.
*/


extern void main() {
    *(char *) 0xb8000 = 'Q';
}