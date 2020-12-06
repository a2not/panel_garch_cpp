#pragma once

#include <iostream>
#include <cassert>
#include <vector>

using std::vector;

template <typename T>
struct Matrix {
    int r, c;
    vector<vector<T>> M;

    Matrix(int n, int m) : r(n), c(m){
        M = vector<vector<T>>(n, vector<T>(m));
    }

    Matrix(int n, int m, T val) {
        r = n;
        c = m;
        M = vector<vector<T>>(n, vector<T>(m, val));
    }

    inline const vector<T> &operator[](int k) const { return (M.at(k)); }
    inline vector<T> &operator[](int k) { return (M.at(k)); }

    Matrix<T> &operator+=(const Matrix<T> &B) {
        assert(r == B.r);
        assert(c == B.c);
        for (size_t i = 0; i < r; ++i) {
            for (size_t j = 0; j < c; ++j) {
                (*this)[i][j] += B[i][j];
            }
        }
        return *this;
    }
    Matrix<T> &operator-=(const Matrix<T> &B) {
        assert(r == B.r);
        assert(c == B.c);
        for (size_t i = 0; i < r; ++i) {
            for (size_t j = 0; j < c; ++j) {
                (*this)[i][j] -= B[i][j];
            }
        }
        return *this;
    }
    Matrix<T> &operator*=(const Matrix<T> &B) {
        assert(c == B.r);
        Matrix<T> C(r, B.c, 0);
        for (size_t i = 0; i < r; i++) {
            for (size_t j = 0; j < B.c; j++) {
                for (size_t k = 0; k < c; k++) {
                    C[i][j] = (C[i][j] + (*this)[i][k] * B[k][j]);
                }
            }
        }
        return C;
    }
    Matrix<T> operator+(const Matrix<T> &B) const { return Matrix<T>(*this) += B; }
    Matrix<T> operator-(const Matrix<T> &B) const { return Matrix<T>(*this) -= B; }
    Matrix<T> operator*(const Matrix<T> &B) const { return Matrix<T>(*this) *= B; }

    Matrix<T> t() {
        Matrix<T> res(c, r);
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                res[j][i] = M[i][j];
            }
        }
        return res;
    }

    friend std::ostream &operator<<(std::ostream &os, const Matrix<T> &p) {
        return os << p.M;
    }
};

