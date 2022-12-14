;   Made by Noah Van Miert
;   13/12/2022
;
;   NOS-KERNEL


[bits 32]

global x86_idt_load
x86_idt_load:
    ; Make call frame
    push ebp
    mov ebp, esp

    ; Load idt
    mov eax, [ebp + 8]
    lidt [eax]

    ; Restore stack frame
    mov esp, ebp
    pop ebp
    ret