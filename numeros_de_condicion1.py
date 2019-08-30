import numpy as np
import subprocess


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
	f = open("datos/n_de_condicion/campo_de_condiciones.txt", "w")
	densidad = 0.1

	N_DE_EQUIPOS_INICIAL = 10
	N_DE_EQUIPOS_FINAL = 100

	n = N_DE_EQUIPOS_INICIAL
	for y in xrange(10):
		string = ""	
		while n <= N_DE_EQUIPOS_FINAL:
			string = string + str(obtener_numero_de_condicion_1(n,densidad)) + " "
			n += 5

		f.write(string+"\n")
		print str(densidad*100.0) + " completado" 
		densidad += 0.1
	f.close()


guardar_campo()