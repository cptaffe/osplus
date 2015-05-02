
#include "io.h"

#include "writer.h"
#include "driver/vga.h"

void os::IO::PutLine(const char *c) {
	os::Writer *w = os::driver::VGAWriter::Instance();
	for (size i = 0; c[i] != '\0'; i++) {
		w->WriteByte(c[i]);
	}
	w->WriteByte('\n');
}
