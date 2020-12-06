#pragma once

#include <cassert>
#include "panel_garch/matrix"

// take vech operation on d*d symmetric matrix and return (d*(d+1) / 2) dimension column std::vector
template<typename T>
Matrix<T> vech(const Matrix<T> &M) {
    // validate M is symmetric
    assert(("vech on non-square matrix", M.r == M.c));
    for (int i = 0; i < M.r; ++i) {
        for (int j = 0; j < M.c; ++j) {
            assert(("vech on non-symmetric matrix.", M[i][j] == M[j][i]));
        }
    }

    int writer = 0;
    Matrix<T> res((M.r * (M.r + 1)) / 2, 1);
    for (int j = 0; j < M.r; ++j) {
        for (int i = j; i < M.c; ++i) {
            res[writer++][0] = M[i][j];
        }
    }
    return res;
}

