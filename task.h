
#ifndef BOS_TASK_H_
#define BOS_TASK_H_

#include "types.h"
#include "runnable.h"

namespace basilisk {

class Task : public Runnable {
public:
	Task(void *call = nullptr);

	// Scheduleable classes can be scheduled
	// via a Task returned by GetTask.
	class Runnable : public basilisk::Runnable {
	public:
		virtual ~Runnable() {}
		void Run() { GetTask().Run(); }
		virtual Task &GetTask() = 0;
	};

	virtual void Run();
private:
	void Switch(Task *task);
	void Initialize(void *call);

	// Singleton Task Scheduler.
	class Scheduler {
	public:
		static Scheduler& GetInstance() { return sched_; }

		void Yield(); // reschedule
		void Sleep(); // don't reschedule

		bool Put(Task *task);
	private:
		Scheduler();
		static Scheduler sched_;

		Task *Get();

		Task *tasks[10] = {0};
		Task *current;
	};

	u32 stackp;
	u32 stack[0x1000]; // 4kb stack.
} __attribute__((packed));

} // namespace basilisk

#endif // BOS_TASK_H_
