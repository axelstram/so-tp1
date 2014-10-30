#include "sched_lottery_base.h"
#include <cstdlib>
#include <iostream>
using namespace std;

SchedLotteryBase::SchedLotteryBase(vector<int> argn) : quantum(argn[1]), semilla(argn[2]), cantTicks(0), cantTickets(0)
{
	std::srand(semilla); 
}

SchedLotteryBase::~SchedLotteryBase() 
{

}

void SchedLotteryBase::load(int pid) 
{
  	
  	tareasYTickets.insert(tareasYTickets.begin(),std::pair<int,int>(pid, 10));
  	cantTickets += 10;

}

void SchedLotteryBase::load(int pid,int deadline) 
{
	tareasYTickets.insert(tareasYTickets.begin(),std::pair<int,int>(pid, 10));
  	cantTickets += 10;


}


void SchedLotteryBase::unblock(int pid)
{
	tareasYTickets.insert(tareasYTickets.begin(),std::pair<int,int>(pid, 10));

  	cantTickets += 10;
	
}

int SchedLotteryBase::tick(int cpu, const enum Motivo motivo)
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
			cantTicks = 0;

			std::list<std::pair<int, int> >::iterator it = tareasYTickets.begin();

			while(it != tareasYTickets.end() && it->first != tareaActual)
			{
				it++;
			}

			cantTickets-=(it->second);

			tareasYTickets.erase(it);

			if(tareasYTickets.empty())
			{
				return IDLE_TASK;
			}
			
			return loteria();
			
		}
}
	
int SchedLotteryBase::loteria()
{
	
	int ticketGanador = rand() % cantTickets;

	cout << "hay " << tareasYTickets.size() << "tareas y gano el ticket "<< ticketGanador << endl;

	int duenioTicketGanador;

		std::list<std::pair<int,int> >::iterator it = tareasYTickets.begin();

		int sumaParcial = 0;
/*
		//caso base = 0
		if(ticketGanador == 0)
		 duenioTicketGanador = tareasYTickets.begin()->first;
*/
		bool hayGanador;

  		while (!hayGanador)
  		{
  			int primerTicket = sumaParcial;
  			int ultimoTicket = primerTicket + (it->second) -1;

  			//HACER LO DE PRIMER TICKET Y ULTIMO TICKET!!
  			if(primerTicket <= ticketGanador && ticketGanador <= ultimoTicket)
  			{
  				duenioTicketGanador = it->first;
  				hayGanador = true;
  				cout << "gano la tarea " << duenioTicketGanador << " con rango [" << primerTicket << ".." << ultimoTicket << "]" << endl;		
  				
  			}
  			sumaParcial += it->second;
  			++it;
  		}

  		
  		
  		
  		return duenioTicketGanador;

  		//cout << "entonces gano la tarea " << duenioTicketGanador << endl;
}



