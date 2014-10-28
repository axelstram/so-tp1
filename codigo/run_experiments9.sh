#!/bin/bash

# Example: ./run_experiments.sh x y z
# Donde x es la cantidad de experimentos, y es el numero de lote, z es el quantum del scheduler
N="1"

 TicksTask0=0
 TicksTask1=0
 TicksTask2=0
 TicksTask3=0
 TicksTask4=0

while [ $N -le $1 ];
do
    echo "Creating experiment ${N}..."
    R=$RANDOM
    (./simusched Tareas/lote$2.tsk 1 0 0 SchedLottery $3 $R) > temp.txt

    


	while IFS= read -r line;
	do
   		fields=($(printf "%s" "$line"|cut -d' ' --output-delimiter=' ' -f1-))

    	if [ "${fields[0]}" == "CPU" ]
  		then
  			
  			if [ "${fields[2]}" == "0" ]
			then 
				((TicksTask0++))

			elif [ "${fields[2]}" == "1" ]
			then
				((TicksTask1++)) 		

			elif [ "${fields[2]}" == "2" ]
			then 
				((TicksTask2++))

			elif [ "${fields[2]}" == "3" ]
			then 
					((TicksTask3++))	
			

			elif [ "${fields[2]}" == "4" ]
			then 
					((TicksTask4++))	
			fi
			
			if [ "${fields[1]}" == "100" ]
			then
				break
			fi
		fi
    	
   	
	done < temp.txt

	
    
    N=$[ $N+1 ]
done

echo "El promedio de la tarea 0 es:" $(($TicksTask0 / $1))
echo "El promedio de la tarea 1 es:" $(($TicksTask1 / $1))
echo "El promedio de la tarea 2 es:" $(($TicksTask2 / $1))
echo "El promedio de la tarea 3 es:" $(($TicksTask3 / $1))
echo "El promedio de la tarea 4 es:" $(($TicksTask4 / $1))