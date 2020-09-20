import matplotlib.pyplot as plt
import numpy as np
from matplotlib import cm

filenames = [
    "SEIR1.txt",
    "SEIR2.txt",
    "SEIR3.txt"]

lengths = [365*10, 365*2, 365]

c = cm.get_cmap('viridis', 5)

N = 6

colors = [c(k/N) for k in range(0,N)]

for filename in filenames:
    with open(filename) as f:
        lines = f.readlines()

    S = []
    E = []
    I = []
    R = []
    Serr = []
    Eerr = []
    Ierr = []
    Rerr = []

    for i in range(0,len(lines)):
        if i % 8 == 0:
            S.append(float(lines[i]))
        if i % 8 == 1:
            E.append(float(lines[i]))
        if i % 8 == 2:
            I.append(float(lines[i]))
        if i % 8 == 3:
            R.append(float(lines[i]))
        if i % 8 == 4:
            Serr.append(float(lines[i]))
        if i % 8 == 5:
            Eerr.append(float(lines[i]))
        if i % 8 == 6:
            Ierr.append(float(lines[i]))
        if i % 8 == 7:
            Rerr.append(float(lines[i]))

    print(max(Serr), max(Ierr), max(Rerr))

    X = np.linspace(0, 365, lengths[filenames.index(filename)])

    #plt.plot(X,S, label = "S")
    #plt.fill_between(X,
    #    [S[k]-Serr[k] for k in range(0,len(S))],
    #    [S[k]+Serr[k] for k in range(0, len(S))])
    #plt.plot(X,E, label = "E")
    #plt.fill_between(X,
    #    [E[k]-Eerr[k] for k in range(0,len(E))],
    #    [E[k]+Eerr[k] for k in range(0, len(E))])
    #plt.plot(X,I, label = "I")
    #plt.fill_between(X,
    #    [I[k]-Ierr[k] for k in range(0,len(I))],
    #    [I[k]+Ierr[k] for k in range(0, len(I))])
    plt.plot(X,R, label = "R, h = " + str(365/lengths[filenames.index(filename)]))
    plt.fill_between(X,
        [R[k]-Rerr[k] for k in range(0,len(R))],
        [R[k]+Rerr[k] for k in range(0, len(R))])
plt.xlabel("t(days)")
plt.legend()
plt.ylabel("# of people")
#plt.yscale("log")

plt.show()
