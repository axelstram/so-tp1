import sys
import random
import os
import time

"""Primer parametro: cantidad de experimentos
   Segundo parametro: lote (numero de lote del archivo)
   Tercer parametro: quantum
"""

n = sys.argv[1]
lote = sys.argv[2]
quantum = sys.argv[3]

for x in range(1, int(n)):
    rand = random.randint(1, 32000)
    print "Executing SchedLotteryBase on lote%s with seed: %s" % (lote, rand)
    os.system('./simusched Tareas/lote%s.tsk 1 1 0 SchedLotteryBase %s %s | ./graphsched.py > ../latex/Graficos/ej9_%s_base.png' % (lote, quantum, rand, x))
    time.sleep(1)
    print "Executing SchedLottery on lote%s with seed: %s" % (lote, rand)
    os.system('./simusched Tareas/lote%s.tsk 1 1 0 SchedLottery %s %s | ./graphsched.py > ../latex/Graficos/ej9_%s.png' % (lote, quantum, rand, x))
    
print "End"
