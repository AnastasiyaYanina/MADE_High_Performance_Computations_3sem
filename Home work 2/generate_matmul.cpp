#include "main.h"

vector<vector<int> > generate(int n) {
    vector<vector<int> > mat(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            mat[i][j] = (rand() % 2);
        }
    }
    return mat;
}

vector<vector<int> >  matmul_m_m_i_j_k(vector<vector<int> > A, vector<vector<int> > B) {
    vector<vector<int> > C(A.size(), vector<int>(B.size()));

    for (int i = 0; i < A.size(); ++i) {
        for (int j = 0; j < B.size(); ++j) {
            for (int k = 0; k < A.size(); ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

vector<vector<int> > matmul_m_m_k_i_j(vector<vector<int> > A, vector<vector<int> > B) {
    vector<vector<int> > C(A.size(), vector<int>(B.size()));

    for (int k = 0; k < A.size(); ++k) {
        for (int i = 0; i < A.size(); ++i) {
            for (int j = 0; j < A.size(); ++j) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}
