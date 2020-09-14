#include <vector>
#include <Eigen/Dense>

#ifndef RUNGE_KUTTA_H
#define RUNGE_KUTTA_H

using Eigen::Vector2d;

template <typename VectorType, typename Function>
VectorType rungeKuttaStep(VectorType yn, Function func, double h, double tn){
    VectorType k1 = h*func(tn, yn);
    VectorType k2 = h*func(tn+h/2, yn+k1/2);
    VectorType k3 = h*func(tn+h/2, yn+k2/2);
    VectorType k4 = h*func(tn+h, yn+k3);

    return yn+k1/6+k2/3+k3/3+k4/6;
}

template <typename VectorType, typename Function>
void rungeKutta(VectorType y0, Function func, double h, int iterations, std::vector<VectorType>& data, std::vector<VectorType>& error){
    VectorType yn = y0;
    double t = 0;
    for(int i=0; i<iterations; i++){
        data.push_back(yn);

        yn = rungeKuttaStep(yn, func, h, t);

        t += h;
    }
    
    std::vector<VectorType> halfSteps;
    yn = y0;
    t = 0;
    for(int i=0; i<iterations*2; i++){
        halfSteps.push_back(yn);

        yn = rungeKuttaStep(yn, func, h/2, t);

        t += h/2;
    }
    
    for(int i=0; i <iterations; i++){
        error.push_back((halfSteps[2*i]-data[i])/(32-1));
    }
    
}

#endif
