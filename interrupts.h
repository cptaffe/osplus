
#ifndef BOS_INTERRUPTS_H_
#define BOS_INTERRUPTS_H_

#include "types.h"

namespace basilisk {

// Singleton Global Descriptor Table.
class GlobalDescriptor {
public:
	class Entry {
	public:
		constexpr Entry();
		Entry(void *base, u16 limit, u16 flags);

		// TODO: get better constant names.
		enum {
			kDescCodeData = 1 << 4, // code or data descriptor
			kPresent = 1 << 7,
			kAvaliable = 1 << 12,
			kLongMode = 1 << 13,
			kLongSegSize = 1 << 14, // 32 bits long (16 is default)
			kLowGranularity = 1 << 15, // 4kb - 4gb (1b - 1mb is default)

			// Ring priviledges (0 is default)
			kPrivRing0 = (0 & 3) << 5,
			kPrivRing1 = (1 & 3) << 5,
			kPrivRing2 = (2 & 3) << 5,
			kPrivRing3 = (3 & 3) << 5,

			kMemAccess = 1 << 0,
			kMemPermissive = 1 << 1,

			// Expand Down or Conforming in Execute mode.
			kMemOther = 1 << 2,

			// Execute memory instead of Read memory.
			kMemExecute = 1 << 3,

			// Ring 0 (Kernel Space) memory settings
			kRing0CodeFlags = kDescCodeData | kPresent | kLongSegSize
				| kLowGranularity | kPrivRing0 | kMemExecute | kMemPermissive,
			kRing0DataFlags = kDescCodeData | kPresent | kLongSegSize
				| kLowGranularity | kPrivRing0 | kMemPermissive,

			// Ring 3 (User Space) settings
			kRing3CodeFlags = kDescCodeData | kPresent | kLongSegSize
				| kLowGranularity | kPrivRing3 | kMemExecute | kMemPermissive,
			kRing3DataFlags = kDescCodeData | kPresent | kLongSegSize
				| kLowGranularity | kPrivRing3 | kMemPermissive,
		};

		void *GetHandler();
		void SetHandler(void *handler);
	private:
		u16 limit;
		u16 base1;
		u8 base2;
		u8 access;
		u8 limit_flags;
		u8 base3;
	} __attribute__((packed));

	class Pointer {
	public:
		Pointer(u16 size, void *table);
	private:
		u16 limit;
		u32 base;
	} __attribute__((packed));

	static GlobalDescriptor& GetInstance() { return global_; }

	void Apply();
private:
	GlobalDescriptor();
	static GlobalDescriptor global_;
	Entry entries[5];
	Pointer ptr;
};


// Singleton Interrupts controller
class Interrupts {
public:
	class Entry {
	public:
		constexpr Entry();
		Entry(void *handler, u16 sel, u8 flags);

		void *GetHandler();
		void SetHandler(void *handler);
	private:
		u16 base1;
		u16 selector;
		u8 zero = 0;
		u8 flags;
		u16 base2;
	} __attribute__((packed));

	class Pointer {
	public:
		Pointer(u16 size, void *table);
	private:
		u16 limit;
		u32 base;
	} __attribute__((packed));

	static Interrupts& GetInstance() { return interrupts_; }

	void *GetHandler(int n);
	void SetHandler(int n, void *handler);

	void Apply();
private:
	Interrupts();
	static Interrupts interrupts_;
	Entry entries[256]; // all possible interrupts
	Pointer ptr;
};

} // namespace basilisk

#endif // BOS_INTERRUPTS_H_
