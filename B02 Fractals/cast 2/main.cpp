#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

int main()
{
    ofstream outdata;
    outdata.open("pravdep.dat");
    double x=0.01,lambda=3.56995;
    const int M=1e6,N=1e9;
    int h[M]={0},index;
    for(int i=1;i<=N;i++){
        x = lambda*x*(1-x);
        index = int(x*M);
        h[index]++;
    }
    for (int j=0;j<M;j++){
        if (h[j]>0) outdata << double(j)/double(M) << "\t" <<  h[j] << endl;
    }
    outdata.close();
    return 0;
}
