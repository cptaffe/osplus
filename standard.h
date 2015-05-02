
#ifndef BOS_STANDARD_H_
#define BOS_STANDARD_H_

// This file defines standard functions that may have
// calls generated during compilation.

#include "types.h"

extern "C" void *memcpy(void *dest, const void *src, basilisk::size n);

#endif // BOS_STANDARD_H_
