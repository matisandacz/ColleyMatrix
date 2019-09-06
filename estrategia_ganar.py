import numpy as np
import matplotlib.pyplot as plt
import subprocess
from shutil import copyfile
import sys

def obtener_posicion(equipo, archivo_ranking):
	ordenado = np.argsort(np.loadtxt(archivo_ranking))
	posicion = len(ordenado)
	for x in ordenado:
		if x+1 == equipo:
			break
		else:
			posicion -= 1
	return posicion


def equipo_en_posicion(posicion, archivo_ranking):
	ordenado = np.argsort(np.loadtxt(archivo_ranking))
	return ordenado[len(ordenado) - posicion] + 1


# indica las cantidad de veces que es nesesario para el
# equipo en la posicion_i vencer al que se encuentra en la posicion_d indicada para llegar al primer puesto
# si el equipo tiene la posicion indicada, entonces se enfrenta con una posicion arriba
def veces_necesarias_vencer_a_posicion(posicion_i, posicion_d, archivo_partidos):
	subprocess.call("main 0 " + archivo_partidos + " temp.out", shell=True)

	archivo_partidos_modificado = "archivo_partidos_modificado.txt"

	
	# copiado de internet. copia un archivo
	copyfile(archivo_partidos, archivo_partidos_modificado)

	mi_equipo = equipo_en_posicion(posicion_i,"temp.out")
	enfrentamientos_necesarios = 0

	while obtener_posicion(mi_equipo,"temp.out") != 1 and enfrentamientos_necesarios < 500:
		rival = equipo_en_posicion(posicion_d,"temp.out")
		if rival == mi_equipo:
			rival = equipo_en_posicion(posicion_d-1,"temp.out")

		# agregamos el partido
		f1 = open(archivo_partidos_modificado, "r")
		f2 = open("temp2.out","w")
		primera_linea = True
		for line in f1:
			if primera_linea:
				primera_linea = False
				f2.write(line.split()[0] + " " + str(int(line.split()[1])+1) + "\n" )
			else:
				f2.write(line)


		f2.write("1 " + str(mi_equipo) + " 1 " + str(rival) + " 0\n")
		f1.close()
		f2.close()

		copyfile("temp2.out", archivo_partidos_modificado)


		# generamos el archivo
		subprocess.call("main 0 " + archivo_partidos_modificado + " temp.out", shell=True)
		enfrentamientos_necesarios +=1
	
	return enfrentamientos_necesarios


def generar_campo(archivo_partidos):
	f = open(archivo_partidos, "r")
	equipos = int(f.readline().split()[0])
	f.close()

	#f = open("campo_para_estrategias.txt", "w")
	#f.close()

	for x in xrange(21,equipos+1):
		f = open("campo_para_estrategias.txt", "a")
		print "Calculando para el equipo en la posicion inicial " + str(x)
		tira = ""
		for y in xrange(1,6):
			tira = tira + str(veces_necesarias_vencer_a_posicion(x,y,archivo_partidos)) + " "
			print "Completado usando el equipo "  + str(x) + " contra el que este en " + str(y)  
		tira = tira + "\n"
		f.write(tira)
		f.close() 


generar_campo(sys.argv[1])

a = np.loadtxt("campo_para_estrategias.txt")[:19].transpose()

fig, ax = plt.subplots()
heatmap = ax.pcolor(a, edgecolors='k', linewidths=1.0) # heatmap contient les valeurs

ax.set_xticks(np.arange(19)+0.5, minor=False)
ax.set_xticklabels(np.arange(19)+ 2, minor=False)

ax.set_yticks(np.arange(5)+0.5, minor=False)
ax.set_yticklabels(np.arange(5)+ 1, minor=False)


plt.colorbar(heatmap)

plt.title('Victorias a una posicion especifica hasta terminar primero')
plt.xlabel('mi posicion inicial')
plt.ylabel('posicion a la que se enfrenta')

plt.show()
