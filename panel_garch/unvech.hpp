#pragma once

#include <cmath>
#include <vector>
#include <cassert>
#include "panel_garch/matrix"

// unvech column vector to a Toeplitz matrix
template <typename T>
Matrix<T> unvech(const Matrix<T>& V) {
    int writer = 0;
    assert(("unvech on matrix.", V.c == 1));
    int d = (-1.0 + sqrt(1 + 8 * V.r)) / 2;

    // validate vector size
    assert(("unvech on infeasible sized vector.", V.r == (d * (d + 1)) / 2));

    Matrix<T> res(d, d);
    for (int j = 0; j < d; ++j) {
        for (int i = j; i < d; ++i) {
            res[i][j] = V[writer][0];
            res[j][i] = V[writer][0];
            writer++;
        }
    }
    return res;
}

