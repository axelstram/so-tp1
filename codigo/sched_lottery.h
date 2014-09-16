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
		int redistribuirTickets();
		void compensar(int tarea, int ticks);
		
		// el valor de quantum por parametro
		int quantum;
		// la cantidad de ticks actuak
		int cantTicks;
		int semilla;
		int cantTickets;
		std::list<std::pair<int,int> > tareasYTickets;

		//diccionario que indica que procesos bloqueados deberan ser compenados cuando se desbloqueen y el multiplicador

		std::map<int,int> aCompensar;
		
		//variable bool que indica, para cada tick, si una tarea fue compensada y se le debe quitar la compensacion

		bool compensada;
		
};

#endif
