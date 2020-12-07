#pragma once

#include <cassert>
#include "panel_garch/matrix"

template <typename T>
Matrix<T> kronecker_product(const Matrix<T> &A, const Matrix<T> &B) {
    int m = A.r, n = A.c;
    int p = B.r, q = B.c;

    Matrix<T> C(m * p, n * q, 0);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int s = 0; s < p; ++s) {
                for (int t = 0; t < q; ++t) {
                    int y = i * p + s;
                    int x = j * q + t;
                    C[y][x] = A[i][j] * B[s][t];
                }
            }
        }
    }
    return C;
}

template <typename T>
double spectral_radius_of_kroneckers(int iN, const Matrix<T> &vLambda) {
    assert(("vLambda not size (4, 1)", vLambda.r == 4 && vLambda.c == 1));
    T gam = vLambda[0][0];
    T rho = vLambda[1][0];
    T varphi = vLambda[2][0];
    T eta = vLambda[3][0];
    
    // Definition (13)
    Matrix<T> mC(iN, iN, rho), mD(iN, iN, eta);
    for (int i = 0; i < iN; ++i) {
        mC[i][i] += gam - rho;
        mD[i][i] += varphi - eta;
    }

    double res = 0;
    Matrix<T> kron = kronecker_product(mC, mC);
    kron += kronecker_product(mD, mD);

    return res;
}

