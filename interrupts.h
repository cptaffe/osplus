
#ifndef BOS_INTERRUPTS_H_
#define BOS_INTERRUPTS_H_

#include "types.h"

namespace basilisk {

// Singleton Interrupts controller
class Interrupts {
public:
	class Entry {
	public:
		Entry(u8 num, u32 base, u16 sel, u8 flags);
	private:
		u16 blow;
		u16 selector;
		u8 zero = 0;
		u8 flags;
		u16 bhigh;
	} __attribute__((packed));

	class Pointer {
	public:
		Pointer();
	private:
		u16 limit;
		u32 base;
	} __attribute__((packed));

	static Interrupts& Instance() { return interrupts_; }

	void SetHandler(int n, void *handler);

private:
	Interrupts();
	Load();
	static Interrupts interrupts_;
	Entry entries[256] = {0}; // all possible interrupts
	Pointer ptr;
};

} // namespace basilisk

#endif // BOS_INTERRUPTS_H_
