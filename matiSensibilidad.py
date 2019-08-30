#Tiene que tomar un archivo de los rankings desordenado,
#Y tiene que devolver en otro archivo, la lista de los numeros de los equipos de mejor a peor.

import sys
import os
import subprocess
from random import randint
from random import shuffle

import numpy as np



archivo = str(sys.argv[1])
f = open(archivo, "r")
rankings = []

#genera el vector de rankings asociado al archivo
for line in f:
    palabras = line.split()
    ranking = float(palabras[0])
    rankings.append(ranking)

#print(rankings)

f = open("matiSensibilidad.txt", "w")


#f.write("This is line %d\r\n" % (i+1))

#aca se van a guardar los equipos por orden
equiposOrdenados = []

#aca tengo la lista de rankings desordenada
copia = rankings.copy()

#aca tengo la lista de rankings orddenada
rankings.sort(reverse=1)


for i in range(len(rankings)):
    for j in range(len(copia)):
        if(copia[j] == rankings[i]):
            equiposOrdenados.append(j+1)

for i in range(len(equiposOrdenados)):
    f.write("%d \n" %(equiposOrdenados[i]))
