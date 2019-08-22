import sys
import os
import subprocess
from random import randint
from random import shuffle

import numpy as np

class par_de_equipos:
    equipo_1 = 0
    equipo_2 = 0

# parametros:
#	 num_de_equipos  densidad_matriz

f = open("competencia_generada.in", "w")
n_competidores = int(sys.argv[1])
# esto refiere al porcentaje de los posibles partidos que en realidad se dan
densidad_matriz = float(sys.argv[2])
# refiere cuantos pares de equipos no pueden jugar entre si
n_partidos_bloqueados =  (n_competidores-1.0) * (n_competidores-1.0) * 0.5  * (1.0-densidad_matriz)

partidos_totales = (n_competidores-1.0) * (n_competidores-1.0) * 0.5  * (densidad_matriz)


posibles_partidos = []
for x in xrange(n_competidores):
	for y in xrange(x+1,n_competidores):
		p = par_de_equipos()
		p.equipo_1 = x
		p.equipo_2 = y
		posibles_partidos.append(p)


shuffle(posibles_partidos)


while len(posibles_partidos) > partidos_totales:
	posibles_partidos.pop()
f.write(str(n_competidores) + " " + str(len(posibles_partidos)) +"\n")


for x in xrange(len(posibles_partidos)):
	equipo_1 = posibles_partidos[x].equipo_1
	equipo_2 = posibles_partidos[x].equipo_2

	if randint(0,2) == 1 :
		f.write("1 " + str(equipo_1+1) + " 1 " + str(equipo_2+1) + " 0\n")
	else :
		f.write("1 " + str(equipo_1+1) + " 0 " + str(equipo_2+1) + " 1\n")
f.close()