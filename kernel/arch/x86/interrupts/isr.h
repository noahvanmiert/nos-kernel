/*
 *	Made by Noah Van Miert
 *	12/12/2022
*/

#ifndef __ISR_H_
#define __ISR_H_

#include "../../../lib/stdint.h"
#include "../../../lib/stddef.h"


struct x86_Registers {
	uint32_t edi, esi, ebp, kern_esp, ebx, edx, ecx, eax;
	uint32_t gs, fs, es, ds;
	uint32_t eip, cs, interrupt, esp, ss;
	uint32_t eflags, error;
} __PACKED__;


void x86_isr_init();

#endif // __ISR_H_
