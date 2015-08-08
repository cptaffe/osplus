
#include "task.h"
#include "io.h"

namespace basilisk {

Task::Scheduler Task::Scheduler::sched_;

namespace {

// the current task (implicitly spawned on startup).
Task task(0);

} // namespace

// creation of a new task for running.
Task::Task(void *func) :
	stackp((u32) stack[(sizeof(stack) / sizeof(u32)) - 1]) {
	Initialize(func);
}

Task::Scheduler::Scheduler() {
	// set up current task.
	current = &task;
}

void Task::Run() {
	// Running a Task adds the task to the scheduler
	// and runs the scheduler, running all scheduled
	// tasks (theoretically).
	IO::GetInstance().Put("Running Run\n");
	Scheduler::GetInstance().Put(this);
	Scheduler::GetInstance().Yield();
	IO::GetInstance().Put("Returned from Yield\n");
}

bool Task::Scheduler::Put(Task *task) {
	// insert if possible.
	for (uint i = 0; i < (sizeof(tasks) / sizeof(Task *)); i++) {
		if (tasks[i] == nullptr) {
			tasks[i] = task;
			return true;
		}
	}
	return false;
}

Task *Task::Scheduler::Get() {
	// insert if possible.
	for (uint i = 0; i < (sizeof(tasks) / sizeof(Task *)); i++) {
		if (tasks[i] != nullptr) {
			Task *task = tasks[i];
			tasks[i] = nullptr;
			return task;
		}
	}
	return nullptr;
}

// switches to another task.
void Task::Scheduler::Yield() {
	Task *running = current;
	Task *next = Get();
	if (next != nullptr) {
		Put(running);
		current = next;
		running->Switch(next);
	}
}

// switches to another task.
void Task::Scheduler::Sleep() {
	Task *running = current;
	Task *next = Get();
	if (next != nullptr) {
		current = next;
		running->Switch(next);
	}
}

} // namespace basilisk
