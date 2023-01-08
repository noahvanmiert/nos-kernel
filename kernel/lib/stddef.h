/*
    Made by Noah Van Miert
    12/12/2022

    NOS-KERNEL
*/

#ifndef __STDDEF_H_
#define __STDDEF_H_

#ifndef NULL
#define NULL ((void *) 0)
#endif

typedef signed char bool_t;

enum bool_value {
    false = 0,
    true = 1
};


/* 
    These macros can optimize
    conditions if used correctly.
*/
#define likely(a)               __builtin_expect(!!(a), 1)
#define unlikely(a)             __builtin_expect(!!(a), 0)


/*
    Some macros for gcc attributes.
*/
#define __PACKED__              __attribute__((packed))
#define __CDECL__               __attribute__((cdecl))

#endif // __STDDEF_H_
