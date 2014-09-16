#!/bin/bash

# Example: ./run_experiments.sh x y z
# Donde x es la cantidad de experimentos, y es el numero de lote, z es el quantum del scheduler
N="1"
while [ $N -lt $1 ];
do
    echo "Creating experiment ${N}..."
    R=$RANDOM
    ./simusched Tareas/lote$2.tsk 1 1 0 SchedLotteryBase $3 $R | ./graphsched.py > ../latex/Graficos/ej9_${N}_base.png
    ./simusched Tareas/lote$2.tsk 1 1 0 SchedLottery $3 $R | ./graphsched.py > ../latex/Graficos/ej9_${N}.png
    N=$[ $N+1 ]
done
