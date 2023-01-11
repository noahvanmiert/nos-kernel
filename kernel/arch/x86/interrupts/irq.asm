;	Made by Noah Van Miert
;	10/01/2023


global x86_irq0
global x86_irq1
global x86_irq2
global x86_irq3
global x86_irq4
global x86_irq5
global x86_irq6
global x86_irq7
global x86_irq8
global x86_irq9
global x86_irq10
global x86_irq11
global x86_irq12
global x86_irq13
global x86_irq13
global x86_irq14
global x86_irq15



x86_irq0:
	cli
	push byte 0
	push byte 32
	jmp x86_irq_common


x86_irq1:
	cli
	push byte 0
	push byte 33
	jmp x86_irq_common


x86_irq2:
	cli
	push byte 0
	push byte 34
	jmp x86_irq_common


x86_irq3:
	cli
	push byte 0
	push byte 35
	jmp x86_irq_common


x86_irq4:
	cli
	push byte 0
	push byte 36
	jmp x86_irq_common


x86_irq5:
	cli
	push byte 0
	push byte 37
	jmp x86_irq_common


x86_irq6:
	cli
	push byte 0
	push byte 38
	jmp x86_irq_common


x86_irq7:
	cli
	push byte 0
	push byte 39
	jmp x86_irq_common


x86_irq8:
	cli
	push byte 0
	push byte 40
	jmp x86_irq_common


x86_irq9:
	cli
	push byte 0
	push byte 41
	jmp x86_irq_common


x86_irq10:
	cli
	push byte 0
	push byte 42
	jmp x86_irq_common


x86_irq11:
	cli
	push byte 0
	push byte 43
	jmp x86_irq_common


x86_irq12:
	cli
	push byte 0
	push byte 44
	jmp x86_irq_common


x86_irq13:
	cli
	push byte 0
	push byte 45
	jmp x86_irq_common


x86_irq14:
	cli
	push byte 0
	push byte 46
	jmp x86_irq_common


x86_irq15:
	cli
	push byte 0
	push byte 47
	jmp x86_irq_common



[extern] x86_irq_handler

x86_irq_common:
	pusha

	push ds
	push es
	push fs
	push gs

	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	mov eax, esp
	push eax
	mov eax, x86_irq_handler
	call eax

	pop eax
	pop gs
	pop fs
	pop es
	pop ds

	popa

	add esp, 8
	iret

