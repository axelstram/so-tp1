#include "tasks.h"
#include <cstdlib>
#include <iostream>

using namespace std;


void TaskCPU(int pid, vector<int> params) 
{ 
	//params: n
	uso_CPU(pid, params[0]); // Uso el CPU n milisegundos.
}


void TaskIO(int pid, vector<int> params) 
{ 
	//params: ms_pid, ms_io,
	uso_CPU(pid, params[0]); // Uso el CPU ms_pid milisegundos.
	uso_IO(pid, params[1]); // Uso IO ms_io milisegundos.
}


void TaskAlterno(int pid, vector<int> params) 
{ 
	//params: ms_pid, ms_io, ms_pid, ...
	for (int i = 0; i < (int)params.size(); i++) {
		
		if (i % 2 == 0) 
			uso_CPU(pid, params[i]);
		else 
			uso_IO(pid, params[i]);

	}
}


void TaskConsola(int pid, vector<int> params)
{
	int cantLlamadasBloqueantes = params[0];
	int bmin = params[1];
	int bmax = params[2];

	srand(time(NULL));

	for (int n = 1; n <= cantLlamadasBloqueantes; n++) {
		int duracionLlamadaBloqueante = (rand() % (bmax-bmin)) + bmin;
		uso_IO(pid, duracionLlamadaBloqueante);
	}
}


void TaskBatch(int pid, vector<int> params)
{
	int totalCPU = params[0];
	int cantBloqueos = params[1];

	srand(time(NULL));

	while (totalCPU > 0) {

		while (cantBloqueos > 0) {
			int hayQueHacerUnBloqueo = rand() % 2;

			if (hayQueHacerUnBloqueo) 
				uso_IO(pid, 1); //Bloqueo 1 ciclo.
		 	else
				uso_CPU(pid, 1); //Sino, uso el CPU un ciclo.
			
			totalCPU--; 	//Tiempo de CPU utilizado en lanzar la llamada bloqueante o en usar el CPU.
			cantBloqueos--;
		}

		if (cantBloqueos == 0)
			uso_CPU(pid, 1);	//Si ya no hay mas bloqueos para hacer, el resto del tiempo uso el CPU.

		totalCPU--;
	}
}


void tasks_init(void) 
{
	/* Todos los tipos de tareas se deben registrar acá para poder ser usadas.
	 * El segundo parámetro indica la cantidad de parámetros que recibe la tarea
	 * como un vector de enteros, o -1 para una cantidad de parámetros variable. */
	register_task(TaskCPU, 1);
	register_task(TaskIO, 2);
	register_task(TaskAlterno, -1);
	register_task(TaskConsola, 3);
	register_task(TaskBatch, 2);
}
