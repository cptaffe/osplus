
#ifndef BOS_TASK_H_
#define BOS_TASK_H_

#include "types.h"

namespace basilisk {

class Scheduler {
public:
	static Scheduler& GetInstance() { return sched_; }

	class Task {
	public:
		Task(int id, void *call = nullptr);
		void Switch(Task *task);
	private:
		void Initialize(void *call);
		u32 stackp;
		u32 task_id;
		u32 stack[0x1000]; // 4kb stack.
	};

	bool Put(Task *task);
	Task *Get();
	void Yield(); // reschedule
	void Sleep(); // don't reschedule
private:
	Scheduler();
	static Scheduler sched_;

	Task *tasks[10] = {0};
	Task *current;
};

} // namespace basilisk

#endif // BOS_TASK_H_
