#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

int main()
{
    ofstream outdata;
    outdata.open("schema3.dat");
    double x[500],X;
    int N = 100;
    X = sqrt(M_PI);
    x[N] = 0;
    x[N-1] = 1;
    for (int n=N-1;n>0;n--){
        x[n-1] = -x[n+1] + (4+0.1*cos(M_PI*n))*x[n];
    }
    for (int i=0;i<N;i++){
        outdata << i << "\t" << X/x[0]*x[i] << endl;
    }
    outdata.close();
    return 0;
}
