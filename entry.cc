
#include "kernel.h"

extern "C" void _init();
extern "C" void _fini();

extern "C" void GlobalEntryPoint() {
	_init();
	os::Kernel::EntryPoint();
	_fini();
	asm("cli\nhlt\n");
	for (;;) {} // hang forever.
}
