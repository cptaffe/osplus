
#include "../standard.h"
#include "vga.h"

namespace basilisk {

driver::VGAWriter driver::VGAWriter::vga;

driver::VGAWriter::VGAWriter() {
	// clear screen.
	for (size li = 0; li < (kHeight * kWidth); li++) {
		buf[li] = (color << 8) | ' ';
	}
}

void driver::VGAWriter::Newline() {
	if (i != kHeight) {
		i = (i + 1) % kHeight;
	} else {
		memcpy(&buf[kWidth], buf, kWidth * (kHeight - 1));
	}
}

void driver::VGAWriter::Put(u8 c) {
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

bool driver::VGAWriter::Write(Buffer& buf) {
	for (auto i = buf.Iter(); !i.Done(); i.Next()) {
		Put(i.Get());
	}
	return true; // success
}

} // namespace basilisk
