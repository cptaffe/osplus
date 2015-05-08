
#ifndef BOS_KERNEL_H_
#define BOS_KERNEL_H_

#include "types.h"
#include "runnable.h"
#include "screen.h"

namespace basilisk {

// Singleton Flags class,
// manages the CPU's flags register.
class Flags {
public:
	static Flags& GetInstance();
	enum {
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
	u32 Get() const;
	void Set(u32);

	// Interrupt specific convenience functions
	bool GetInterrupts() const;
 	void SetInterrupts(bool active);
private:
	Flags();
	static Flags flags;
};

class Permissions {
public:
	explicit Permissions(bool ints) : interrupts(ints) {}
	void Invoke() {
		old_interrupts = Flags::GetInstance().GetInterrupts();
		Flags::GetInstance().SetInterrupts(interrupts);
	}
	void Revoke() {
		Flags::GetInstance().SetInterrupts(old_interrupts);
	}
private:
	bool interrupts;
	bool old_interrupts;
};

// Singleton Kernel class,
// manages the computer's resources.
class Kernel {
public:
	static Kernel& GetInstance();

	// call Run on a Runnable object.
	void Do(Runnable& r, Permissions &p);

	// screen getter
	Screen &GetScreen() const;

	void Halt(); // halt the system.
	void __attribute__((noreturn)) Hang(); // hang forever.

	// Kernel message to user.
	void MessageUser(const char *msg);
private:
	Kernel();
	static Kernel kernel;

	void __attribute__((noreturn)) Panic(const char *str);

	Screen &screen;
};

} // namespace basilisk

#endif // BOS_KERNEL_H_
