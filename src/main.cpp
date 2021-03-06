#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include <vector>
#include <string>
#include <exception>

#include <rungeKutta.h>
#include <euler.h>

using Eigen::MatrixXd;
using Eigen::Vector2d;
using Eigen::Vector3d;
using Eigen::Vector4d;
using Eigen::VectorXd;

using namespace Eigen;

double beta = 3;
double alpha = 0.14;

Vector2d SIS(double tn, Vector2d y){
    Vector2d v;

    v(0) = -beta*y(0,0)*y(1,0)/(y(0,0)+y(1,0))+alpha*v(1,0);
    v(1) = beta*y(0,0)*y(1,0)/(y(0,0)+y(1,0))-alpha*v(1,0);

    return v;

}

//The SIR model, includes resistant population and vacination of suseptible pop, N = S + I + R
double SIRInfec = 3;
double SIRRec = 0.14;
double SIRVac = 0;

//vector function for the derivatives of S, I & R respectively, y = (S, I, R), tn for generality
Vector3d SIR(double tn, Vector3d y) {
    Vector3d derivatives;
    double S = y(0,0);
    double I = y(1,0);
    double R = y(2,0);
    double N = S + I + R;

    derivatives(0) = -SIRInfec*S*I/N - SIRVac*S;
    derivatives(1) = SIRInfec*S*I/N - SIRRec*I;
    derivatives(2) = SIRVac*S + SIRRec*I;

    return derivatives;
}

double b = 0.45;
double a = 0.18;
double sigma = 0.41;

//Missing some parameters
Vector4d SEIR(double tn, Vector4d y){
	Vector4d derivatives;
    double S = y(0,0);
	double E = y(1,0);
    double I = y(2,0);
    double R = y(3,0);
    double N = S + E + I + R;

	derivatives(0) = -b*I*S/N;
	derivatives(1) = b*I*S/N-a*E;
	derivatives(2) = a*E - sigma*I;
	derivatives(3) = sigma*I;

	return derivatives;
}

//SIR with traveling
//populations
Vector4d SusV;//S1 to S4 with initial suseptible population in four diferent groups
Vector4d InfV;
Vector4d RecV;

//SIR parameters given as vectors
Vector4d TInf =  Vector4d (1, 1, 0.3, 0.3);
double TRec =  0.14; //recovery rate is the same for all populations
Vector4d TVac =  Vector4d (0.05, 0.05, 0.05, 0.05);




//Vector function containing derivatives of all pops, y(S1, S2, S3, S4, I1, I2, I3, I4 R1, R2, R3, R4)
VectorXd TravelSIR(double tn, VectorXd y){
    VectorXd sol(12);
    Vector4d S;
        S << y(0), y(1), y(2), y(3);
    Vector4d I;
        I << y(4), y(5), y(6), y(7);
    Vector4d R;
        R << y(8), y(9), y(10), y(11);

    //Traveling parameters into relevant population, balanced w_nm = w_mn required
    MatrixXd Tcoff(4,4);
    Tcoff <<   0, 0.01, 0.1/3, 0,
             0.01,   0,   0, 0.1/3,
             0.1,   0,   0, 0,
               0, 0.1,   0, 0;
    //Sn
    for (int i = 0; i < 4; i++) {//for each pop
        double sumTS = 0;
        for (int j = 0; j < 4; j++) {//calculate sum of traveling, from j going to i
            if (j != i) {
                sumTS += Tcoff(i, j)*S(j) - Tcoff(j, i)*S(i);
            };
        };
        sol(i) = -TInf(i)*S(i)*I(i)/(S(i)+R(i)+I(i))- TVac(i)*S(i) + sumTS;       
        };

    //In
    for (int i = 0; i < 4; i++) {//for each pop
        double sumTI = 0;
        for (int j = 0; j < 4; j++) {//calculate sum of traveling, from j going to i
            if (j != i) {
                sumTI += Tcoff(i, j)*I(j) - Tcoff(j, i)*I(i);
            };
        };
        sol(i+4) = TInf(i)*S(i)*I(i)/(S(i)+R(i)+I(i)) - TRec*I(i) + sumTI;        
        };
    //Rn
    for (int i = 0; i < 4; i++) {//for each pop
        double sumTR = 0;
        for (int j = 0; j < 4; j++) {//calculate sum of traveling, from j going to i
            if (j != i) {
                sumTR += Tcoff(i, j)*R(j) - Tcoff(j, i)*R(i);
            };
        };
        sol(i+8) = TVac(i)*S(i) + TRec*I(i) + sumTR;        
        };
    return sol;
};


int main(){
    /*
    Vector2d y0;
    y0(0) = 199;
    y0(1) = 1;

    std::vector<Vector2d> data;
    std::vector<Vector2d> error;
 
    rungeKutta(y0, SIS, 0.5, 60, data, error);
    std::ofstream SISFile;
    SISFile.open("SISSolutionRK.txt");

    for(int i=0; i<data.size(); i++){
        SISFile << data[i] << std::endl;
        SISFile << error[i] << std::endl;
    }

    SISFile.close();

    //test for euler method

    Vector3d y0;
    y0(0) = 199;
    y0(1) = 1;
    y0(2) = 0;

    std::vector<Vector3d> data;
    std::vector<Vector3d> error;
 
    euler(y0, SIR, 0.5, 60, data, error);
    std::ofstream SIRFile;
    SIRFile.open("SIRSolutionEuler.txt");

    for(int i=0; i<data.size(); i++){
        SIRFile << data[i] << std::endl;
        SIRFile << error[i] << std::endl;
    }
*/
//SIR with traveling
    /*
	std::vector<VectorXd> data;
    std::vector<VectorXd> error;

    VectorXd initPop(12);
    initPop <<  200, 200, 590, 600, 
                0, 0, 10, 0,
                0, 0, 0, 0;
 
    rungeKutta(initPop, TravelSIR, 0.01, 3000, data, error);
    std::ofstream SISFile;
    SISFile.open("SIRTravel.txt");

    for(int i=0; i<data.size(); i++){
        SISFile << data[i] << std::endl;
        SISFile << error[i] << std::endl;
    }

    SISFile.close();
	*/
	
	//SEIR
	std::vector<Vector4d> data1;
	std::vector<Vector4d> error1;
	std::vector<Vector4d> data2;
	std::vector<Vector4d> error2;
	std::vector<Vector4d> data3;
	std::vector<Vector4d> error3;
	
	Vector4d y0;
	y0(0) = 179000;
	y0(1) = 1000;
	y0(2) = 0;
	y0(3) = 0;

	rungeKutta(y0, SEIR, 0.1, 365*10, data1, error1);
	rungeKutta(y0, SEIR, 0.5, 365*2, data2, error2);
	rungeKutta(y0, SEIR, 1.0, 365, data3, error3);
	
	std::ofstream SISFile1;
    SISFile1.open("SEIR1.txt");
	std::ofstream SISFile2;
    SISFile2.open("SEIR2.txt");
	std::ofstream SISFile3;
    SISFile3.open("SEIR3.txt");

    for(int i=0; i<data1.size(); i++){
        SISFile1 << data1[i] << std::endl;
        SISFile1 << error1[i] << std::endl;
    }
    for(int i=0; i<data2.size(); i++){
        SISFile2 << data2[i] << std::endl;
        SISFile2 << error2[i] << std::endl;
    }
    for(int i=0; i<data3.size(); i++){
        SISFile3 << data3[i] << std::endl;
        SISFile3 << error3[i] << std::endl;
    }

    SISFile1.close();
    SISFile2.close();
    SISFile3.close();

    return 0;
}
