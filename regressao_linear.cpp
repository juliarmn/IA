#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Regressao {
    double a;
    double b;
public:
    Regressao(vector<int> y, vector<int> x);
};

double** criar_matriz_A(vector<int>& x) {
    double** matriz_A = new double*[2];
    for (int i = 0; i < 2; ++i) {
        matriz_A[i] = new double[2];
    }

    matriz_A[0][0] = x.size();
    matriz_A[0][1] = 0;
    matriz_A[1][0] = 0;
    matriz_A[1][1] = 0;

    for (int i = 0; i < x.size(); ++i) {
        matriz_A[0][1] += x[i];
        matriz_A[1][0] += x[i];
        matriz_A[1][1] += x[i] * x[i];
    }
    return matriz_A;
}

double* criar_vetor_B(vector<int>& y, vector<int>& x) {
    double *vetor_B = new double[2];
    vetor_B[0] = 0;
    vetor_B[1] = 0;
    for (int i = 0; i < y.size(); i++) {
        vetor_B[0] += y[i];
        vetor_B[1] += y[i] * x[i];
    }
    return vetor_B;
}

double* crammer(double **matriz_A, double *vetor_B) {
    double *vet_solucao = new double[2];
    double det_A;
    det_A = matriz_A[0][0] * matriz_A[1][1] - matriz_A[0][1] * matriz_A[1][0];
    double det_x = vetor_B[0] * matriz_A[1][1] - vetor_B[1] * matriz_A[1][0];
    vet_solucao[0] = det_x / det_A;
    double det_y = matriz_A[0][0] * vetor_B[1] - matriz_A[0][1] * vetor_B[0];
    vet_solucao[1] = det_y / det_A;
    return vet_solucao;
}

Regressao::Regressao(vector<int> y, vector<int> x) {
    double **matriz_A = criar_matriz_A(x);
    double *vetor_B = criar_vetor_B(y, x);
    double *solucao = crammer(matriz_A, vetor_B);

    a = solucao[1];
    b = solucao[0];

    cout << "A solucao da regressao: " << a << "x + " << b << endl;

    delete[] solucao;
    for (int i = 0; i < 2; ++i) {
        delete[] matriz_A[i];
    }
    delete[] matriz_A;
    delete[] vetor_B;
}

int main () {
    vector<int> x;
    x.push_back(-2);
    x.push_back(-1);
    x.push_back(0);
    x.push_back(1);
    x.push_back(2);
    x.push_back(3);

    vector<int> y;
    y.push_back(-7);
    y.push_back(-5);
    y.push_back(-1);
    y.push_back(1);
    y.push_back(3);
    y.push_back(7);
    Regressao Regressao(y, x);
    return 0;
}
