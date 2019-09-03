import sys, os, subprocess
import copy

f = open(sys.argv[2],"r")
fl = list(f)
f.close()
f = fl

h = list(map(int,f[0].split(" ")))

success_count = 0
n = len(f)
for i in range(max([len(f)-100,1]),len(f)):
    #print(success_count,i,n)
    partido_eliminadoStr = f.pop(i)
    partido_eliminado = list(map(int,partido_eliminadoStr.split(" ")))[1:]
    equipo0 = partido_eliminado[0]-1
    equipo1 = partido_eliminado[2]-1
    goles0 = partido_eliminado[1]
    goles1 = partido_eliminado[3]
    fnew_comp = open("temp_comp.in","w")
    fnew_comp.write(str(h[0])+" "+str(h[1]-1)+"\n")
    for line in f[1:]:
        fnew_comp.write(line)
    fnew_comp.close()
    if len(sys.argv) > 3:
        print("./main "+sys.argv[1]+" temp_comp.in temp_ranking.out "+sys.argv[3])
        subprocess.call("./main "+sys.argv[1]+" temp_comp.in temp_ranking.out "+sys.argv[3], shell=True)
    else:
        subprocess.call("./main "+sys.argv[1]+" temp_comp.in temp_ranking.out", shell=True)

    fresult = open("temp_ranking.out","r")
    ranking = list(map(float,list(fresult)))
    rank0 = 1 #ranking de los equipos del partido eliminado
    rank1 = 1
    for num in ranking:
        if num > ranking[equipo0]:
            rank0 += 1
        if num > ranking[equipo1]:
            rank1 += 1
    if (rank0<=rank1) == (goles0 >= goles1):
        success_count += 1
    f.insert(i,partido_eliminadoStr)

print(success_count,n)
print(float(success_count)/n)

fout = open("prediction_result","w")
fout.write(str(success_count/n))
fout.close()

os.remove("temp_comp.in")
os.remove("temp_ranking.out")
