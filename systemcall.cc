
#include "systemcall.h"
#include "io.h"

namespace basilisk {

SystemCall SystemCall::syscall_;

void SystemCall::Invoke(u32 *args) {
	IO::GetInstance().Put("Handler!\n");
	if (args[0] == 5) {
		IO::GetInstance()
		.Put("got 0x").Put(args[0], 16).Put(";\n");
	}
}

} // namespace basilisk
