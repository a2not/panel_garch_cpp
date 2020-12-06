#pragma once

#include <cassert>
#include <Eigen/Core>

using Eigen::Matrix;

// take vech operation on d*d symmetric matrix and return (d*(d+1) / 2) dimension column std::vector
template<typename T, int d>
Matrix<T, (int)(d * (d + 1)) / 2, 1> vech(Matrix<T, d, d> M) {
    // validate M is symmetric
    for (int i = 0; i < d; ++i) {
        for (int j = 0; j < d; ++j) {
            assert(("vech on non-symmetric matrix.", M(i, j) == M(j, i)));
        }
    }

    int writer = 0;
    Matrix<double, (int)(d * (d + 1)) / 2, 1> res;
    for (int j = 0; j < d; ++j) {
        for (int i = j; i < d; ++i) {
            res(writer++, 0) = M(i, j);
        }
    }
    return res;
}

