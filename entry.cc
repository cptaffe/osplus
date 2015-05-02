
#include "kernel.h"
#include "io.h"

extern "C" void _init();
extern "C" void _fini();

extern "C" void GlobalEntryPoint() {
	os::IO::PutLine("in GlobalEntryPoint\n");
	_init();
	os::Kernel::EntryPoint();
	_fini();
	//asm("cli\nhlt\n");
	for (;;) {
		os::IO::PutLine("hanging.\n");
	} // hang forever.
}
