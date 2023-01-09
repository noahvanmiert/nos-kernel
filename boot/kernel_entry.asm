;	Made by Noah Van Miert
;	12/12/2022


[bits 32]
[extern main]

global _start
_start:
    ; call the main function
    ; defined in kernel/kernel.c
    call main
    jmp $
