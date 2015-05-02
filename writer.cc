
#include "writer.h"

void basilisk::Writer::Write(const char *msg, size len) {
	for (size i = 0; i < len; i++) {
		WriteByte(msg[i]);
	}
}
