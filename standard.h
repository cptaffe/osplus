
#ifndef OS_STANDARD_H_
#define OS_STANDARD_H_

// This file defines standard functions that may have
// calls generated during compilation.

#include "types.h"

extern "C" void *memcpy(void *dest, const void *src, size n);

extern "C" void __cxa_pure_virtual();
extern "C" void __cxa_atexit(void (*func) (void *), void * arg, void * dso_handle);


void operator delete(void *ptr);

#endif // OS_STANDARD_H_
