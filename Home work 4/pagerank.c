#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

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
    int i, j;
    for (i = 0; i < N; ++i) {
        C[i] = 0;
        for (j = 0; j < N; ++j) {
            C[i] += A[i * N + j] * B[j];
        }
    }
}

double l1_dist_matrix(double *A, double *B, int N) {
    double result = 0;
    int i;
    for (i = 0; i < N; ++i) {
        result += fabs(A[i] - B[i]);
    }
    return result;
}

void pagerank_matrix(double *matrix, double *result, int N, double eps, double damping, int max_iter) {
    double *f_matrix = (double *) malloc(N * N * sizeof(double));
    int i, j;
    for (i = 0; i < N; ++i) {
        double row_sum = 0;
        for (j = 0; j < N; ++j) {
            row_sum += matrix[i * N + j];
        }
        for (j = 0; j < N; ++j) {
            if (row_sum != 0) {
                f_matrix[j * N + i] = matrix[i * N + j] / row_sum;
            }
            else {
                f_matrix[j * N + i] = 0;
            }
        }
    }
    
    double *c_vector = (double *) malloc(N * sizeof(double));
    for (i = 0; i < N; ++i) {
        c_vector[i] = 1 / N;
    }
    for (i = 0; i < max_iter; ++i) {
        matmul_matrix(f_matrix, c_vector, result, N);

        for (j = 0; j < N; ++j) {
            result[j] = damping * result[j] + (1 - damping) / N;
        }
        double l1_dist = l1_dist_matrix(c_vector, result, N);
        if (l1_dist < eps) {
            break;
        }
        memcpy(c_vector, result, N * sizeof(double));
    }
    free(f_matrix);
    free(c_vector);
}

void naive_ranking(double *matrix, double *ranking, int N) {
    int i, j;
    double sum_rank = 0;
    for (i = 0; i < N; ++i) {
        ranking[i] = 0;
        for (j = 0; j < N; ++j) {
            ranking[i] += matrix[j * N + i];
        }
        sum_rank += ranking[i];
    }
    for (i = 0; i < N; ++i) {
        ranking[i] /= sum_rank;
    }
}

int main(int argc, char *argv[]) {
    const float EDGE_PROB = 0.6;
    double EPS = 1e-5;
    double DAMPING = 0.8;
    int MAX_ITER = 1e5;
    
    int i, j, N;   
    printf("N ");
    scanf("%d", &N);
    printf("\n");        

    double *matrix = (double *) malloc(N * N * sizeof(double));
    generate_matrix(matrix, N, EDGE_PROB);
    
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            printf("%.0lf ", matrix[i * N + j]);
        }
        printf("\n");
    }
    printf("\n");
    
    double *result = (double *) malloc(N * sizeof(double));
    double start_p = clock();    
    pagerank_matrix(matrix, result, N, EPS, DAMPING, MAX_ITER);
    double end_p = clock();
    printf("Time pagerank = %f \n", end_p - start_p);
    
    double *ranking = (double *) malloc(N * sizeof(double));    
    double start_r = clock();    
    naive_ranking(matrix, ranking, N);
    double end_r = clock();
    printf("Time naive_ranking = %f \n", end_r - start_r);
           
    for (i = 0; i < N; ++i) {
        printf("%d pagerank: %lf, ranking: %lf\n", i, result[i], ranking[i]);
    }
    free(matrix);
    free(ranking);
    free(result);
    return 0;
}
