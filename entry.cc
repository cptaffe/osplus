
#include "io.h"
#include "runnable.h"
#include "kernel.h"

extern "C" void _init();
extern "C" void _fini();

class test : public basilisk::Runnable {
	void Run() {
		using namespace basilisk;
		IO::PutLine(
			"Basilisk OS v0.0.1 (c) 2015 Connor Taffe. All rights reserved.\n\n"
		);
	}
};

extern "C" void GlobalEntryPoint() {
	using namespace basilisk;
	_init();
	IO::PutLine(
		"OS has successfully booted...\n"
	);
	test t;
	asm("sti\n");
	Kernel::Instance()->Do(&t);
	_fini();
	asm("cli\nhlt\n");
	for (;;) {} // hang forever.
}
