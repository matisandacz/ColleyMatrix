import numpy as np
import matplotlib.pyplot as plt
import sys,os,subprocess

n_equipos = int(sys.argv[1])
n_partidos = int(sys.argv[2])

n = int(sys.argv[3]) #numero de competencias a simular

print(n_equipos,n)
pivotes = np.zeros(shape = (n,n_equipos))
print(pivotes.shape)

for k in range(n):
    #genero la competencia
    #triangulo con generate_ranking printeando los pivotes en un archivo
    #por cada competencia me guardo el vector de pivotes
    #promedio todos esos vectores y grafico
    subprocess.call("python ../Scripts\ generadores/generador_competencia.py " + str(n_equipos) + " "+ str(n_partidos), shell=True)
    subprocess.call("../main 0 ../competencia_generada.in ../ranking.out 2", shell=True)
    f = open("pivotes.csv","r")
    flist = list(f)
    for i in range(n_equipos):
        pivotes[k,i] = float(flist[i])

pivotes_minimos = np.min(pivotes,axis = 0)

plt.figure()
plt.grid()
plt.xlabel("Número de columna")
plt.ylabel("Valor del pivote")
plt.plot(np.arange(n_equipos),pivotes_minimos)
plt.ylim(bottom = 0)
plt.show()
