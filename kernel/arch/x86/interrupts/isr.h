/*
 *	Made by Noah Van Miert
 *	12/12/2022
*/

#ifndef __ISR_H_
#define __ISR_H_

#include "../../../lib/stdint.h"
#include "../../../lib/stddef.h"


struct x86_Registers {
	unsigned int gs, fs, es, ds;
	unsigned int edi, esi, ebp, ebx, edx, ecx, eax;
	unsigned int error, interrupt;
	unsigned int  eip, cs, eflags, useresp, ss;
} __PACKED__;


void x86_isr_init();

#endif // __ISR_H_
