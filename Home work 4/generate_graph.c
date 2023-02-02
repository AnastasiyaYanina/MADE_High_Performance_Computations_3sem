#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <omp.h>

void generate_matrix(double *matrix, int N, float edge_prob) {
    int i, j;
    int seed = time(NULL);
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            if ((float)rand_r(&seed) / RAND_MAX < edge_prob) {
                matrix[i * N + j] = 1;
            } else {
                matrix[i * N + j] = 0;
            }
        }
    }
}

void matmul_matrix(double *A, double *B, double *C, int N) {
    int i, j, k;
    #pragma omp parallel for private(i, j, k) shared(A, B, C, N) default(none)
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            C[i * N + j] = 0;
            for (k = 0; k < N; ++k) {
                C[i * N + j] += A[i * N + k] * B[k * N + j];
            }
        }
    }
}

void power_matrix(double *matrix, double *result, int N, int power) {
    int power_bit = 0;
    while ((power >> power_bit) > 0) {
    	power_bit += 1;
    }
    
    double *power_matrix[power_bit];
    int i;
    for (i = 0; i < power_bit; ++i) {
        power_matrix[i] = (double *) malloc(N * N * sizeof(double));
    }
    
    memcpy(power_matrix[0], matrix, N * N * sizeof(double));
    for (i = 1; i < power_bit; ++i) {
        matmul_matrix(
            power_matrix[i - 1], power_matrix[i - 1], power_matrix[i], N);
    }

    double *buffer = (double *) malloc(N * N * sizeof(double));
    memcpy(result, power_matrix[power_bit - 1], N * N * sizeof(double));
    for (i = 1; i < power_bit; ++i) {
        int current_bit_ind = power_bit - i - 1;

        if (power & (1 << current_bit_ind) != 0) {
            matmul_matrix(result, power_matrix[current_bit_ind], buffer, N);
            memcpy(result, buffer, N * N * sizeof(double));
        }
    }
    free(buffer);
    for (i = 0; i < power_bit; ++i) {
        free(power_matrix[i]);
    }
}

int main(int argc, char *argv[]) {
    const float EDGE_PROB = 0.6;
    
    int N, power;
    printf("N power");
    printf("\n");
    scanf("%d", &N);
    scanf("%d", &power);     

    double *matrix = (double *) malloc(N * N * sizeof(double));
    generate_matrix(matrix, N, EDGE_PROB);
    
    int i = N, j = N;
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            printf("%.0lf ", matrix[i * N + j]);
        }
        printf("\n");
    }
    printf("\n");
    
    double *result = (double *) malloc(N * N * sizeof(double));   
    power_matrix(matrix, result, N, power);

    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            printf("%.0lf ", result[i * N + j]);
        }
        printf("\n");
    }
    free(result);
    free(matrix);
    return 0;
}
