
#include "io.h"

extern "C" void _init();
extern "C" void _fini();

extern "C" void GlobalEntryPoint() {
	_init();
	os::IO::PutLine(
		"OS has successfully booted...\n"
		"Basilisk OS v0.0.1 (c) 2015 Connor Taffe. All rights reserved.\n\n"
	);
	_fini();
	asm("cli\nhlt\n");
	for (;;) {} // hang forever.
}
