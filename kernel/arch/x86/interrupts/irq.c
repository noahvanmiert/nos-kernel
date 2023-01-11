/*
 *	Made by Noah Van Miert
 *	10/01/2023
*/

#include "irq.h"
#include "../../../lib/stdio.h"
#include "idt.h"
#include "isr.h"

extern void x86_irq0();
extern void x86_irq1();
extern void x86_irq2();
extern void x86_irq3();
extern void x86_irq4();
extern void x86_irq5();
extern void x86_irq6();
extern void x86_irq7();
extern void x86_irq8();
extern void x86_irq9();
extern void x86_irq10();
extern void x86_irq11();
extern void x86_irq12();
extern void x86_irq13();
extern void x86_irq14();
extern void x86_irq15();

extern void x86_irq_handler(struct x86_Registers *regs);

static void *routines[16] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0
};


void x86_irq_attach_handler(int irq, void (*handler)(struct x86_Registers *regs))
{
	if (irq < 15)
		routines[irq] = (void *) handler;

	
	kputs("succesfully attached handler\n");

	/*
	 * If the irq is bigger than 15, it is invalid 
	 * because there are only 16 irq's.
	*/
}


void x86_irq_dettach_handler(int irq)
{
	if (irq < 15)
		routines[irq] = NULL;

	/*
	 * If the irq is bigger than 15, it is invalid 
	 * because there are only 16 irq's.
	*/
}


void x86_irq_remap()
{
	/* write ICW1 to PIC1, we are gonna write commands to PIC1 */
	outb(0x20, 0x11);
	/* write ICW1 to PIC2, we are gonna write commands to PIC2 */
	outb(0xa0, 0x11);
	
	/* remap PIC1 to 0x20 (32 in decimal)*/
	outb(0x21, 0x20);
	/* remap PIC2 to 0x28 (40 in decimal) */
	outb(0xa1, 0x28);
	
	/* IRQ2 -> connection to slave */
	outb(0x21, 0x04);
	outb(0xa1, 0x02);

	/* write ICW4 to PIC1, we are gonna write commands to PIC1 */
	outb(0x21, 0x01);
	/* write ICW4 to PIC2, we are gonna write commands to PIC2 */
	outb(0xa1, 0x01);

	/* enable all IRQs on PIC1 */
	outb(0x21, 0x0);
	/* enable all IRQs on PIC2 */
	outb(0xa1, 0x0);
}


static volatile int current_interrupts[15];


void x86_irq_init()
{
	x86_irq_remap();

	x86_idt_set_gate(32, x86_irq0, 0x08, 0x8e);
	x86_idt_set_gate(33, x86_irq1, 0x08, 0x8e);
	x86_idt_set_gate(34, x86_irq2, 0x08, 0x8e);
	x86_idt_set_gate(35, x86_irq3, 0x08, 0x8e);
	x86_idt_set_gate(36, x86_irq4, 0x08, 0x8e);
	x86_idt_set_gate(37, x86_irq5, 0x08, 0x8e);
	x86_idt_set_gate(38, x86_irq6, 0x08, 0x8e);
	x86_idt_set_gate(39, x86_irq7, 0x08, 0x8e);
	x86_idt_set_gate(40, x86_irq8, 0x08, 0x8e);
	x86_idt_set_gate(41, x86_irq9, 0x08, 0x8e);
	x86_idt_set_gate(42, x86_irq10, 0x08, 0x8e);
	x86_idt_set_gate(43, x86_irq11, 0x08, 0x8e);
	x86_idt_set_gate(44, x86_irq12, 0x08, 0x8e);
	x86_idt_set_gate(45, x86_irq13, 0x08, 0x8e);
	x86_idt_set_gate(46, x86_irq14, 0x08, 0x8e);
	x86_idt_set_gate(47, x86_irq15, 0x08, 0x8e);

	for (int i = 0; i < 16; i++)
		current_interrupts[i] = 0;
}


extern void x86_irq_handler(struct x86_Registers *regs)
{
	current_interrupts[regs->interrupt - 32] = 1;
	void (*handler)(struct x86_Registers *regs);

	handler = (void (*)(struct x86_Registers *)) routines[regs->interrupt - 32];

	if (handler)
		handler(regs);
	
	/* If the irq is on PIC2 */
	if (regs->interrupt >= 40)
		outb(0xa0, 0x20);

	outb(0x20, 0x20);
}


void x86_irq_wait(int n)
{
	while (!current_interrupts[n]) {};

	current_interrupts[n] = 0;
}
