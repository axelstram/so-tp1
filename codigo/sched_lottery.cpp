#include "sched_lottery.h"
#include <cstdlib>

using namespace std;

SchedLottery::SchedLottery(vector<int> argn) : semilla(argn[1]), quantum(argn[2]) 
{
	compensatorio = 0;
}

SchedLottery::~SchedLottery() 
{

}

void SchedLottery::load(int pid) 
{
  	// Como llega una nueva tarea al scheduler, se debe recalcular la cantidad de tickets de todas las tareas
  	// para mantener equitativa la probabilidad. 

  	int cantTareas = tareasYTickets.size() + 1;

  	// Ahora dividimos los 100 tickets por la cantidad de Tareas

  	int ticketsCadaUno = 100 / cantTareas;

  	int resto = 100 % cantTareas; // Al resto lo repartimos entre todas

  	//metemos el nuevo pid

  	tareasYTickets.insert(std::pair<int,int>(pid, ticketsCadaUno));

  	bloqueadasTerminadas.insert(std::pair<int,bool>(pid, 1));

  	//Actualizamos la cantidad de tickets de todos

  	std::map<int,int>::iterator it;

  	for (it=tareasYTickets.begin(); it!=tareasYTickets.end(); ++it)
  	{
  		it->second =ticketsCadaUno;

  		//reparto el resto, un ticket para cada uno hasta que se termine

  		if(resto>0)
  		{
  			it->second++;
  			resto--;
  		}

  	}

}

void SchedLottery::load(int pid,int deadline) 
{
	tareasYTickets.insert(std::pair<int,int>(pid, 1));
}

void SchedLottery::unblock(int pid) 
{
	std::map<int,bool>::iterator it = bloqueadasTerminadas.find(pid);

	it->second = 1;

}

int SchedLottery::tick(int cpu, const enum Motivo motivo) 
{

	if(compensatorio)
	{//modo compensation tickets
		return 0;	
	}
	else
	{// modo basico


		if (motivo == TICK)
		{
			int tareaActual = current_pid(cpu);
			//Si estoy en la IDLE me la salteo
			if (tareaActual == IDLE_TASK && !tareasYTickets.empty()) 
				return loteria();

			cantTicks++;
			
			if (cantTicks == quantum)
			{//si me pase del quantum se resetean la cuenta de ticks y elijo otra tarea	
				cantTicks = 0;
				
				return loteria();
			}
			// si no me pase del quantum sigue la actual
			return tareaActual;
		}
		else if (motivo == EXIT || motivo == BLOCK)
		{
			int tareaActual = current_pid(cpu);
			cantTicks++;

			//Bloqueo o termino la tarea

			std::map<int,bool>::iterator it = bloqueadasTerminadas.find(tareaActual);

			it->second = 0;
			
			if(tareasYTickets.empty())
			{//si se acabaron las tareas
				return IDLE_TASK;
			}
			else
			{//si no eljio otra tarea
				return loteria();	
			}

		}
	
	}
	
}
	


int SchedLottery::loteria()
{
	std::srand(semilla); 

	int ticketGanador = rand() % 100;

	bool estaDisponible;

	do
	{
		int duenioTicketGanador;

		std::map<int,int>::iterator it;

		int sumaParcial = 0;

  		while (it!=tareasYTickets.end() && (sumaParcial < ticketGanador))
  		{
  			sumaParcial += it-> second;

  			if(ticketGanador <= sumaParcial)
  			{
  				duenioTicketGanador = it->first;
  				return duenioTicketGanador;
  			}

  			++it;
  		}


  	estaDisponible = (bloqueadasTerminadas.find(duenioTicketGanador))->second;

	}while(!estaDisponible);
}
