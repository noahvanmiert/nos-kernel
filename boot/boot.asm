; Made by Noah Van Miert
; 12/12/2022
; 
; NOS-KERNEL

[org 0x7c00]         

BOOT_DISK: db 0

kernel_loc equ 0x1000                                    
mov [BOOT_DISK], dl                 

rm_main:
    xor ax, ax                          
    mov es, ax
    mov ds, ax
    mov bp, 0x8000
    mov sp, bp

    mov bx, kernel_loc
    
    ; The amount of sectors we want to read
    ; I think should be enough
    mov dh, 50

    mov ah, 0x02
    mov al, dh 
    mov ch, 0x00
    mov dh, 0x00
    mov cl, 0x02
    mov dl, [BOOT_DISK]
    int 0x13               

    ; Clear the screen            
    mov ah, 0x0
    mov al, 0x3
    int 0x10                


; Load gdt and enter protected mode
enter_pm:
    cli
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp seg_code:pm_main

%include "boot/gdt.asm"

[bits 32]
pm_main:
    ; Setup registers
    mov ax, seg_data
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
    
    ; Setup the stack
	mov ebp, 0x90000		
	mov esp, ebp

    jmp kernel_loc

; Fill the rest of the bootsector with 0
times 510-($-$$) db 0              
dw 0xaa55