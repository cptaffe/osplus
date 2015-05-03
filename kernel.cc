
// NOTE: this file contans a test entrypoint

#include "types.h"

extern "C" void GlobalEntryPoint() {

	// put character at location.
	((u16 *) 0xb8000)[0] = (15 << 8) | 'X';

	// hang forever
	for (;;) {}
}
