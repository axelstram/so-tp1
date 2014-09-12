#ifndef __SCHED_LOT__
#define __SCHED_LOT__

#include "basesched.h"
#include <map>

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
		// el valor de quantum por parametro
		int quantum;
		// la cantidad de ticks actuak
		int cantTicks;
		int semilla;
		std::map<int, int> tareasYTickets;
		bool compensatorio;
		/* Para cambiar en el constructor:
		 0 = modo basico
		 1 = modo basico + compensation tickets
		*/
		bool hayCompensado;
		//Para saber si el proceso current_pid fue compensado en el tick que paso
		std::map<int, bool> bloqueadasTerminadas;
		//Para saber cuales tareas fueron bloqueadas o ya terminaron (1 == ready, 0 == block o exit)
};

#endif
