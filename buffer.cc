
#include "buffer.h"

namespace basilisk {

Buffer::Iterator::Iterator(Buffer *b) : buf(b) {}

void Buffer::Iterator::Next() {
	index++;
}

bool Buffer::Iterator::Done() {
	return index == buf->len;
}

const u8 &Buffer::Iterator::Get() {
	return buf->obj[index];
}

Buffer::Buffer(const void *buf, size s) : obj(static_cast<const u8 *>(buf)), len(s), iter(this) {}

Buffer::Buffer(const char *buf) : Buffer(buf,
	[buf]()->size {
		size i;
		for(i = 0; buf[i] != '\0'; i++) {}
		return i;
	}()) {}

Buffer::Iterator &Buffer::Iter() const { return iter; }

} // namespace basilisk
