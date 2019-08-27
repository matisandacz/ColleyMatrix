import numpy as np
import matplotlib.pyplot as plt

fin = open("out.out","r")

y0 = []
y1 = []
y2 = []
for line in fin:
    line = list(map(float,line.split(" ")))
    y0.append(line[0])
    y1.append(line[1])
    y2.append(line[2])

plt.figure()
plt.plot(np.arange(len(y0)),y0,color = "red")
plt.plot(np.arange(len(y1)),y1,color = "blue")
plt.plot(np.arange(len(y2)),y2,color = "green")
plt.show()

#import numpy as np
#import matplotlib.pyplot as plt
#
#fin0 = open("out0.out","r")
#fin1 = open("out1.out","r")
#fin2 = open("out2.out","r")
#fin3 = open("out3.out","r")
#fin4 = open("out4.out","r")
#
#
#y0 = []
#y1 = []
#y2 = []
#y3 = []
#y4 = []
#
#for line in fin0:
#    line = list(map(float,line.split(" ")))
#    y0.append(line[0])
#for line in fin1:
#    line = list(map(float,line.split(" ")))
#    y1.append(line[0])
#for line in fin2:
#    line = list(map(float,line.split(" ")))
#    y2.append(line[0])
#for line in fin3:
#    line = list(map(float,line.split(" ")))
#    y3.append(line[0])
#for line in fin4:
#    line = list(map(float,line.split(" ")))
#    y4.append(line[0])
#
#
#plt.figure()
#plt.plot(np.arange(len(y0)),y0,color = "green")
#plt.plot(np.arange(len(y1)),y1,color = "blue")
#plt.plot(np.arange(len(y2)),y2,color = "red")
#plt.plot(np.arange(len(y3)),y3,color = "orange")
#plt.plot(np.arange(len(y4)),y4,color = "purple")
#plt.show()
#
