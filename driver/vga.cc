
#include "../standard.h"
#include "vga.h"

namespace basilisk {

driver::VGAScreen driver::VGAScreen::vga;

driver::VGAScreen::VGAScreen() : color(7, 0) {
	// clear text and reset color
	Paint();
	Clear();
}

void driver::VGAScreen::Newline() {
	if (i < (kHeight - 1)) {
		i++;
	} else {
		memcpy(buf, &buf[kWidth], kWidth * (kHeight - 1) * sizeof(u16));
		for (uint li = 0; li < kWidth; li++) {
			buf[kWidth * (kHeight - 1) + li] = (color.color << 8) | ' ';
		}
	}
}

void driver::VGAScreen::Put(u8 c) {
	switch (c) {
	case '\n':
		Newline();
		// fallthrough
	case '\r':
		j = 0;
		break;
	default:
		buf[(i * kWidth) + j] = (color.color << 8) | c;
		j = (j + 1) % kWidth;
		if (j == 0) {
			// at end of line.
			Newline();
		}
	}
}

bool driver::VGAScreen::Write(const Buffer& buf) {
	for (auto i = buf.Iter(); !i.Done(); i.Next()) {
		Put(i.Get());
	}
	return true; // success
}

void driver::VGAScreen::Clear() {
	for (size li = 0; li < (kHeight * kWidth); li++) {
		buf[li] = (0xff00 & buf[li]) | ' ';
	}
	i = j = 0; // reset
}

void driver::VGAScreen::Paint() {
	// repaint screen with selected color
	for (size li = 0; li < (kHeight * kWidth); li++) {
		// bitmask to remove color.
		buf[li] = (color.color << 8) | (0x00ff & buf[li]);
	}
}

const Screen::Color &driver::VGAScreen::GetColor() const {
	return color;
}

void driver::VGAScreen::SetColor(const Screen::Color &col) {
	color = col;
}

} // namespace basilisk
