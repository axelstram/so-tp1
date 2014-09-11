#include <vector>
#include <queue>
#include "sched_rr.h"
#include "basesched.h"
#include <iostream>

using namespace std;


SchedRR::SchedRR(vector<int> argn) : cantCores(argn[1]), quantum(cantCores), cantTicks(cantCores, 0)
{	
	// Round robin recibe la cantidad de cores y sus cpu_quantum por parámetro
	//argn[1] = #cant cores
	//argn[2...] = quantums
	for (int nroCore = 0; nroCore < cantCores; nroCore++)
		quantum[nroCore] = argn[nroCore+2];
}


SchedRR::~SchedRR() 
{

}


void SchedRR::load(int pid) 
{	
	colaDeTareas.push(pid);
}


void SchedRR::unblock(int pid) 
{
	colaDeTareas.push(pid);
}


int SchedRR::tick(int cpu, const enum Motivo motivo) 
{	
	if (motivo == TICK)
		return next(cpu);

	if (motivo == EXIT || motivo == BLOCK) {

		if (colaDeTareas.empty()) {
			return IDLE_TASK;
		} else {
			int sigTarea = colaDeTareas.front(); 
			colaDeTareas.pop();

			return sigTarea;
		}

	}

	return 0;
}


int SchedRR::next(int cpu)
{
	int tareaActual = current_pid(cpu);
			
	//Me salteo la tarea idle al inicio de la simulacion y devuelvo la primera tarea real a ejecutar.
	if (tareaActual == IDLE_TASK && !colaDeTareas.empty()) {
		int sigTarea = colaDeTareas.front(); 
		colaDeTareas.pop();

		return sigTarea;
	}

	cantTicks[cpu]++;

	if (cantTicks[cpu] > quantum[cpu]) {	
		cantTicks[cpu] = 0;
		//Vuelvo a poner la tarea al final de la cola, ya que la misma no termino de ejecutarse
		if (tareaActual != IDLE_TASK)
			colaDeTareas.push(tareaActual);
		else
			return IDLE_TASK;

		int sigTarea = colaDeTareas.front(); 
		colaDeTareas.pop();

		return sigTarea;
	}

	return tareaActual;
}