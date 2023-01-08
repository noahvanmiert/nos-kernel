/*
    Made by Noah Van Miert
    13/12/2022

    NOS-KERNEL
*/


#include "idt.h"
#include "../../../lib/stddef.h"


struct x86_IdtEntry {
    uint16_t base_low;
    uint16_t segment_selector;
    uint8_t reserved;
    uint8_t flags;
    uint16_t base_high;
} __PACKED__;


struct x86_IdtDiscriptor {
    uint16_t limit;
    struct x86_IdtEntry *ptr;
} __PACKED__;


struct x86_IdtEntry g_IDT[256];
struct x86_IdtDiscriptor g_IDTDescriptor = { sizeof(g_IDT) - 1, g_IDT };

extern void __CDECL__ x86_idt_load(struct x86_IdtDiscriptor *idt_discriptor);


void x86_idt_set_gate(uint32_t interrupt, void (*base)(), uint16_t segment_descriptor, uint8_t flags)
{
    g_IDT[interrupt].base_low = ((uint32_t) base) & 0xffff;
    g_IDT[interrupt].segment_selector = segment_descriptor;
    g_IDT[interrupt].reserved = 0;
    g_IDT[interrupt].flags = flags;
    g_IDT[interrupt].base_high = ((uint32_t) base >> 16) & 0xffff;
}


#define SET_FLAG(num, flag)    num |= (flag)
#define UNSET_FLAG(num, flag)  num &= ~(flag)


void x86_idt_enable_gate(int interrupt)
{
    SET_FLAG(g_IDT[interrupt].flags, IDT_FLAG_PRESENT);
}


void x86_idt_disable_gate(int interrupt)
{
    UNSET_FLAG(g_IDT[interrupt].flags, IDT_FLAG_PRESENT);
}


void x86_idt_init()
{
    x86_idt_load(&g_IDTDescriptor);
}
