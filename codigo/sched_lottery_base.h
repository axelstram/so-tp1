#ifndef __SCHED_LOTTERY_BASE__
#define __SCHED_LOTTERY_BASE__

#include "basesched.h"
#include <map>
#include <list>
#include <utility>

class SchedLotteryBase : public SchedBase {
  public:
    SchedLotteryBase(std::vector<int> argn);
    ~SchedLotteryBase();
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
