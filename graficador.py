import matplotlib.pyplot as plt
import csv

x = []
y = []

with open('errores.txt','r') as csvfile:
    plots = csv.reader(csvfile, delimiter='\n')
    n = 10.0
    for row in plots:
    	print row[0]
        x.append(n)
        y.append(row[0])
        n += 1.0


plt.plot(x, y, 'b')
plt.show()