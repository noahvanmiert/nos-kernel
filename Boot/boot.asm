; Made by Noah Van Miert  
; 11/12/2022              
;
; NOS-KERNEL


[org 0x7c00]

; Set teletype mode
mov ah, 0x0e

; load greeting_msg ptr into bx
mov bx, greeting_msg

; puts - Prints a string in Real Mode (16-bit)
; This only works in Real Mode because int relies on 
; the BIOS interrupt 0x10
puts:
    mov al, [bx]
    cmp al, 0
    je end
    int 0x10
    inc bx
    jmp puts

end:
    jmp $

greeting_msg: db "Welcome to nos-os!", 0

; Write bytes to the remaining space in the boot sector
times 510-($-$$) db 0
dw 0xaa55