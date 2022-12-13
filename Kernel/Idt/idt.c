#include "idt.h"

struct IDT_Entry {
    uint16_t base_low;
    uint16_t segment_selector;
    uint8_t reserved;
    uint8_t flags;
    uint16_t base_high;
} __attribute__((packed));


struct IDT_Discriptor {
    uint16_t limit;
    struct IDT_Entry *ptr;
} __attribute__((packed));


struct IDT_Entry g_IDT[256];
struct IDT_Discriptor g_IDTDescriptor = { sizeof(g_IDT) - 1, g_IDT };

extern void __attribute__((cdecl)) idt_load(struct IDT_Discriptor *idt_discriptor);

void idt_set_gate(uint32_t interrupt, void *base, uint16_t segment_descriptor, uint8_t flags)
{
    g_IDT[interrupt].base_low = ((uint32_t) base) & 0xffff;
    g_IDT[interrupt].segment_selector = segment_descriptor;
    g_IDT[interrupt].reserved = 0;
    g_IDT[interrupt].flags = flags;
    g_IDT[interrupt].base_high = ((uint32_t) base >> 16) & 0xffff;
}

#define SET_FLAG(num, flag)    num |= (flag)
#define UNSET_FLAG(num, flag)  num &= ~(flag)

void idt_enable_gate(int interrupt)
{
    SET_FLAG(g_IDT[interrupt].flags, IDT_FLAG_PRESENT);
}

void idt_disable_gate(int interrupt)
{
    UNSET_FLAG(g_IDT[interrupt].flags, IDT_FLAG_PRESENT);
}

void idt_init()
{
    idt_load(&g_IDTDescriptor);
}