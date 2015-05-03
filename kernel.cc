
// NOTE: this file contans a test entrypoint

#include "kernel.h"

namespace {
// marks an 'X' for each call.
void MarkX() {
	static int i = 0;
	// put character at location.
	((u16 *) 0xb8000)[i++] = (15 << 8) | 'X';
}
} // namespace

void os::Kernel::EntryPoint() {
	MarkX();
}
