import sys
from numpy import array
from scipy.linalg import lu

# Generamos el archivo que tenga n partidos entre 2 equipos.
f = open("competencia_generada.in", "w")

partidos = int(sys.argv[1])

#Primer linea de formato.
f.write(str(2) + " " + str(partidos) +"\n")

#Hiperparametro
victoriasPrimero = 0

#Generamos partidos artificiales.
for i in xrange(victoriasPrimero):
	f.write("1 " + str(1) + " 1 " + str(2) + " 0\n")
for i in xrange (partidos - victoriasPrimero):
	f.write("1 " + str(1) + " 0 " + str(2) + " 0\n")



#a = array([[5.,6.,4.,4.],
#		  [1.,2.,3.,3.],
#		  [1.,2.,2.,2.],
#		  [1.,4.,3.,4.]])
#pl, u = lu(a, permute_l=True)
#print(u)

f.close()