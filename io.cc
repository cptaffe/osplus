
#include "io.h"
#include "driver/vga.h"
#include "writeable.h"

namespace basilisk {

IO IO::io;

IO& IO::Put(Buffer buf) {
	driver::VGAWriter::Instance().Write(buf);
	return *this;
}

} // namespace basilisk
