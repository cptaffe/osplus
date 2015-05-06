
#ifndef BOS_INTERFACE_H_
#define BOS_INTERFACE_H_

#include "buffer.h"
#include "types.h"

namespace basilisk {

// Writable interface
// Used to declare writable devices.
class Writeable {
public:
	virtual ~Writeable() {}
	virtual bool Write(const Buffer& buf);
};

class Readable {
public:
	virtual ~Readable() {}
	virtual bool Read(Buffer& buf);
};

class ReadWriteable : public Readable, Writeable {
public:
	virtual ~ReadWriteable() {}
};

} // namespace basilisk

#endif // BOS_INTERFACE_H_
