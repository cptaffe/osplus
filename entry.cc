
#include "io.h"
#include "runnable.h"
#include "kernel.h"
#include "types.h"

extern "C" void _init();
extern "C" void _fini();

// StartUp Singleton.
class StartUp : public basilisk::Runnable {
public:
	static StartUp& Instance() { return start; }
	void Run() {
		using namespace basilisk;
		// indicate successful boot.
		IO::Instance()
		.Put("OS has successfully booted...\n")
		.Put("Basilisk OS v0.0.1 (c) 2015 Connor Taffe. All rights reserved.\n");
	}
private:
	static StartUp start;
};

StartUp StartUp::start;

extern "C" __attribute__((noreturn)) void GlobalEntryPoint() {
	_init();
	basilisk::Kernel::Instance().Do(StartUp::Instance());
	_fini();

	// hang forever.
	asm("cli\nhlt\n");
	for (;;) {}
}
