[bits 32]

global idt_load
idt_load:
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