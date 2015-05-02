
#ifndef BOS_KERNEL_H_
#define BOS_KERNEL_H_

#include "types.h"
#include "runnable.h"

namespace basilisk {

class Kernel {
public:
	Kernel();
	static Kernel *Instance();

	// call Run on a Runnable object.
	void Do(Runnable *r, bool interruptable = true);

private:
	static Kernel kernel;

	enum Flag {
		// flags
		kCarry = 1 << 0,
		kParity = 1 << 2,
		kAdjust = 1 << 4,
		kZero = 1 << 6,
		kSign = 1 << 7,
		kTrap = 1 << 8,
		kInterrupt = 1 << 9,
		kDirection = 1 << 10,
		kOverflow = 1 << 11,
		kIOPriviledge = 1 << 12,
		kNestedTask = 1 << 14,
		// eflags
		kResume = 1 << 16,
		kVirtual = 1 << 17,
		kAlignment = 1 << 18,
		kVirtualInterrupt = 1 << 19,
		kVirtualInterruptPending = 1 << 20,
		kCPUIDAvaliable = 1 << 21,
	};

	u32 flag();
	void set_flag(u32 f);

	// getter and setter for interrupts
	bool interrupt();
	void set_interrupt(bool active);
};

} // namespace basilisk

#endif // BOS_KERNEL_H_
