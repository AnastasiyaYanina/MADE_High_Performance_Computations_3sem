#include <omp.h>
#include <stdio.h>
#include <stdlib.h>


float dotprod(int *a, int *b, size_t N)
{
    int i, tid;
    float sum;  
    #pragma omp parallel private(i, tid) shared(a, b, N, sum) 
    {
        tid = omp_get_thread_num();
        #pragma omp for reduction(+:sum)
        for (i = 0; i < N; ++i){ 
            sum += a[i] * b[i];
            printf("tid = %d i = %d\n", tid, i);
        }
    }

    return sum;
}


int main (int argc, char *argv[])
{
    const size_t N = 100;
    int i;
    int sum;
    int a[N], b[N];

    for (i = 0; i < N; ++i)
    {
        a[i] = b[i] = (int)i;
    }

    sum = 0.0;
    sum = dotprod(a, b, N);

    printf("Sum = %d\n",sum);
    return 0;
}
