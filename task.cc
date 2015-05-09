
#include "task.h"

namespace basilisk {

Scheduler Scheduler::sched_;

namespace {

// the current task (implicitly spawned on startup).
Scheduler::Task task(0);

} // namespace

// creation of a new task for running.
Scheduler::Task::Task(int id, void *func) :
	task_id(id) {
	// set stackp
	stackp = (u32) stack;
	Initialize(func);
}

Scheduler::Scheduler() {
	// set up current task.
	current = &task;
}

bool Scheduler::Put(Task *task) {
	// insert if possible.
	for (uint i = 0; i < (sizeof(tasks) / sizeof(Task *)); i++) {
		if (tasks[i] == nullptr) {
			tasks[i] = task;
			return true;
		}
	}
	return false;
}

Scheduler::Task *Scheduler::Get() {
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
void Scheduler::Yield() {
	Task *running = current;
	Task *next = Get();
	if (next != nullptr) {
		Put(running);
		current = next;
		running->Switch(next);
	}
}

// switches to another task.
void Scheduler::Sleep() {
	Task *running = current;
	Task *next = Get();
	if (next != nullptr) {
		current = next;
		running->Switch(next);
	}
}

} // namespace basilisk
