#include <vector>
#include <queue>
#include "sched_rr2.h"
#include "basesched.h"
#include <iostream>

using namespace std;

SchedRR2::SchedRR2(vector<int> argn) {
	cores = argn[1];
	ticks (cores, 0);
	blocked_tasks_qty (cores, 0);
	queues (cores, std::queue<int>);
	for (int core = 0; core < cores; core++)
		quantum[core] = argn[core+2];
}

SchedRR2::~SchedRR2() {

}


void SchedRR2::load(int pid) {
	// Tengo que cargar el proceso en la cpu con menos tareas
	int min = cpu_taskload(0);
	for (int i = 1; i < cores; i++)
		return ;
}

void SchedRR2::unblock(int pid) {
}

int SchedRR2::tick(int cpu, const enum Motivo m) {
  return IDLE_TASK;
}

int SchedRR2::next(int cpu) {
	return 0;
}

int SchedRR2::cpu_taskload(int cpu) {
	// Me fijo la carga actual de la cpu
	int amount = blocked_tasks_qty[cpu] + queues[0].size();
	return (current_pid(cpu) == IDLE_TASK) ? amount + 1 : amount;
}
