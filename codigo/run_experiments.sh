#!/bin/bash

# Example: ./run_experiments.sh x y z
# Donde x es la cantidad de experimentos, y es el numero de lote, z es el quantum del scheduler
N="1"
while [ $N -lt $1 ];
do
    echo "Creating ej9_${N}.png experiment..."
    ./simusched Tareas/lote$2.tsk 1 1 0 SchedLottery $3 $RANDOM | ./graphsched.py > ../latex/Graficos/ej9_${N}.png
    N=$[ $N+1 ]
done
