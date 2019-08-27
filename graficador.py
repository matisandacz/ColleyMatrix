import matplotlib.pyplot as plt
import csv



def plotear_por_n_de_equipos():
	x = []
	y = []
	y2 = []
	y3 = []	
	

	with open('datos/errores_en_base_a_n_equipo0.1.txt','r') as csvfile:
	    plots = csv.reader(csvfile, delimiter='\n')
	    n = 10.0
	    for row in plots:
	        x.append(n)
	        y.append(float(row[0])/100.0)
	        n += 1.0	

	with open('datos/errores_en_base_a_n_equipo0.4.txt','r') as csvfile:
	    plots = csv.reader(csvfile, delimiter='\n')
	    n = 10.0
	    for row in plots:
	        y2.append(float(row[0])/100.0)
	        n += 1.0	
	

	with open('datos/errores_en_base_a_n_equipo0.85.txt','r') as csvfile:
	    plots = csv.reader(csvfile, delimiter='\n')
	    n = 10.0
	    for row in plots:
	        y3.append(float(row[0])/100.0)
	        n += 1.0	
	

	plt.plot(x, y, x, y2 , x ,y3)
	plt.gca().legend(('0.1','0.4','0.85') ,title="densidad")
	plt.xlabel('n de equipos')
	plt.ylabel('||Ax -b||/n')
	plt.grid()
	plt.title("Efecto del numero de equipos en el error en b")
	plt.show()


def plotear_por_densidad():
	x = []
	y = []
	y2 = []
	y3 = []

	n_usados = [20, 50 ,80]

	densidad = 0.05
	for p in xrange(20):
		f =open('datos/errores_en_base_a_n_equipo' + str(densidad) + ".txt","r")
		lines= f.readlines()
		y.append(float(lines[n_usados[0]-10]))
		y2.append(float(lines[n_usados[1]-10]))
		y3.append(float(lines[n_usados[2]-10]))
		x.append(densidad)
		densidad += 0.05

	plt.plot(x, y, x, y2 , x ,y3)
	plt.gca().legend(('20','50','80') ,title="n de equipos")
	plt.xlabel('densidad')
	plt.ylabel('||Ax -b||/n')
	plt.grid()
	plt.title("Efecto de la densidad en el error en b")
	plt.show()



def plotear_3d():
	matrix 
	densidad = 0.05
	for p in xrange(20):
		with open('datos/errores_en_base_a_n_equipo' +  str(densidad) + ".txt",'r') as csvfile:
	    plots = csv.reader(csvfile, delimiter='\n')
	    y = []
	    for row in plots:
	        y.append(float(row[0])/100.0)

		densidad += 0.05