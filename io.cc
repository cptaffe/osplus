
#include "io.h"

#include "terminal.h"
#include "driver/vga.h"

void os::IO::PutLine(const char *c) {
	os::Terminal *term = os::driver::VGA::Instance();
	for (size i = 0; c[i] != '\0'; i++) {
		term->Put(c[i]);
	}
}
