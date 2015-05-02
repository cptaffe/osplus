
#include "../standard.h"
#include "vga.h"

os::driver::VGAWriter os::driver::VGAWriter::vga;

os::driver::VGAWriter::VGAWriter() {
	// clear screen.
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
