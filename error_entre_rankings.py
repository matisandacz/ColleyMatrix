import numpy as np
import sys

f1 = open(sys.argv[1],"r")
f2 = open(sys.argv[2],"r")
r1 = list(map(float,list(f1)))
r2 = list(map(float,list(f2)))
f1.close()
f2.close()

fout = open(sys.argv[3],"w")

for i in range(len(r1)):
    fout.write(str(np.abs(r1[i]-r2[i])))

error = np.array(r1)-np.array(r2)

print("Norma 2 del error:",np.linalg.norm(error))
print("Norma 1 del error:",np.linalg.norm(error, ord = 1))
print("Norma infinito del error:",np.linalg.norm(error, ord = np.inf))
print("Error promedio: ",np.linalg.norm(error, ord = 1)/len(r1))
