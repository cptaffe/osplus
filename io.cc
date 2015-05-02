
#include "io.h"

#include "writer.h"
#include "driver/vga.h"

void basilisk::IO::PutLine(const char *c) {
	using namespace basilisk;
	Writer *w = driver::VGAWriter::Instance();
	for (size i = 0; c[i] != '\0'; i++) {
		w->WriteByte(c[i]);
	}
	w->WriteByte('\n');
}
