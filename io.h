
#ifndef BOS_FMT_H_
#define BOS_FMT_H_

#include "buffer.h"
#include "types.h"

namespace basilisk {

// Singleton Input/Output class.
class IO {
public:
	static IO &GetInstance() { return io; };

	// print many types of data
	IO& Put(Buffer buffer);
	IO& Put(u32 number, int base = 10);
private:
	static IO io;
};

} // namespace basilisk

#endif // BOS_FMT_H_
