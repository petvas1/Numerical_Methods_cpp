#include <time.h>
#include <random>

#include "xoroshiro128plus.h"

int main(int argc, char** argv)
{
    const int N = 10000;

    srand(time(0));
    uint64_t s0 = rand() << 32 | rand();
    uint64_t s1 = rand() << 32 | rand();

    double* x = new double[N];

    for (int i = 0; i < N; i++)
    {
        x[i] = next_double(&s0, &s1);
    }

    return 0;
}