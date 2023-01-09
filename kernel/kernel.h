/*
 *	Made by Noah Van Miert
 *	9/1/2023
*/

#ifndef __KERNEL_H_
#define __KERNEL_H_

#define KERNEL_VERSION "0.1.0"

#ifdef _KERNEL_VERBOSE_MODE
#define _kernel_verbose_msg(msg) kputs(msg)
#else
#define _kernel_verbose_msg(msg)
#endif // _KERNEL_VERBOSE_MODE

#endif // __KERNEL_H_
