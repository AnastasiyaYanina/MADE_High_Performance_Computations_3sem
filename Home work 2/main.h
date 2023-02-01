#include <vector>
#include <random>
#include <iostream>
#include <ctime>

using namespace std;

vector<vector<int>> generate(int n);
vector<vector<int>>  matmul_m_m_i_j_k(vector<vector<int> > A, vector<vector<int> > B);
vector<vector<int>>  matmul_m_m_k_i_j(vector<vector<int> > A, vector<vector<int> > B);
