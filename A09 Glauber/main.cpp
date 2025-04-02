#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <time.h>
#include <stdlib.h>
#include <numeric>
#include <stdint.h>	// uint64_t
#include <limits.h> // ULLONG_MAX
#define tstep if (t%(tend/100) == 0)

using namespace std;

static inline uint64_t rotl(const uint64_t x, int k)
{
	return (x << k) | (x >> (64 - k));
}

uint64_t xoroshiro128_next(uint64_t* s0, uint64_t* s1)
{
	const uint64_t _s0 = *s0;
	uint64_t _s1 = *s1;
	const uint64_t result = _s0 + _s1;

	_s1 ^= _s0;
	*s0 = rotl(_s0, 24) ^ _s1 ^ (_s1 << 16);
	*s1 = rotl(_s1, 37);

	return result;
}

double next_double(uint64_t* s0, uint64_t* s1)
{
	return (double)xoroshiro128_next(s0, s1) / (double)ULLONG_MAX;
}

int main(int argc, char** argv)
{
    srand(time(0));
    uint64_t s0 = rand() << 32 | rand();
    uint64_t s1 = rand() << 32 | rand();
    double x; //random number

    ofstream fout;
    fout.open("glauber1.dat");

    //double T; //teplota
    //T = 2.2;
    float T[5] = {2, 2.22, 2.26, 2.28, 2.35};
    float m;

    const int N = 512;
    int M[N][N]; //mriezka


    int spin[5] = {4, 2, 0, -2, -4}; //moznosti suctov okolitych spinov
    double Idx[5], P[5];

    int I, J, sum, index, tend;
    double p;
    tend = 1 * 5000;

    for (int k = 0; k < 1; ++k)
    {
        m = 0;
        for (int s = 0; s < 5; ++s)
        {
            Idx[s] = 0.5*spin[s] + 3;
            P[s] = 1/( 1 + exp(2*(2*(Idx[s])-6)/T[k]) ); //pravdepodobnosti otocenia
        }

        //pociatocny stav
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N ; ++j)
            {
                x = next_double(&s0, &s1); //nahodne cislo
                if (x > 0.5) M[i][j] = 1;
                else M[i][j] = -1;
                fout << M[i][j] << "\t";
            }
            fout << endl;
            //m += accumulate(M[i], M[i] + N, 0);
        }
        fout << "\n\n";
        //fout << 0 << "\t" << m/(N*N) << endl; //t = 0

        for (int t = 1; t <= tend; ++t)
        {
            m = 0;
            for (int i = 0; i < N; ++i)
            {
                for (int j = 0; j < N ; ++j)
                {
                    //najdenie nahodneho indexu spinu
                    I = N*next_double(&s0, &s1);
                    J = N*next_double(&s0, &s1);

                    sum = M[(I-1+N)%N][J] + M[(I+1)%N][J] + M[I][(J-1+N)%N] + M[I][(J+1)%N]; //suma spinov okolo M[I][J]
                    auto itr = find(spin, spin + 5, sum);
                    index = distance(spin, itr); //poradove cislo podla sumy okolitych spinov
                    if (M[I][J] == -1) p = 1 - P[index]; //pravdep. ze sa spin s hodnotou -1 otoci
                    else p = P[index]; //pravdep. ze sa spin s hodnotou +1 otoci
                    x = next_double(&s0, &s1);
                    if (x < p) M[I][J] *= -1; //otoc spin s pravdep. p
                    tstep fout << M[i][j] << "\t";
                }
                tstep m += accumulate(M[i], M[i] + N, 0);
                //tstep fout << endl;
            }
            //tstep fout << t/5000. << "\t" << m/(N*N) << endl;
            //tstep fout << "\n\n";
        }
        //fout << "\n\n";
    }

    fout.close();
    return 0;
}
