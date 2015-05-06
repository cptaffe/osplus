
#ifndef BOS_BUFFER_H_
#define BOS_BUFFER_H_

#include "iterator.h"
#include "types.h"

namespace basilisk {

// Buffer class
// Serializable bytes.
class Buffer : public Iterable<const u8> {
public:
	class Iterator : public basilisk::Iterator<const u8> {
	public:
		Iterator(Buffer *b);
		virtual void Next();
		virtual bool Done();
		virtual const u8 &Get();
	private:
		Buffer *buf;
		size index = 0;
	};

	Buffer(const void *buf, size s);

	// implicit constructor targets strings.
	Buffer(const char *buf);
	virtual Iterator &Iter() const;
private:
	const u8 *obj;
	size len;
	mutable Iterator iter;
};

} // namespace basilisk

#endif // BOS_BUFFER_H_
