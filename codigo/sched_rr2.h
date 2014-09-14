#ifndef __SCHED_RR2__
#define __SCHED_RR2__

#include <vector>
#include <queue>
#include "basesched.h"

class SchedRR2 : public SchedBase {
	public:
		SchedRR2(std::vector<int> argn);
        ~SchedRR2();
		virtual void load(int pid);
		virtual void unblock(int pid);
		virtual int tick(int cpu, const enum Motivo m);

	private:
		int next(int cpu);
		int cpu_taskload(int cpu);
		int cores;
		std::vector<int> quantum;
		std::vector<std::queue<int>> queues;
		std::vector<int> ticks;
		std::vector<int> blocked_tasks_qty;
};

#endif
