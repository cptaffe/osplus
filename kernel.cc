
#include "kernel.h"
#include "io.h"

namespace basilisk {

Flags Flags::flags;

Flags& Flags::Instance() { return flags; }

u32 Flags::Get() const {
	u32 flags = 0;
	asm (
		// push eflags onto stack, return in eax register.
		"pushfl\n"
		"pop %0\n"
		: "=r"(flags)
	);
	return flags;
}

void Flags::Set(u32 f) {
	asm (
		"push %0\n"
		"popfl\n"
		:: "r"(f)
	);
}

Kernel Kernel::kernel;

Kernel::Kernel() {
	// do nothing
}

Kernel& Kernel::Instance() { return kernel; }

bool Kernel::Interrupts(bool active) {
	bool old = Flags::Instance().Get() & Flags::kInterrupt;
	if (active) {
		Flags::Instance().Set(Flags::Instance().Get() | Flags::kInterrupt);
	} else {
		Flags::Instance().Set(Flags::Instance().Get() & !Flags::kInterrupt);
	}
	return old;
}

void Kernel::Do(Runnable& r, bool interruptable) {
	bool old = Interrupts(interruptable);
	r.Run(); // running job with interrupts setting
	Interrupts(old);
}

} // namespace basilisk
