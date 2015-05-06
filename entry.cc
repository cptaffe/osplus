
#include "io.h"
#include "runnable.h"
#include "kernel.h"
#include "types.h"

extern "C" void _init();
extern "C" void _fini();

class StartUp : public basilisk::Runnable {
	void Run() {
		using namespace basilisk;
		// indicate successful boot.
		IO::PutLine(
			"OS has successfully booted...\n"
			"Basilisk OS v0.0.1 (c) 2015 Connor Taffe. All rights reserved.\n"
		);
	}
};

void start() {
	using namespace basilisk;
	// test interrupts
	StartUp start;
	Kernel::Instance()->Do(&start);
}

extern "C" void GlobalEntryPoint() {
	_init();
	start();
	_fini();

	// hang forever.
	asm(
		"cli\n"
		"hlt\n"
	);
	for (;;) {}
}
