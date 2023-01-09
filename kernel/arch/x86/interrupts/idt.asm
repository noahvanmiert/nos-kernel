;   Made by Noah Van Miert
;   13/12/2022


[bits 32]

; loads the idt into the idt
; register
global x86_idt_load
x86_idt_load:
    push ebp
    mov ebp, esp

    ; Load idt
    mov eax, [ebp + 8]
    lidt [eax]

    mov esp, ebp
    pop ebp
    ret
