
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
class StartUpTask : public basilisk::Runnable {
public:
	static StartUpTask& GetInstance() { return start; }
	void Run() {
		using namespace basilisk;
		// indicate successful boot.
		IO::GetInstance().Put(
			"OS has successfully booted...\n"
			"Basilisk OS v0.0.1 (c) 2015 Connor Taffe. All rights reserved.\n"
		);
		asm("int $0x80\n"); // test interrupt
	}
private:
	static StartUpTask start;
};

StartUpTask StartUpTask::start;

extern "C" __attribute__((noreturn)) void main() {
	using namespace basilisk;
	Kernel::Start(); // kernel startup.

	Permissions p(true);
	Kernel::GetInstance().Do(StartUpTask::GetInstance(), p);

	Kernel::Stop(); // stop execution.
}
