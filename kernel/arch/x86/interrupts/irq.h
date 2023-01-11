/*
 *	Made by Noah Van Miert
 *	10/01/2023
*/

#ifndef __X86_IRQ_H_
#define __X86_IRQ_H_

#include "isr.h"

/*
 *	Standard ISA IRQs
 *
 *	0 - Programmable Interrupt Timer Interrupt
 *	1 - Keyboard Interrupt
 *	2 - Cascade (used internally by the two PICs, never raised)
 *	3 - COM2 (if enabled)
 *	4 - COM3 (if enabled)
 *	5 - LPT2 (id enabled)
 *	6 - Floppy Disk
 *	7 - LPT1 / Unreliable "spurios" interrupt (usually)
 *	8 - CMOS real-time clock (if enabled)
 *	9 - Free for peripherals / legacy SCSI / NIC
 *	10 - Free for peripherals / SCSI / NIC
 *	11 - Free for peripherals / SCSI / NIC
 *	12 - PS2 Mouse
 *	13 - FPU / Coprocessor / Inter-processor
 *	14 - Primary ATA Hard Disk
 *	15 - Secondary ATA Hard Disk
*/

void x86_irq_attach_handler(int irq, void (*handler)(struct x86_Registers *regs));
void x86_irq_dettach_handler(int irq);

void x86_irq_remap();
void x86_irq_init();
void x86_irq_wait(int n);

#endif // __X86_IRQ_H_
