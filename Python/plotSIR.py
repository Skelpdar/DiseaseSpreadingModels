import matplotlib.pyplot as plt
import numpy as np

filename = "SIRSolutionEulerExp1.txt"

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

print(max(Serr), max(Ierr), max(R))

X = np.linspace(0, 30, 60)

#plt.figure(dpi = 200)
plt.plot(X,S, label = "S")
plt.fill_between(X,
    [S[k]-Serr[k] for k in range(0,len(S))],
    [S[k]+Serr[k] for k in range(0, len(S))])
plt.plot(X,I, label = "I")
plt.fill_between(X,
    [I[k]-Ierr[k] for k in range(0,len(I))],
    [I[k]+Ierr[k] for k in range(0, len(I))])
plt.plot(X,R, label = "R")
plt.fill_between(X,
    [R[k]-Rerr[k] for k in range(0,len(R))],
    [R[k]+Rerr[k] for k in range(0, len(R))])
plt.xlabel("t(days)")
plt.legend()


plt.show()