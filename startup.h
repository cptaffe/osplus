
#ifndef BOS_STARTUP_H_
#define BOS_STARTUP_H_

#include "task.h"

namespace basilisk {

// StartUp Singleton.
class StartUpTask : public Task::Runnable {
public:
	static StartUpTask& GetInstance() { return start; }

	// implement Task::Runnable
	virtual Task &GetTask() { return task; }

	// override Task::Runnable's Runnable interface
	// while Task::Scheduler::Switch / Task::Scheduler::Initiate
	// is still not working.
	virtual void Run();
private:
	StartUpTask() : task((void *) &test) {}

	static StartUpTask start;
	static void test() { GetInstance().Run(); }

	Task task;
};

} // namespace basilisk

#endif // BOS_STARTUP_H_
