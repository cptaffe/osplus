
#include "kernel.h"
#include "io.h"

basilisk::Kernel basilisk::Kernel::kernel;

basilisk::Kernel::Kernel() {
	// do nothing
}

basilisk::Kernel *basilisk::Kernel::Instance() {
	return &kernel;
}

basilisk::u32 basilisk::Kernel::flag() {
	using namespace basilisk;
	u32 flags = 0;
	asm (
		// push eflags onto stack, return in eax register.
		"pushfl\n"
		"pop %0\n"
		: "=r"(flags)
	);
	return flags;
}

void basilisk::Kernel::set_flag(basilisk::u32 f) {
	asm (
		"push %0\n"
		"popfl\n"
		:: "r"(f)
	);
}

bool basilisk::Kernel::interrupt() {
	// returns if kInterrupt is set.
	return flag() & kInterrupt;
}

void basilisk::Kernel::set_interrupt(bool active) {
	using namespace basilisk;
	if (active) {
		set_flag(flag() | kInterrupt);
	} else {
		set_flag(flag() & !kInterrupt);
	}
}

void basilisk::Kernel::Do(Runnable *r, bool interruptable) {
	using namespace basilisk;
	bool level = interrupt();
	if (level) {
		IO::PutLine("interrupts are on");
	} else {
		IO::PutLine("interrupts are off");
	}
	set_interrupt(interruptable);
	r->Run(); // running job without interrupts;
	set_interrupt(level);
}
