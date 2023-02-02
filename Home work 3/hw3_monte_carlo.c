#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <omp.h>
const unsigned int N = 1e7; 


int main() {       
    unsigned int count = 0;
    int seed;
    double x, y, start, end;
    double pi;
    unsigned int i, tid;
    
    start = omp_get_wtime();
    #pragma omp parallel \
    private(x, y, seed, i, tid) \
    shared(N, count) \
    default(none)
    {
        tid = omp_get_thread_num();        
        seed = time(NULL) ^ tid; 
        #pragma omp for reduction(+:count)
        for (i = 0; i < N; ++i) {
            x = (double) rand_r(&seed) / (double) RAND_MAX;
            y = (double) rand_r(&seed) / (double) RAND_MAX;
            if (x * x + y * y <= 1.0) 
            {
                count++;
            }
        }
    }
    end = omp_get_wtime();
    pi = ((double)count / (double)N) * 4.0;
    
    printf("Pi: %f\n", pi);
    printf("Time: %f\n", end - start);

    return 0;
}
