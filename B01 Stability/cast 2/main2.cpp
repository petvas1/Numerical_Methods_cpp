#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

int main()
{
    ofstream outdata;
    outdata.open("schema2.dat");
    double x[500],a;
    x[0] = 0;
    x[1] = 1;
    a = 0.001;
    for (int n=1;n<=500;n++){
        x[n+1] = a*x[n]-x[n-1];
        outdata << n-1 << "\t" << x[n-1] << endl;
    }
    outdata.close();
    return 0;
}
