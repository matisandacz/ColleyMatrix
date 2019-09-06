import numpy as np
import subprocess
import matplotlib.pyplot as plt


def obtener_colley(archivo_partidos):
	partidos = open(archivo_partidos, "r")

	## obtencion de matriz de colley 
	n_equipos =  int(partidos.readline().split()[0])
	colley = np.identity(n_equipos, dtype = float)
	colley *= 2

	for line in partidos:
		palabras = line.split()
		equipo_1 = int(palabras[1])
		puntaje_1 = int(palabras[2])
		equipo_2 = int(palabras[3])
		puntaje_2 = int(palabras[4])	

		colley[equipo_1-1][equipo_2-1] -=1
		colley[equipo_2-1][equipo_1-1] -=1	

		colley[equipo_1-1][equipo_1-1] += 1
		colley[equipo_2-1][equipo_2-1] += 1	

	partidos.close()

	return colley


def obtener_numero_de_condicion_1_de_competencia(archivo_partidos):
	return np.linalg.cond(obtener_colley(archivo_partidos),1)


def obtener_numero_de_condicion_1(numero_de_equipos, densidad):
	max_k = 0.0
	for x in xrange(100):
		subprocess.call("python generador_competencia.py " + str(numero_de_equipos) + " "+ str(densidad), shell=True)
		k_actual = obtener_numero_de_condicion_1_de_competencia("competencia_generada.in")
		max_k = max(max_k,k_actual)

	return max_k


def guardar_campo():
	f = open("campo_de_condiciones.txt", "w")
	f.close()

	densidad = 0.1

	N_DE_EQUIPOS_INICIAL = 10
	N_DE_EQUIPOS_FINAL = 100

	for y in xrange(10):
		f = open("campo_de_condiciones.txt", "a")
		string = ""
		n = N_DE_EQUIPOS_INICIAL
		while n <= N_DE_EQUIPOS_FINAL:
			string = string + str(obtener_numero_de_condicion_1(n,densidad)) + " "
			print string
			n += 10

		f.write(string+"\n")
		f.close()
		print str(densidad*100.0) + " completado" 
		densidad += 0.1


guardar_campo()

a = np.loadtxt("campo_de_condiciones.txt")

fig, ax = plt.subplots()
heatmap = ax.pcolor(a, edgecolors='k', linewidths=1.0) # heatmap contient les valeurs

ax.set_xticks(np.arange(10)+0.5, minor=False)
ax.set_xticklabels(np.arange(10)*10 + 10  , minor=False)

ax.set_yticks(np.arange(10)+0.5, minor=False)
ax.set_yticklabels([0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0], minor=False)

for i in xrange(10):
    for j in xrange(10):
        text = ax.text(j + 0.5, i + 0.5, int(a[i, j]),  ha="center", va="center", color="w")


plt.colorbar(heatmap)

plt.title('k1 maximo para distintas densidades y numero de equipos')
plt.xlabel('n de equipos')
plt.ylabel('densidad')

plt.show()