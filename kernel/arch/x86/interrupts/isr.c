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

void x86_isr_init()
{
    x86_idt_set_gate(0, x86_isr0, 0x08, 0x8e);
    x86_idt_set_gate(1, x86_isr1, 0x08, 0x8e);
    x86_idt_set_gate(2, x86_isr2, 0x08, 0x8e);
    x86_idt_set_gate(3, x86_isr3, 0x08, 0x8e);
    x86_idt_set_gate(4, x86_isr4, 0x08, 0x8e);
    x86_idt_set_gate(5, x86_isr5, 0x08, 0x8e);
    x86_idt_set_gate(6, x86_isr6, 0x08, 0x8e);
    x86_idt_set_gate(7, x86_isr7, 0x08, 0x8e);
    x86_idt_set_gate(8, x86_isr8, 0x08, 0x8e);


    // Enable all idt gates
    for (int i = 0; i < 256; i++)
        x86_idt_enable_gate(i);
}


void __CDECL__ isr_handler()
{
    kpanic("an error occurred");
}