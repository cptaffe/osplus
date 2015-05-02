
#ifndef OS_STANDARD_H_
#define OS_STANDARD_H_

// This file defines standard functions that may have
// calls generated during compilation.

#include "types.h"

extern "C" void *memcpy(void *dest, const void *src, size n);

#endif // OS_STANDARD_H_

