;   Made by Noah Van Miert
;   12/12/2022
;
;   NOS-KERNEL


[bits 32]

extern isr_handler


global x86_isr0
global x86_isr1
global x86_isr2
global x86_isr3
global x86_isr4
global x86_isr5
global x86_isr6
global x86_isr7
global x86_isr8
global x86_isr9
global x86_isr10
global x86_isr11
global x86_isr12
global x86_isr13
global x86_isr14
global x86_isr15
global x86_isr16
global x86_isr17
global x86_isr18
global x86_isr19
global x86_isr20
global x86_isr21
global x86_isr22
global x86_isr23
global x86_isr24
global x86_isr25
global x86_isr26
global x86_isr27
global x86_isr28
global x86_isr29
global x86_isr30
global x86_isr31
global x86_isr32


; This is repeated for every interrupt
; op to 32. One day I will do all the 255
x86_isr0:
    cli
    push byte 0
    push byte 0
    jmp x86_isr_common

x86_isr1:
    cli
    push byte 0
    push byte 1
    jmp x86_isr_common

x86_isr2:
    cli
    push byte 0
    push byte 2
    jmp x86_isr_common

x86_isr3:
    cli
    push byte 0
    push byte 3
    jmp x86_isr_common

x86_isr4:
    cli
    push byte 0
    push byte 4
    jmp x86_isr_common

x86_isr5:
    cli
    push byte 0
    push byte 5
    jmp x86_isr_common

x86_isr6:
    cli
    push byte 0
    push byte 6
    jmp x86_isr_common

x86_isr7:
    cli
    push byte 0
    push byte 7
    jmp x86_isr_common

x86_isr8:
    cli
    push byte 8
    jmp x86_isr_common


x86_isr9:
    cli
    push byte 0
    push byte 9
    jmp x86_isr_common


x86_isr10:
    cli
    push byte 10
    jmp x86_isr_common


x86_isr11:
    cli
    push byte 11
    jmp x86_isr_common


x86_isr12:
    cli
    push byte 12
    jmp x86_isr_common


x86_isr13:
    cli
    push byte 13
    jmp x86_isr_common


x86_isr14:
    cli
    push byte 14
    jmp x86_isr_common


x86_isr15:
    cli
    push byte 0
    push byte 15
    jmp x86_isr_common


x86_isr16:
    cli
    push byte 0
    push byte 16
    jmp x86_isr_common


x86_isr17:
    cli
    push byte 0
    push byte 17
    jmp x86_isr_common


x86_isr19:
    cli
    push byte 0
    push byte 19
    jmp x86_isr_common


x86_isr20:
    cli
    push byte 0
    push byte 20
    jmp x86_isr_common


x86_isr21:
    cli
    push byte 0
    push byte 21
    jmp x86_isr_common


x86_isr22:
    cli
    push byte 0
    push byte 22
    jmp x86_isr_common


x86_isr23:
    cli
    push byte 0
    push byte 23
    jmp x86_isr_common


x86_isr24:
    cli
    push byte 0
    push byte 24
    jmp x86_isr_common


x86_isr25:
    cli
    push byte 0
    push byte 25
    jmp x86_isr_common


x86_isr26:
    cli
    push byte 0
    push byte 26
    jmp x86_isr_common


x86_isr27:
    cli
    push byte 0
    push byte 27
    jmp x86_isr_common


x86_isr28:
    cli
    push byte 0
    push byte 28
    jmp x86_isr_common


x86_isr29:
    cli
    push byte 0
    push byte 29
    jmp x86_isr_common


x86_isr30:
    cli
    push byte 0
    push byte 30
    jmp x86_isr_common


x86_isr31:
    cli
    push byte 0
    push byte 31
    jmp x86_isr_common


x86_isr32:
    cli
    push byte 0
    push byte 32
    jmp x86_isr_common


x86_isr_common:
    pusha           ; pushed edi, esi, esp, ebx, edx, ecx, eax

    push ds
	push es
	push fs
	push gs

    mov ax, 0x10    ; user kernel data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax


    xor eax, eax
    mov ax, ds
    push eax

    push esp        ; pass pointer to stack to C
    call isr_handler
    add esp, 4

    pop eax

    pop gs
	pop fs
	pop es
	pop ds

    popa            ; pop what we pushed with pusha
    add esp, 8      ; remove error code and interrupt number
    iret            ; will pop: cs, eip, eflags, ss, esp