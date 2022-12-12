/*
    Made by Noah Van Miert
    12/12/2022

    NOS-KERNEL
*/

#ifndef __STDINT_H_
#define __STDINT_H_

typedef signed char int8_t;
typedef short  int  int16_t;
typedef int         int32_t;
typedef long   int  int64_t;

typedef unsigned char      uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long int  uint64_t;

typedef uint64_t size_t;

typedef unsigned long uintptr_t;

typedef int8_t bool_t;

#ifndef NULL
#define NULL ((void *) 0)
#endif

#define true 1
#define false 0

#endif // __STDINT_H_