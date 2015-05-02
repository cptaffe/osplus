
#include "io.h"

extern "C" void _init();
extern "C" void _fini();

extern "C" void GlobalEntryPoint() {
	_init();
	os::IO::PutLine("hello, world!");
	_fini();
	asm("cli\nhlt\n");
	for (;;) {} // hang forever.
}
