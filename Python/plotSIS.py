import matplotlib.pyplot as plt
import numpy as np

filename = "SISSolution.txt"

with open(filename) as f:
    lines = f.readlines()

S = []
I = []
Serr = []
Ierr = []

for i in range(0,len(lines)):
    if i % 4 == 0:
        S.append(float(lines[i]))
    if i % 4 == 1:
        I.append(float(lines[i]))
    if i % 4 == 2:
        Serr.append(float(lines[i]))
    if i % 4 == 3:
        Ierr.append(float(lines[i]))

print(Serr)

X = np.linspace(0, 1000, 100)

plt.plot(X,S)
plt.fill_between(X,
    [S[k]-Serr[k] for k in range(0,len(S))],
    [S[k]+Serr[k] for k in range(0, len(S))])
plt.plot(X,I)
plt.fill_between(X,
    [I[k]-Ierr[k] for k in range(0,len(I))],
    [I[k]+Ierr[k] for k in range(0, len(I))])

plt.show()
