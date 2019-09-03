import random

NUMERO_DE_EQUIPOS = 100
NUMERO_DE_EQUIPOS_GRUPO_A = NUMERO_DE_EQUIPOS/2
NUMERO_DE_EQUIPOS_GRUPO_B = NUMERO_DE_EQUIPOS - NUMERO_DE_EQUIPOS_GRUPO_A

PARTIDOS_TOTALES = (NUMERO_DE_EQUIPOS_GRUPO_A * (NUMERO_DE_EQUIPOS_GRUPO_A - 1))/2 + (NUMERO_DE_EQUIPOS_GRUPO_B * (NUMERO_DE_EQUIPOS_GRUPO_B - 1))/2

f = open("competencia_generada.in", "w")
f.write(str(NUMERO_DE_EQUIPOS) + " " + str(PARTIDOS_TOTALES) +"\n")


for x in xrange(NUMERO_DE_EQUIPOS_GRUPO_A):
	for y in xrange(x+1, NUMERO_DE_EQUIPOS_GRUPO_A):
		puntaje_1 = random.gauss(0.0, 1)
		puntaje_2 = random.gauss(0.0, 1)
		if x == 0:
			puntaje_1 = random.gauss(10.0, 1)
		if y == 0:
			puntaje_2 = random.gauss(10.0, 1)

		if puntaje_1 > puntaje_2:
			f.write("1 " + str(x+1) + " 1 " + str(y+1) + " 0\n")
		elif puntaje_2 > puntaje_1:
			f.write("1 " + str(x+1) + " 0 " + str(y+1) + " 1\n")
		else:
			if random.randint(0, 1) == 0:
				f.write("1 " + str(x+1) + " 1 " + str(y+1) + " 0\n")
			else:
				f.write("1 " + str(x+1) + " 0 " + str(y+1) + " 1\n")


for x in xrange(NUMERO_DE_EQUIPOS_GRUPO_B):
	for y in xrange(x+1, NUMERO_DE_EQUIPOS_GRUPO_B):
		puntaje_1 = random.gauss(10.0, 1.0)
		puntaje_2 = random.gauss(10.0, 1.0)
		if puntaje_1 > puntaje_2:
			f.write("1 " + str(x+1+NUMERO_DE_EQUIPOS_GRUPO_A) + " 1 " + str(y+1+NUMERO_DE_EQUIPOS_GRUPO_A) + " 0\n")
		elif puntaje_2 > puntaje_1:
			f.write("1 " + str(x+1+NUMERO_DE_EQUIPOS_GRUPO_A) + " 0 " + str(y+1+NUMERO_DE_EQUIPOS_GRUPO_A) + " 1\n")
		else:
			if random.randint(0, 1) == 0:
				f.write("1 " + str(x+1+NUMERO_DE_EQUIPOS_GRUPO_A) + " 1 " + str(y+1+NUMERO_DE_EQUIPOS_GRUPO_A) + " 0\n")
			else:
				f.write("1 " + str(x+1+NUMERO_DE_EQUIPOS_GRUPO_A) + " 0 " + str(y+1+NUMERO_DE_EQUIPOS_GRUPO_A) + " 1\n")

f.close()