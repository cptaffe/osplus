
#include "kernel.h"
#include "io.h"

namespace basilisk {

Flags Flags::flags;

Flags::Flags() {
	// nothing yet...
}

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

// interrupt specific convenience function.
bool Flags::Interrupts() const {
	return Flags::Instance().Get() & Flags::kInterrupt;
}

void Flags::SetInterrupts(bool active) {
	if (active) {
		Flags::Instance().Set(Flags::Instance().Get() | Flags::kInterrupt);
	} else {
		Flags::Instance().Set(Flags::Instance().Get() & !Flags::kInterrupt);
	}
}

Kernel Kernel::kernel;

Kernel::Kernel() {
	// do nothing
}

Kernel& Kernel::Instance() { return kernel; }

void Kernel::Do(Runnable& r, bool interruptable) {
	bool old = Flags::Instance().Interrupts();
	Flags::Instance().SetInterrupts(interruptable);
	r.Run(); // running job with interrupts setting
	Flags::Instance().SetInterrupts(old);
}

} // namespace basilisk
