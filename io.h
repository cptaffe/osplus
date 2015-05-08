
#ifndef BOS_FMT_H_
#define BOS_FMT_H_

#include "buffer.h"

namespace basilisk {

// Singleton Input/Output class.
class IO {
public:
	static IO &GetInstance() { return io; };

	// print many types of data
	IO& Put(Buffer buffer);
private:
	static IO io;
};

} // namespace basilisk

#endif // BOS_FMT_H_
