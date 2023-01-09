/*
 *	Made by Noah Van Miert
 *	12/12/2022
*/

#include "kernel.h"

#include "lib/stdio.h"
#include "arch/x86/interrupts/idt.h"
#include "arch/x86/interrupts/isr.h"
#include "kpanic.h"


static void _kernel_init() 
{
    k_io_init();
    x86_idt_init();
    x86_isr_init();
	
	_kernel_verbose_msg("kernel version: ");
	_kernel_verbose_msg(KERNEL_VERSION);
	_kernel_verbose_msg("\n");

	_kernel_verbose_msg("kernel initialisation: OK\n");
}


extern int main() {
    _kernel_init();
 
    kputs("Welcome to nos-os!\n");

	return 0;
}
