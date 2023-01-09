/*
 *	Made by Noah Van Miert
 *	13/12/2022
*/


#ifndef __IDT_H_
#define __IDT_H_

#include "../../../lib/stdint.h"


enum IDT_Flags {
    IDT_FLAG_GATE_TAKS          = 0x5,
    IDT_FLAG_GATE_16BIT_INT     = 0x6,
    IDT_FLAG_GATE_16BIT_TRAP    = 0x7,
    IDT_FLAG_GATE_32BIT_INT     = 0x8,
    IDT_FLAG_GATE_32BIT_TRAP    = 0x8,

    IDT_FLAG_RING_0             = (0 << 5),
    IDT_FLAG_RING_1             = (1 << 5),
    IDT_FLAG_RING_2             = (2 << 5),
    IDT_FLAG_RING_3             = (3 << 5),

    IDT_FLAG_PRESENT            = 0x80
};


void x86_idt_init();
void x86_idt_disable_gate(int interrupt);
void x86_idt_enable_gate(int interrupt);
void x86_idt_set_gate(uint32_t interrupt, void (*base)(), uint16_t segment_descriptor, uint8_t flags);

#endif // __IDT_H_
