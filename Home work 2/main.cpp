#include "main.h"

int main() {
    vector<vector<int> > mat1 = generate(500);
    vector<vector<int> > mat2 = generate(500);
    
    unsigned int start_time = clock();
    vector<vector<int> > mat = matmul_m_m_i_j_k(mat1, mat2);
    unsigned int end_time = clock();
    cout << "N=500 i j k: " << end_time - start_time << endl;
    
    start_time = clock();
    mat = matmul_m_m_k_i_j(mat1, mat2);
    end_time = clock();
    cout << "N=500 k i j: " << end_time - start_time << endl;
    
    mat1 = generate(512);
    mat2 = generate(512);
    start_time = clock();
    mat = matmul_m_m_i_j_k(mat1, mat2);
    end_time = clock();    //
    cout << "N=512 i j k: " << end_time - start_time << endl;
    
    start_time = clock();
    mat = matmul_m_m_k_i_j(mat1, mat2);
    end_time = clock();
    cout << "N=512 k i j: " << end_time - start_time << endl;
    
    mat1 = generate(1000);
    mat2 = generate(1000);
    start_time = clock();
    mat = matmul_m_m_i_j_k(mat1, mat2);
    end_time = clock();
    cout << "N=1000 i j k: " << end_time - start_time << endl;
    
    start_time = clock();
    mat = matmul_m_m_k_i_j(mat1, mat2);
    end_time = clock();
    cout << "N=1000 k i j: " << end_time - start_time << endl;
    
    mat1 = generate(1024);
    mat2 = generate(1024);
    start_time = clock();
    mat = matmul_m_m_i_j_k(mat1, mat2);
    end_time = clock();
    cout << "N=1024 i j k: " << end_time - start_time << endl;
    
    start_time = clock();
    mat = matmul_m_m_k_i_j(mat1, mat2);
    end_time = clock();
    cout << "N=1024 k i j: " << end_time - start_time << endl;
    
    mat1 = generate(2000);
    mat2 = generate(2000);
    start_time = clock();
    mat = matmul_m_m_i_j_k(mat1, mat2);
    end_time = clock();
    cout << "N=2000 i j k: " << end_time - start_time << endl;
    
    start_time = clock();
    mat = matmul_m_m_k_i_j(mat1, mat2);
    end_time = clock();
    cout << "N=2000 k i j: " << end_time - start_time << endl;
    
    mat1 = generate(2048);
    mat2 = generate(2048);
    start_time = clock();
    mat = matmul_m_m_i_j_k(mat1, mat2);
    end_time = clock();
    cout << "N=2048 i j k: " << end_time - start_time << endl;
    
    start_time = clock();
    mat = matmul_m_m_k_i_j(mat1, mat2);
    end_time = clock();
    cout << "N=2048 k i j: " << end_time - start_time << endl;
    return 0;
}
