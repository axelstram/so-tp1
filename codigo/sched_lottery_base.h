#ifndef __SCHED_LOT__BASE_
#define __SCHED_LOT__BASE_

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
		
		// el valor de quantum por parametro
		int quantum;
		// la cantidad de ticks actuak
		int cantTicks;
		int semilla;
		std::list<std::pair<int,int> > tareasYTickets;
				
		
};

#endif
