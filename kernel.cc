
#include "kernel.h"
#include "driver/vga.h"
#include "bsod.h"
#include "io.h"

namespace basilisk {

Flags Flags::flags;

Flags::Flags() {
	// nothing yet...
}

Flags& Flags::GetInstance() { return flags; }

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
bool Flags::GetInterrupts() const {
	return Flags::GetInstance().Get() & Flags::kInterrupt;
}

void Flags::SetInterrupts(bool active) {
	if (active) {
		Flags::GetInstance().Set(Flags::GetInstance().Get() | Flags::kInterrupt);
	} else {
		Flags::GetInstance().Set(Flags::GetInstance().Get() & !Flags::kInterrupt);
	}
}

Kernel Kernel::kernel;

// NOTE: although Kernel seems dependent on VGAScreen's
// Instance method, the constructor needn't have run
// as
Kernel::Kernel() : screen(driver::VGAScreen::GetInstance()) {
	// do nothing
}

Kernel& Kernel::GetInstance() { return kernel; }

void Kernel::Do(Runnable& r, Permissions& p) {
	p.Invoke();
	r.Run(); // running job with interrupts setting
	p.Revoke();
}

Screen &Kernel::GetScreen() const {
	return screen;
}

void __attribute__((noreturn)) Kernel::Panic(const char *str) {
	BlueScreenOfDeath::Instance().Invoke(GetScreen(), str);
	Hang();
}

void Kernel::Halt() {
	asm("hlt\n"); // execute hlt instruction.
}

void __attribute__((noreturn)) Kernel::Hang() {
	Flags::GetInstance().SetInterrupts(false); // turn off interrupts
	Halt(); // halt the system.
	for (;;) {}
}

void Kernel::MessageUser(const char *msg) {
	Screen& screen = GetScreen();
	const Screen::Color& color = screen.GetColor();
	screen.SetColor(Screen::Color(Screen::Color::kWhite, Screen::Color::kRed));
	screen.Write(msg);
	screen.SetColor(color);
}

} // namespace basilisk
