
#ifndef OS_TERMINAL_H_
#define OS_TERMINAL_H_

#include "types.h"

namespace os {
class Writer {
public:
	virtual ~Writer() {};
	virtual void WriteByte(u8 c) = 0;

	// convenience methods.
	void Write(const char *msg, size len);
};
} // namespace os

#endif // OS_TERMINAL_H_
