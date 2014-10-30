#include "tasks.h"
#include <cstdlib>
#include <iostream>

using namespace std;

void PrecalcularLlamadasBloqueantes(vector<bool>& hayLlamadasBloqueantes, int cantBloqueos);

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
	vector<bool> hayLlamadaBloqueante(totalCPU, false);

	srand(time(NULL));

	PrecalcularLlamadasBloqueantes(hayLlamadaBloqueante, cantBloqueos);

	for (int cicloCPU = 0; cicloCPU < totalCPU; cicloCPU++) {
		int hayQueHacerUnBloqueo = hayLlamadaBloqueante[cicloCPU];

		if (hayQueHacerUnBloqueo)
			uso_IO(pid, 1);
		else
			uso_CPU(pid, 1);
	}
}


void PrecalcularLlamadasBloqueantes(vector<bool>& hayLlamadaBloqueante, int cantBloqueos)
{	
	int totalCPU = hayLlamadaBloqueante.size();
	vector<int> momentosLlamadasBloqueantes;

	for (int i = 0; i < totalCPU; i++)
		momentosLlamadasBloqueantes.push_back(i);

	while (cantBloqueos > 0) {
		int i = rand() % totalCPU;
		int instanteRandom = momentosLlamadasBloqueantes[i];

		hayLlamadaBloqueante[instanteRandom] = true;
		momentosLlamadasBloqueantes.erase(momentosLlamadasBloqueantes.begin() + i);

		cantBloqueos--;
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
