import sys
import random

import numpy as np
T = int(sys.argv[1])
N = int(sys.argv[2])

f = open("../competencia_generada.in","w")

habilidades = []
for i in range(T):
    habilidades.append(random.random())

f.write(str(T)+" "+str(N)+"\n")

for i in range(N):
    equipo_1,equipo_2 = 0,0
    while(equipo_1 == equipo_2):
        equipo_1 = random.randint(1,T)
        equipo_2 = random.randint(1,T)

    if random.random() > habilidades[equipo_1-1]/(habilidades[equipo_1-1]+habilidades[equipo_2-1]):
        f.write("1 " + str(equipo_1) + " 1 " + str(equipo_2) + " 0\n")
    else:
        f.write("1 " + str(equipo_1) + " 0 " + str(equipo_2) + " 1\n")

f.close()
