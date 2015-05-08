
#include "interrupts.h"
#include "io.h"

namespace basilisk {

Interrupts Interrupts::interrupts_;
GlobalDescriptor GlobalDescriptor::global_;

// zeroing default constructor
constexpr GlobalDescriptor::Entry::Entry() :
	limit(0),
	base1(0),
	base2(0),
	access(0),
	limit_flags(0),
	base3(0) {}

GlobalDescriptor::Entry::Entry(void *handler, u16 limit, u16 flags) :
	limit(limit & 0xffff), // limit 0:15
	access(flags & 0xff),
	limit_flags(((limit >> 16) & 0xf) | ((flags >> 8) & 0xf0)) // limit 16:19, flags
	{
	SetHandler(handler); // set bases to handler
}

void *GlobalDescriptor::Entry::GetHandler() {
	// reconstruct pointer from bases.
	return (void *) (base1 | base2 << 16 | base3 << 24);
}

void GlobalDescriptor::Entry::SetHandler(void *handler) {
	const u32 handle = (u32) handler;
	base1 = handle & 0xffff; // low half
	base2 = (handle >> 16) & 0xff; // high half, low byte
	base3 = (handle >> 24) & 0xff; // high half, high byte
}

GlobalDescriptor::Pointer::Pointer(u16 size, void *table) :
	limit(size - 1), // subtracts one so sizeof can be used.
	base((u32) table) {}

GlobalDescriptor::GlobalDescriptor() : ptr(sizeof(entries), &entries) {
	// default entry construction.
	entries[0] = Entry(0, 0, 0);
	entries[1] = Entry(0, (u16) 0x000fffff, Entry::kRing0CodeFlags);
	entries[2] = Entry(0, (u16) 0x000fffff, Entry::kRing0DataFlags);
	entries[3] = Entry(0, (u16) 0x000fffff, Entry::kRing3CodeFlags);
	entries[4] = Entry(0, (u16) 0x000fffff, Entry::kRing3DataFlags);
	Apply(); // initial application
}

void GlobalDescriptor::Apply() {
	// load new global descriptor table pointer
	asm(
		"lgdt (%0)\n" :: "r"((Pointer *) &ptr)
	);

	// reload segment registers
	asm (
		"jmpl $0x08, $1f\n"
		"1:\n"
		"mov $0x10, %ax\n"
		"mov %ax, %dx\n"
		"mov %ax, %es\n"
		"mov %ax, %fs\n"
		"mov %ax, %gs\n"
		"mov %ax, %ss\n"
	);
}

constexpr Interrupts::Entry::Entry() :
	base1(0),
	selector(0),
	flags(0),
	base2(0) {}

Interrupts::Entry::Entry(void *handler, u16 sel, u8 fl) :
	selector(sel),
	flags(fl) {
	SetHandler(handler); // set bases to handler
}

void *Interrupts::Entry::GetHandler() {
	return (void *) (base1 | base2 << 16);
}

void Interrupts::Entry::SetHandler(void *handler) {
	const u32 handle = (u32) handler;
	base1 = handle & 0xffff;
	base2 = (handle >> 16) & 0xffff;
}

Interrupts::Pointer::Pointer(u16 size, void *table) :
	limit(size - 1), // subtracts one so sizeof can be used.
	base((u32) table) {}

namespace {

extern "C" void handle() {
	IO::GetInstance().Put("Handler!\n");
}

// shitty interrupt handler
asm(
	".global handler\n"
	"handler:\n"
	"call handle\n"
	"iret\n"
);

extern "C" void handler();

} // namespace

Interrupts::Interrupts() : ptr(sizeof(entries), &entries) {
	// TODO: int 0x80 will crash the system.
	SetHandler(0x80, (void *) &handler);
	Apply(); // initial application.
}

void *Interrupts::GetHandler(int n) {
	return entries[n].GetHandler(); // return handler function
}

void Interrupts::SetHandler(int n, void *handler) {
	// set handler function for interrupt.
	entries[n] = Entry(handler, 0x08, Entry::kPresent | Entry::kInterruptGate);
}

// Load Interrupt Descriptor Table
void Interrupts::Apply() {
	asm(
		"lidt (%0)\n" :: "r"(&ptr)
	);
}

} // namespace basilisk
