#include <iostream>
#include <fstream>
#include <iomanip>
#include <valarray>
#include <cmath>
#include <vector>
#define pi M_PI

using namespace std;

void step(double h, double x, valarray<double> &Y, double omega);
valarray<double> f(double x, valarray<double> Y, double omega);

int main()
{
    ofstream fout;
    fout.open("data.dat");
    double x, h, N, L, error, omega1, omega2, omega3, omegaMax, omegaMin, omegaStep, intervals, y1, y2, y3;
    vector <double> om;
    L = 1;

    int M = 2; //number of equations
    valarray<double> Y(M), k1(M), k2(M), k3(M), k4(M);

    //initial values Y[0] = y(x0), Y[1] = y'(x0), ...
    x = 0; Y[0] = 0; Y[1] = 1;

    // Set step size and number of steps
    h = 0.01;
    N = 1e5;

    fout.precision(10);

    error = 1e-10;
    omegaMin = 0;
    omegaMax = 50;
    omegaStep = 1;
    intervals = (omegaMax - omegaMin)/omegaStep;

    for (int i=0;i<intervals;i++)
    {
        // divide interval
        omega1 = omegaMin + i*omegaStep;
        omega2 = omega1 + omegaStep;

        while ((omega2-omega1) >= error)
        {
            // find y(omega1), y(omega2), y(omega3) when x==L
            auto func = [=,&x,&Y](double omega)
            {
                double y; // output
                x = 0; Y[0] = 0; Y[1] = 1;
                for (int n=1; n<N; n++) // Solve the differential equation
                {
                    if (x==L)
                    {
                        y = Y[0];
                        break;
                    }
                    x = n*h;
                    step(h, x, Y, omega); // main R-K step
                }
                return y;
            };

            y1 = func(omega1);
            y2 = func(omega2);
            omega3 = (omega1 + omega2)/2;
            y3 = func(omega3);

            if (y1*y3<0)
                omega2 = omega3;
            else
                omega1 = omega3;
        }

        if (y1*y2<0)
            om.push_back(omega3);
    }

    // Find values of y
    for (int j=0;j<5;j++)
    {
        x = 0; Y[0] = 0; Y[1] = 1;
        for (int n=1; n<N; n++)
        {
            fout << x << "\t" << Y[0] << endl;
            x = n*h;
            if (x>L) break;
            step(h, x, Y, om[j]); // main R-K step
        }
        fout << "\n\n";
    }

    fout.close();
    return 0;
}

void step(double h, double x, valarray<double> &Y, double omega)
{
    int M = Y.size();
    valarray<double> k1(M), k2(M), k3(M),k4(M);

    k1 = h*f(x, Y, omega);
    k2 = h*f(x+0.5*h, Y+0.5*k1, omega);
    k3 = h*f(x+0.5*h, Y+0.5*k2, omega);
    k4 = h*f(x+h, Y+k3, omega);
    Y += (k1 + 2.*k2 + 2.*k3 + k4)/6.;
}

valarray<double> f(double x, valarray<double> Y, double omega)
{
    valarray<double> F(Y.size());  //output

    double alpha = 1;

    //equations Y[0] = y, Y[1] = y', Y[2] = y",...
    F[0] = Y[1];
    F[1] = -alpha*omega*omega*Y[0];

    return F;
}
