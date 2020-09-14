//Eulers method
//given initial value problem, y'(x) = f(x, y(x)), y(x_0) = y_0, Step-size, # of steps

#include <iostream>
#include <vector>
#include <Eigen/Dense>

using namespace std;
using Eigen::MatrixXd;

template<typename vecType,typename func>
vecType eulerStep(vecType y_n, func f, double stepSize, double t) {
    return y_n + stepSize*f(t, y_n)
};
//note f vector valued funtion n -> n where n is size of y_n

template<typename vecType, typename func>
vecType euler(vecType y0, func f, double stepSize, int N) {//y0: vector of initial values; f: vector of derivative expresions; 
//N: number of steps; sysSize: number of OEDs in the system, assumes t0 = 0
    vecType y_n;
    vector<vecType> solutions
    y_n = y0;
    for (int i = 0; i < N; i++) {
        solutions.push_back(y_n);
        y_n = eulerStep(y_n, f, stepSize, i*stepSize);
    }
    return solution;
};
