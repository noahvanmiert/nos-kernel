/*
    Made by Noah Van Miert
    14/12/2022

    NOS-KERNEL
*/


#include "isr.h"
#include "idt.h"

#include "../../../lib/stdio.h"
#include "../../../kpanic.h"


extern void x86_isr0();
extern void x86_isr1();
extern void x86_isr2();
extern void x86_isr3();
extern void x86_isr4();
extern void x86_isr5();
extern void x86_isr6();
extern void x86_isr7();
extern void x86_isr8();
extern void x86_isr9();
extern void x86_isr10();
extern void x86_isr11();
extern void x86_isr12();
extern void x86_isr13();
extern void x86_isr14();
extern void x86_isr15();
extern void x86_isr16();
extern void x86_isr17();
extern void x86_isr18();
extern void x86_isr19();
extern void x86_isr20();
extern void x86_isr21();
extern void x86_isr22();
extern void x86_isr23();
extern void x86_isr24();
extern void x86_isr25();
extern void x86_isr26();
extern void x86_isr27();
extern void x86_isr28();
extern void x86_isr29();
extern void x86_isr30();
extern void x86_isr31();


void x86_isr_init()
{
    /*
        We need to set the gate for every
        interrupt manualy.
    */
    x86_idt_set_gate(0, x86_isr0, 0x08, 0x8e);
    x86_idt_set_gate(1, x86_isr1, 0x08, 0x8e);
    x86_idt_set_gate(2, x86_isr2, 0x08, 0x8e);
    x86_idt_set_gate(3, x86_isr3, 0x08, 0x8e);
    x86_idt_set_gate(4, x86_isr4, 0x08, 0x8e);
    x86_idt_set_gate(5, x86_isr5, 0x08, 0x8e);
    x86_idt_set_gate(6, x86_isr6, 0x08, 0x8e);
    x86_idt_set_gate(7, x86_isr7, 0x08, 0x8e);
    x86_idt_set_gate(8, x86_isr8, 0x08, 0x8e);
    x86_idt_set_gate(9, x86_isr9, 0x08, 0x8e);
    x86_idt_set_gate(10, x86_isr10, 0x08, 0x8e);
    x86_idt_set_gate(11, x86_isr11, 0x08, 0x8e);
    x86_idt_set_gate(12, x86_isr12, 0x08, 0x8e);
    x86_idt_set_gate(13, x86_isr13, 0x08, 0x8e);
    x86_idt_set_gate(14, x86_isr14, 0x08, 0x8e);
    x86_idt_set_gate(15, x86_isr15, 0x08, 0x8e);
    x86_idt_set_gate(16, x86_isr16, 0x08, 0x8e);
    x86_idt_set_gate(17, x86_isr17, 0x08, 0x8e);
    x86_idt_set_gate(18, x86_isr18, 0x08, 0x8e);
    x86_idt_set_gate(19, x86_isr19, 0x08, 0x8e);
    x86_idt_set_gate(20, x86_isr20, 0x08, 0x8e);
    x86_idt_set_gate(21, x86_isr21, 0x08, 0x8e);
    x86_idt_set_gate(22, x86_isr22, 0x08, 0x8e);
    x86_idt_set_gate(23, x86_isr23, 0x08, 0x8e);
    x86_idt_set_gate(24, x86_isr24, 0x08, 0x8e);
    x86_idt_set_gate(25, x86_isr25, 0x08, 0x8e);
    x86_idt_set_gate(26, x86_isr26, 0x08, 0x8e);
    x86_idt_set_gate(27, x86_isr27, 0x08, 0x8e);
    x86_idt_set_gate(28, x86_isr28, 0x08, 0x8e);
    x86_idt_set_gate(29, x86_isr29, 0x08, 0x8e);
    x86_idt_set_gate(30, x86_isr30, 0x08, 0x8e);
    x86_idt_set_gate(31, x86_isr31, 0x08, 0x8e);

    /* Enable all idt gates */
    for (int i = 0; i < 256; i++)
        x86_idt_enable_gate(i);
}


static const char *int_errors[] = {
	"Division by 0",
	"Single-Step interrupt (Debug)",
	"Non Maskable Interrupt",
	"Breakpoint",
	"Overflow",
	"Bound Range Exceeded",
	"Invalid Opcode",
	"Coprocessor Not Available",
	"Double Fault",
	"Coprocessor Segment Overrun",
	"Invalid Task State Segment",
	"Segment Not Present",
	"Stack Segment Fault",
	"General Protection Fault",
	"Page Fault",
	"Unkown Interrupt",
	"Coprocessor Fault",
	"Alignment Check",
	"Machine Check"
};


void __CDECL__ isr_handler(struct x86_Registers regs)
{
	if (regs.interrupt < 18) {
		kpanic(int_errors[regs.interrupt]);
	}
	
    // kputs("INTERRUPTED!\n");
}
