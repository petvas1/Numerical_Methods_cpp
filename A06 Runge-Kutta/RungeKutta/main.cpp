#include <iostream>
#include <fstream>
#include <iomanip>
#include <valarray>
#include <cmath>
#define pi M_PI

using namespace std;

void step(double h, double &x, valarray<double> &Y);
valarray<double> f(double x, valarray<double> Y);

int main()
{
    ofstream fout;
    fout.open("data.dat");
    double x, h, N;
    int M = 2; //number of equations
    valarray<double> Y(M);

    //initial values Y[0] = y(x0), Y[1] = y'(x0), ...
    x = 0; Y[0] = 0; Y[1] = 1;

    // Set step size and number of steps
    h = 0.001;
    N = 1e4;

    fout.precision(10);

    for (int n=0; n<=N; n++) // Solve the differential equation using N intervals
    {
        fout << x << "\t" << Y[0] << "\t" << Y[1] << endl;
        step(h, x, Y); // main R-K step
    }

    fout.close();
    return 0;
}

void step(double h, double &x, valarray<double> &Y)
{
    int M = Y.size();
    valarray<double> k1(M), k2(M), k3(M),k4(M);

    k1 = h*f(x, Y);
    k2 = h*f(x+0.5*h, Y+0.5*k1);
    k3 = h*f(x+0.5*h, Y+0.5*k2);
    k4 = h*f(x+h, Y+k3);
    Y += (k1 + 2.*k2 + 2.*k3 + k4)/6.;
    x += h;
}

valarray<double> f(double x, valarray<double> Y)
{
    valarray<double> F(Y.size());  //output

    double omega = 2*pi, gamma = 0.1;

    //equations Y[0] = y, Y[1] = y', Y[2] = y",...
    F[0] = Y[1];
    F[1] = -omega*omega*Y[0] - gamma*Y[1];

    return F;
}
