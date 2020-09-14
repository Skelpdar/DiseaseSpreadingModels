# DiseaseSpreadingModels

Project for FYTN03 Computational Physics at Lundy University

It's 2020, and every physicist has become a hobby-epidemologist. Today it is our turn. 

Models:
-SIS (Suseptible-Infected-Suseptible)
-SIR (Suseptible-Infected-Resistant)
-SIR with traveling (add different populations with traveling coeff )

Methods
-Euler
    -(Richardsom Extrapolation)
-RK (4th order)

Error
-Num error estimet for O(h^m) algorithm

Installation:
```
git clone https://github.com/Skelpdar/DiseaseSpreadingModels.git
```

Download [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page) and copy the Eigen header-directory to the root of this project. 

Build with:
```
cmake .
make
```
