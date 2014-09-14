#include <vector>
#include <queue>
#include "sched_rr2.h"
#include "basesched.h"
#include <iostream>

using namespace std;

SchedRR2::SchedRR2(vector<int> argn) : cores(argn[1]), ticks (cores, 0), quantum(cores), blocked_tasks (cores, std::set<int>()), queues (cores, std::queue<int>()) {
	for (int core = 0; core < cores; core++)
		quantum[core] = argn[core+2];
}

SchedRR2::~SchedRR2() {

}


void SchedRR2::load(int pid) {
	// Tengo que cargar el proceso en la cpu con menos tareas
	int min = cpu_taskload(0), target_cpu = 0;
	for (int core = 1; core < cores; core++) {
		if (cpu_taskload(core) < min)
			target_cpu = core;
	}
	queues[target_cpu].push(pid);
}

void SchedRR2::unblock(int pid) {
	// Las tareas deben volver a su respectiva cola una vez desbloqueadas
	std::set<int>::iterator it;
	// Busco a que core pertenece el proceso actualmente bloqueado
	for (int core = 0; core < cores; core++) {
		it = blocked_tasks[core].find(pid);
		// si el elemento esta en las tareas bloqueadas de esta cpu...
		if (it != blocked_tasks[core].end()) {
			// lo saco y lo agrego en la cola de listos
			blocked_tasks[core].erase(it);
			queues[core].push(pid);
		}

	}
}

int SchedRR2::tick(int cpu, const enum Motivo m) {
	if (m == TICK)
		return next(cpu);

	if (m == EXIT || m == BLOCK) {
		ticks[cpu] = 0;
		if (m == BLOCK)
			blocked_tasks[cpu].insert(current_pid(cpu));
		return SiguienteTarea(cpu);
	}

	return 0;
}

int SchedRR2::next(int cpu) {
	int current_task = current_pid(cpu);

	//Me salteo la tarea idle al inicio de la simulacion y devuelvo la primera tarea real a ejecutar.
	if (current_task == IDLE_TASK && !queues[cpu].empty())
		return SiguienteTarea(cpu);

	ticks[cpu]++;
	// Si se me termina el quantum
	if (ticks[cpu] == quantum[cpu]) {
		ticks[cpu] = 0;
		queues[cpu].push(current_task);

		return SiguienteTarea(cpu);
	}

	return current_task;
}

int SchedRR2::SiguienteTarea(int cpu) {
	if (queues[cpu].empty()){
		return IDLE_TASK;
	} else {
		int next_task = queues[cpu].front();
		queues[cpu].pop();

		return next_task;
	}
}

int SchedRR2::cpu_taskload(int cpu) {
	// Me fijo la carga actual de la cpu
	int tasks_qty = blocked_tasks[cpu].size() + queues[cpu].size();
	// Si el cpu no esta IDLE, le sumo uno ya que esta corriendo una tarea
	return (current_pid(cpu) != IDLE_TASK) ? tasks_qty + 1 : tasks_qty;
}
