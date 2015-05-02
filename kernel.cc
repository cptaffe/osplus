
// NOTE: this file contans a test entrypoint

#include "kernel.h"
#include "io.h"

void os::Kernel::EntryPoint() {
	os::IO::PutLine("Hello world!\n");
}
