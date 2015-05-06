
#include "interrupts.h"
#include "io.h"

Interrupts::Entry::Entry(u32 base, u16 sel, u8 fl) :
	blow(base & 0xffff),
	bhigh((base & 0xffff0000) >> 16),
	flags(fl),
	selector(sel) {}

Interrupts::Pointer::Pointer(u16 l, u32 b) : limit(l), base(b) {}

Interrupts::Interrupts() : ptr(sizeof(entries) - 1, &entries) {}

void Interrupts::SetHandler(int n, void *handler) {
	entries[n] = Entry(n, (u32) handler, 0x08, 0x8E);
	Load(); // reload entries
}

Interrupts::Load() {
	asm(
		"lidt %0\n"
		:: "r"(&ptr)
	);
}
