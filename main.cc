
#include "kernel.h"
#include "startup.h"
#include "types.h"

// This file is called 'main' because it contains the entry
// point of the OS, which I have named 'main'.

namespace basilisk {

void bootstrap() {
	Permissions p(true);
	Kernel::GetInstance().Do(StartUpTask::GetInstance(), p);
}

extern "C" __attribute__((noreturn)) void main() {
	Kernel::Start(); // kernel startup.
	bootstrap();
	Kernel::Stop(); // stop execution.
}

} // namespace basilisk
