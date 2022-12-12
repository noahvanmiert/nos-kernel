/*
    Made by Noah Van Miert
    12/12/2022

    NOS-KERNEL
*/

#ifndef __STDDEF_H_
#define __STDDEF_H_

#define likely(a)           __builtin_expect(!!(a), 1)
#define unlikely(a)         __builtin_expect(!!(a), 0)


/*
    If we for some reasen don't want
    to use inline functions anymore 
    we can just remove the inline in
    this macro.
*/
#define __inline__ inline

#endif // __STDDEF_H_