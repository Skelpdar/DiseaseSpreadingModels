#include <vector>
#include <Eigen/Dense>

template <typename VectorType, typename Function>
VectorType rungeKuttaStep(VectorType yn, Function func, double h, double tn){
	VectorType k1 = h*func(tn, yn);
	VectorType k2 = h*func(tn+h/2, yn+k1/2);
	VectorType k3 = h*func(tn+h/2, yn+k2/2);
	VectorType k4 = h*func(tn+h, yn+k3);
	
	return yn+k1/6+k2/3+k3/3+k4/6;	
}

/*
Fourth order Runge Kutta method for ODEs (In R^N)
*/
template <typename VectorType, typename Function>
VectorType rungeKutta(VectorType y0, Function func, double h, int iterations, std::vector<VectorType>& data){
	VectorType yn = y0;
	double t = 0;
	for(int i=0; i<iterations; i++){
		data.push_back(yn);

		yn = rungeKuttaStep(yn, func, h, t);

		t += h;	
	}

}	
