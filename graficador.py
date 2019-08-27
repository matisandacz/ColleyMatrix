import matplotlib.pyplot as plt
import csv

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