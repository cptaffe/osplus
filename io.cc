
#include "io.h"
#include "driver/vga.h"
#include "writeable.h"

namespace basilisk {

IO IO::io;

IO& IO::Put(Buffer buf) {
	driver::VGAScreen::GetInstance().Write(buf);
	return *this;
}

IO& IO::Put(u32 number, int base) {
	char msg[32]; // base 2 is 32, lowest base possible.
	int index = 0;
	while (number != 0) {
		int n = number % base;
		if (n < 10) {
			msg[index++] = n + '0';
		} else {
			msg[index++] = n + 'a';
		}
		number /= base;
	}

	int i = 0;
	int j = index - 1;

	while (i != j && i != (j + 1)) {
		char c = msg[j];
		msg[j] = msg[i];
		msg[i] = c;
		i++;
		j--;
	}

	if (index == 0) {
		msg[index++] = '0';
	}

	msg[index] = '\0'; // null terminate
	return Put((const char *) msg);
}

} // namespace basilisk
