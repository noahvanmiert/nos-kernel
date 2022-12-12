/*
    Made by Noah Van Miert
    12/12/2022

    NOS-KERNEL
*/

#ifndef __STDDEF_H_
#define __STDDEF_H_

#define likely(a)           __builtin_expect(!!(a), 1);
#define unlikely(a)         __builtin_expect(!!(a), 0);

#endif // __STDDEF_H_