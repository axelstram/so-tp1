./simusched ./Tareas/lote3.tsk 1 1 2 SchedRR 1 2 | python graphsched.py > ej7_1core_q2.png &
./simusched ./Tareas/lote3.tsk 1 1 2 SchedRR 1 3 | python graphsched.py > ej7_1core_q3.png &
./simusched ./Tareas/lote3.tsk 1 1 2 SchedRR 1 4 | python graphsched.py > ej7_1core_q4.png &
./simusched ./Tareas/lote3.tsk 2 1 2 SchedRR 2 2 2 | python graphsched.py > ej7_2core_q2.png &
./simusched ./Tareas/lote3.tsk 2 1 2 SchedRR 2 3 3 | python graphsched.py > ej7_2core_q3.png &
./simusched ./Tareas/lote3.tsk 2 1 2 SchedRR 2 4 4 | python graphsched.py > ej7_2core_q4.png &
./simusched ./Tareas/lote3.tsk 3 1 2 SchedRR 3 2 2 2 | python graphsched.py > ej7_3core_q2.png &
./simusched ./Tareas/lote3.tsk 3 1 2 SchedRR 3 3 3 3 | python graphsched.py > ej7_3core_q3.png &
./simusched ./Tareas/lote3.tsk 3 1 2 SchedRR 3 4 4 4 | python graphsched.py > ej7_3core_q4.png