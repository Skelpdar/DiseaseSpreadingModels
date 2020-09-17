import matplotlib.pyplot as plt
import numpy as np
from matplotlib import cm

filenames = [
    "ScaniaSIR_0.250000.txt",
    "ScaniaSIR_0.300000.txt",
    "ScaniaSIR_0.350000.txt",
    "ScaniaSIR_0.400000.txt",
    "ScaniaSIR_0.450000.txt",
    "ScaniaSIR_0.500000.txt"]

c = cm.get_cmap('viridis', 5)

N = 6

colors = [c(k/N) for k in range(0,N)]

for filename in filenames:
    with open(filename) as f:
        lines = f.readlines()

    S = []
    I = []
    R = []
    Serr = []
    Ierr = []
    Rerr = []

    for i in range(0,len(lines)):
        if i % 6 == 0:
            S.append(float(lines[i]))
        if i % 6 == 1:
            I.append(float(lines[i]))
        if i % 6 == 2:
            R.append(float(lines[i]))
        if i % 6 == 3:
            Serr.append(float(lines[i]))
        if i % 6 == 4:
            Ierr.append(float(lines[i]))
        if i % 6 == 5:
            Rerr.append(float(lines[i]))

    print(max(Serr), max(Ierr), max(Rerr))

    X = np.linspace(0, 365, 36500)

    #plt.figure(dpi = 200)
    #plt.plot(X,S, label = filename[10:14], color=colors[filenames.index(filename)])
    #plt.fill_between(X,
    #    [S[k]-Serr[k] for k in range(0,len(S))],
    #    [S[k]+Serr[k] for k in range(0, len(S))])
    plt.plot(X,I, label = filename[10:14], color=colors[filenames.index(filename)])
    plt.fill_between(X,
        [I[k]-Ierr[k] for k in range(0,len(I))],
        [I[k]+Ierr[k] for k in range(0, len(I))])
    #plt.plot(X,R, label = filename[10:14], color=colors[filenames.index(filename)])
    #plt.fill_between(X,
    #    [R[k]-Rerr[k] for k in range(0,len(R))],
    #    [R[k]+Rerr[k] for k in range(0, len(R))])
plt.xlabel("t [days]")
plt.ylabel("Infectious [# of People]")
plt.legend()
plt.title("Comparison of the spread constant beta")
#plt.yscale("log")
plt.show()
