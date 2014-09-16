#ifndef __SCHED_LOT__
#define __SCHED_LOT__

#include "basesched.h"
#include <map>
#include <list>
#include <utility>

class SchedLottery : public SchedBase {
  public:
    SchedLottery(std::vector<int> argn);
    ~SchedLottery();
    virtual void load(int pid);
    virtual void load(int pid, int deadline);
    virtual void unblock(int pid);
    virtual int tick(int cpu, const enum Motivo m);

    private:
		int loteria();
		void redistribuirTickets();
		int next_tick(int tareaActual);
		int next_blockexit(int tareaActual);
		// el valor de quantum por parametro
		int quantum;
		// la cantidad de ticks actuak
		int cantTicks;
		int semilla;
		std::list<std::pair<int,int> > tareasYTickets;
		
		//para saber si debe ser compensada en el unblock
		std::vector<double> aCompensar;
		//para saber si hubo tareas compensadas en el anterior ciclo
		bool compensadas;
		//Para saber si el proceso current_pid fue compensado en el tick que paso
		
};

#endif
