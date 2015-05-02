
#include "../standard.h"
#include "vga.h"

os::driver::VGAWriter os::driver::VGAWriter::vga;

void os::driver::VGAWriter::Clear() {
	for (size li = 0; li < (kHeight * kWidth); li++) {
		buf[li] = (color << 8) | ' ';
	}
}

void os::driver::VGAWriter::Newline() {
	if (i != kHeight) {
		i = (i + 1) % kHeight;
	} else {
		memcpy(&buf[kWidth], buf, kWidth * (kHeight - 1));
	}
}

void os::driver::VGAWriter::WriteByte(u8 c) {
	if (!initialized) {
		Clear();
		initialized = true;
	}
	switch (c) {
	case '\n':
		Newline();
		// fallthrough
	case '\r':
		j = 0;
		break;
	default:
		buf[(i * kWidth) + j] = (color << 8) | c;
		j = (j + 1) % kWidth;
		if (j == 0) {
			// at end of line.
			Newline();
		}
	}
}
