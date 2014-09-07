#include <vector>
#include <queue>
#include "sched_rr.h"
#include "basesched.h"
#include <iostream>

using namespace std;


SchedRR::SchedRR(vector<int> argn) 
{
	// Round robin recibe la cantidad de cores y sus cpu_quantum por parámetro
	int cantCores = argn[0];
	vector<int> quantum(cantCores);

	//Cargo los quantums
	for (unsigned int nroCore = 0; nroCore < cantCores; nroCore++)
		quantum[nroCore] = argn[nroCore+1];

	
}


SchedRR::~SchedRR() 
{

}


void SchedRR::load(int pid) 
{

}


void SchedRR::unblock(int pid) 
{

}


int SchedRR::tick(int cpu, const enum Motivo m) 
{
	return 0;
}

