
#include "startup.h"
#include "io.h"

namespace basilisk {

StartUpTask StartUpTask::start;

void StartUpTask::Run() {
	// Test new features here.
	IO::GetInstance().Put(
		"OS has successfully booted...\n"
		"Basilisk OS v0.0.1 (c) 2015 Connor Taffe. All rights reserved.\n"
	);
}
} // namespace basilisk
