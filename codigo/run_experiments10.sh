#!/bin/bash

# Example: ./run_experiments.sh x y z
# Donde x es la cantidad de experimentos, y es el numero de lote, z es el quantum del scheduler
N="1"

 TicksTask0=0
 TicksTask1=0
 TicksTask2=0
 TicksTask3=0

 TotalTicksTask0=0
 TotalTicksTask1=0
 TotalTicksTask2=0
 TotalTicksTask3=0

> result.txt

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
			fi

			if [ "${fields[1]}" == "50" ]
			then
				break
			fi
		fi
    	
   	
	done < temp.txt

	
    
    ((TotalTicksTask0+=TicksTask0))
 	((TotalTicksTask1+=TicksTask1))
 	((TotalTicksTask2+=TicksTask2))
	((TotalTicksTask3+=TicksTask3))

	PromedioTask0=$(awk "BEGIN {printf \"%.2f\",${TotalTicksTask0}/${N}}")
	PromedioTask1=$(awk "BEGIN {printf \"%.2f\",${TotalTicksTask1}/${N}}")
	PromedioTask2=$(awk "BEGIN {printf \"%.2f\",${TotalTicksTask2}/${N}}")
	PromedioTask3=$(awk "BEGIN {printf \"%.2f\",${TotalTicksTask3}/${N}}")

	echo "$N $PromedioTask0 $PromedioTask1 $PromedioTask2 $PromedioTask3" >> result.txt
	#echo "$N $TicksTask0 $TicksTask1 $TicksTask2 $TicksTask3 $TicksTask4" >> result.txt


	TicksTask0=0
 	TicksTask1=0
 	TicksTask2=0
 	TicksTask3=0

    N=$[ $N+1 ]
done

