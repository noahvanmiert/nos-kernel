; Made by Noah Van Miert
; 12/12/2022
; 
; NOS-KERNEL

[bits 32]
[extern main]

global _start
_start:
    ; Call the main function
    ; defined in kernel/kernel.c
    call main
    jmp $
