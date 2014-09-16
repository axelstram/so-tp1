#include "sched_lottery.h"
#include <cstdlib>

using namespace std;

SchedLottery::SchedLottery(vector<int> argn) : quantum(argn[1]), semilla(argn[2]), cantTicks(0), cantTickets(100)
{
	std::srand(semilla); 
}

SchedLottery::~SchedLottery() 
{

}

void SchedLottery::load(int pid) 
{
  	
  	tareasYTickets.insert(tareasYTickets.begin(),std::pair<int,int>(pid, 0));

  	//Actualizamos la cantidad de tickets de todos

  	redistribuirTickets(0);
}

void SchedLottery::load(int pid,int deadline) 
{
	tareasYTickets.insert(tareasYTickets.begin(),std::pair<int,int>(pid, 0));

  	//Actualizamos la cantidad de tickets de todos

  	redistribuirTickets(0);
}

void SchedLottery::unblock(int pid) 
{
	tareasYTickets.insert(tareasYTickets.begin(),std::pair<int,int>(pid, 0));

	//marco que ya se desbloqueo!

	std::map<int,std::pair<int,bool> >::iterator it = aCompensar.find(pid);

	if(it != aCompensar.end())
	{
		(it->second).second = true;
	}

	redistribuirTickets(0);
}

int SchedLottery::tick(int cpu, const enum Motivo motivo) 
{

	int tareaActual = current_pid(cpu);

		if (motivo == TICK)
		{
			//Si estoy en la IDLE me la salteo
			if (tareaActual == IDLE_TASK && !tareasYTickets.empty()) 
			{
				return loteria();
			}

			cantTicks++;
			
			if (cantTicks == quantum)
			{//si se cumple el quantum se resetean la cuenta de ticks y elijo otra tarea	
				cantTicks = 0;
				return loteria();
			}
			// si no me pase del quantum sigue la actual
			return tareaActual;
		}
		else if (motivo == EXIT || motivo == BLOCK)
		{
			if(motivo == BLOCK && cantTicks < quantum)
				compensar(tareaActual, cantTicks);

			cantTicks = 0;

			std::list<std::pair<int, int> >::iterator it = tareasYTickets.begin();

			while(it != tareasYTickets.end() && it->first != tareaActual)
			{
				it++;
			}

			tareasYTickets.erase(it);

			if(tareasYTickets.empty())
			{
				return IDLE_TASK;
			}

			redistribuirTickets(1);

			return loteria();
			
		}
}
	

int SchedLottery::loteria()
{
	
	int ticketGanador = rand() % cantTickets;

	int duenioTicketGanador;

		std::list<std::pair<int,int> >::iterator it = tareasYTickets.begin();

		int sumaParcial = 0;

		//caso base = 0
		if(ticketGanador == 0)
		 return tareasYTickets.begin()->first;

  		while (it!=tareasYTickets.end())
  		{

  			if(ticketGanador >= sumaParcial && ticketGanador <= sumaParcial + it->second)
  			{
  				duenioTicketGanador = it->first;
  				 break;		
  				
  			}
  			sumaParcial += it->second;

  			++it;
  		}
  		redistribuirTickets(1);
  		return duenioTicketGanador;
}


// FUNCION REDISTRIBUIR TICKETS!

void SchedLottery::redistribuirTickets(int modo)
{
	//Primero redistribuimos equitativamente entre todas las tareas

	cantTickets = 100;

	int cantTareas = tareasYTickets.size();

  	int ticketsCadaUno = cantTickets / cantTareas;

  	int resto = cantTickets % cantTareas; // Al resto lo repartimos entre todas

  	
  	std::list<std::pair<int,int> >::iterator it =tareasYTickets.begin();

  	for (; it!=tareasYTickets.end(); ++it)
  	{
  		it->second =ticketsCadaUno;

  		//reparto el resto, un ticket para cada uno hasta que se termine

  		if(resto>0)
  		{
  			it->second++;
  			resto--;
  		}

  	}
  	// si fui llamado desde un tick, elimino las tareas compensadas y termino
  	if(modo == 1)
  	{
  		aCompensar.clear();
  	}

  	if(modo == 0)
  	{// si fui llamado desde un block o desde un tick, tengo que agregarle las compensaciones a las tareas
  	//  que habian sido compensadas con la nueva distribucion de tickets

  		cantTickets = 0;

  		std::list<std::pair<int,int> >::iterator it2 =tareasYTickets.begin();

  		for(; it2!=tareasYTickets.end(); ++it2)
  		{
  			std::map<int,std::pair<int,bool> >::iterator itDic = aCompensar.find(it2->first);

  			if(itDic != aCompensar.end())
  			{
  				if((itDic->second).second)
  				{
  					it2->second *= ((itDic->second).first);
  				}
  			}

  			cantTickets += it2->second;
  		}
  	}

}

void SchedLottery::compensar(int tarea, int ticks)
{
	int ticksConsumidos = ticks;

	if(ticksConsumidos == 0)
	{
		ticksConsumidos = 1;
	}	

	double fraccionQuantum = (double) ticksConsumidos / quantum;

	int multiplicador = (int) 1 / fraccionQuantum;

	aCompensar.insert(aCompensar.begin(), std::make_pair(tarea, std::make_pair(multiplicador, false)));

}