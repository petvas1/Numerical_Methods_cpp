#include <iostream>
#include <cmath>
#include <fstream>
#define pi M_PI

using namespace std;

int main()
{
    double x0, xt, x1, x2, error, N;
    x0 = 0.2;
    xt = 23.6;
    error = 1e-11;
    N = 100;

    auto f = [](double x)
    {
        return pow( sin(pi*x), 2 );
    };

    ofstream fout;
    fout.open("data.dat");

    int i;
    for (i = 1; i < N; ++i)
    {
        if (f(x0) < f(xt)) swap (x0,xt);

        x1 = xt + abs(xt - x0);

        if (f(x1) < f(x0))
        {
            x2 = xt + 2*(xt - x0);
            if ( f(x2) < f(x0) ) x0 = x2;
            else x0 = x1;
        }
        else x0 = (x0 + xt)/2;

        fout << i << "\t" << x0 << endl;
        if ( abs(f(x0) - f(xt) ) < error) break;
    }
    fout.close();

    cout.precision(10);
    cout << "pocet krokov: " <<  i << endl;
    cout << "koren: " << x0 << endl;

    return 0;
}
