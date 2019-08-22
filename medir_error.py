import sys
import os
import subprocess
import numpy as np

def medir_error(archivo_partidos, archivo_ranking, verbose = False) :
	partidos = open(archivo_partidos, "r")

	## obtencion de matriz de colley y b
	n_equipos =  int(partidos.readline().split()[0])
	colley = np.identity(n_equipos, dtype = float)
	colley *= 2
	b =  np.zeros(n_equipos)	

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

		if puntaje_1 > puntaje_2:
			b[equipo_1-1] += 1.0
			b[equipo_2-1] -= 1.0
		else:
			b[equipo_1-1] -= 1.0
			b[equipo_2-1] += 1.0	
	

	b /= 2.0
	b += 1.0

	partidos.close()
	f = open(archivo_ranking)	
	

	## leer matriz resultado
	ranking = np.loadtxt(f, delimiter="\n")
	f.close()

	colley_inv = np.linalg.inv(colley)
	ranking_verd = colley_inv.dot(b) 
		
	

	if verbose:

		print "Colley---------"
		print colley		

		print "b---------"
		print b		

		print "Ranking obtenido---------"
		print ranking		


		print "Ranking verdadero-----"
		print ranking_verd		


	acumulado = 0.0
	for x in xrange(len(ranking_verd)):
		acumulado += abs(ranking_verd[x]  - ranking [x])
	return (acumulado/len(ranking_verd))


def correr_competencias():
	f = open("errores_en_base_a_n_equipo.txt", "w")
	for n in xrange(10,100):
		print n/(100.0-10.0)
		epsilon = 0.0
		N_DE_VECES_QUE_EJECUTA = 10

		for repeticiones in xrange(N_DE_VECES_QUE_EJECUTA):
			subprocess.call("python generador_competencia.py " + str(n) + " 0.5", shell=True)
			subprocess.call("./main 0 competencia_generada.in ranking.out", shell=True)

			temp = open("error.tsv", "r")
			epsilon += float(temp.readline().split()[0])
			temp.close()

		
		epsilon = epsilon/N_DE_VECES_QUE_EJECUTA
		f.write(str(epsilon)+"\n")
	f.close()

correr_competencias()


