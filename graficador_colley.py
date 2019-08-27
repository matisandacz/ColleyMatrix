import sys
import numpy as np
import matplotlib.pyplot as plt

# toma como parametro el archivo de los partidos
# se ejecuta como
#	 python graficador_colley <mi_archivo>

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

plt.imshow(obtener_colley(sys.argv[1]), cmap='bone', interpolation='none', vmin=(-1), vmax=1)
plt.show()
 