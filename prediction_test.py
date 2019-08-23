import sys, os, subprocess
import copy

f = open(sys.argv[2],"r")
fl = list(f)
f.close()
f = fl

success_count = 0
n = len(f)
for i in range(1,len(f)):
    partido_eliminadoStr = f.pop(i)
    partido_eliminado = list(map(int,partido_eliminadoStr.split(" ")))[1:]
    fnew_comp = open("temp_comp.in","w")
    for line in f:
        fnew_comp.write(line)
    fnew_comp.close()
    subprocess.call("./main "+sys.argv[1]+" temp_comp.in temp_ranking.out", shell=True)
    fresult = open("temp_ranking.out","r")
    ranking = list(map(float,list(fresult)))
    rank0 = 1 #ranking de los equipos del partido eliminado
    rank1 = 1
    for num in ranking:
        if num > ranking[partido_eliminado[0]-1]:
            rank0 += 1
        if num > ranking[partido_eliminado[2]-1]:
            rank1 += 1
    if (rank0>=rank1) == (partido_eliminado[1] > partido_eliminado[3]):
        success_count += 1
    f.insert(i,partido_eliminadoStr)
    print(success_count,i)
    print(float(success_count)/float(i))

os.remove("temp_comp.in")
os.remove("temp_ranking.out")
