
#include "io.h"
#include "runnable.h"
#include "kernel.h"
#include "types.h"
#include "bsod.h"

// This file is called 'main' because it contains the entry
// point of the OS, which I have named 'main'.

extern "C" void _init();
extern "C" void _fini();

// StartUp Singleton.
class StartUp : public basilisk::Runnable {
public:
	static StartUp& GetInstance() { return start; }
	void Run() {
		using namespace basilisk;
		// indicate successful boot.
		IO::GetInstance().Put(
			"OS has successfully booted...\n"
			"Basilisk OS v0.0.1 (c) 2015 Connor Taffe. All rights reserved.\n"
		);
	}
private:
	static StartUp start;
};

StartUp StartUp::start;

extern "C" __attribute__((noreturn)) void main() {
	using namespace basilisk;
	// Inerrupts are off by default.
	_init();

	// Do work after constructors have been run.
	Permissions p(true);
	Kernel::GetInstance().Do(StartUp::GetInstance(), p);

	// Use kernel's printing abilities
	Kernel::GetInstance().MessageUser("System halting!\n");

	// run destructors & call hang on Kernel object.
	// NOTE: this is a reason the kernel object may not be allocated
	// in non-static memory.
	_fini();
	Kernel::GetInstance().Hang();
}
