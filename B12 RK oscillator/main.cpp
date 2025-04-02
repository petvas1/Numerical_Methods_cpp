#include <iostream>
#include <fstream>
#include <iomanip>
#include <valarray>
#include <cmath>
#define pi M_PI

using namespace std;

void step(double h, double &t, valarray<double> &Y);
valarray<double> f(double t, valarray<double> Y);

int main()
{
    ofstream fout;
    fout.open("data2.dat");
    double t, h, N;
    int M = 3; //number of equations
    valarray<double> Y(M);

    //initial values Y[0] = y(t0), Y[1] = y'(t0), ...
    t = 0; Y[0] = 0; Y[1] = 1; Y[2] = 0;

    // Set step size and number of steps
    h = 2*pi/1000;
    N = 1e7;

    fout.precision(10);

    for (int n=1; n<=N; n++) // Solve the differential equation using N intervals
    {
        if (n%500 == 0) fout << t << "\t" << Y[0] << "\t" << Y[1] << endl;
        step(h, t, Y); // main R-K step
    }

    fout.close();
    return 0;
}

void step(double h, double &t, valarray<double> &Y)
{
    int M = Y.size();
    valarray<double> k1(M), k2(M), k3(M),k4(M);

    k1 = h*f(t, Y);
    k2 = h*f(t+0.5*h, Y+0.5*k1);
    k3 = h*f(t+0.5*h, Y+0.5*k2);
    k4 = h*f(t+h, Y+k3);
    Y += (k1 + 2.*k2 + 2.*k3 + k4)/6.;
    t += h;
}

valarray<double> f(double t, valarray<double> Y)
{
    valarray<double> F(Y.size());  //output

    double omega0, omega, gamma, force;
    //omega0 = 2*pi;
    //omega = 0.99*omega0;
    gamma = 0.05;
    force = 7.5*cos(t);

    //equations Y[0] = y, Y[1] = y', Y[2] = y",...
    F[0] = Y[1];
    F[1] = - gamma*Y[1] - pow(Y[0],3) + force;
    F[2] = force*Y[1];

    return F;
}
