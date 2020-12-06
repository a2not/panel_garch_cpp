#pragma once

#include <iostream>
#include <cassert>
#include <vector>

using std::vector;

template <typename T>
struct Matrix {
    int r, c;
    vector<vector<T>> M;

    Matrix(int n, int m) : r(n), c(m), M(n, vector<T>(m)){}
    Matrix(int n, int m, T val) : r(n), c(m), M(n, vector<T>(m, val)){}

    inline const vector<T> &operator[](int k) const { return (M.at(k)); }
    inline vector<T> &operator[](int k) { return (M.at(k)); }

    Matrix<T> &operator+=(const Matrix<T> &B) {
        assert(r == B.r);
        assert(c == B.c);
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                (*this)[i][j] += B[i][j];
            }
        }
        return *this;
    }
    Matrix<T> &operator-=(const Matrix<T> &B) {
        assert(r == B.r);
        assert(c == B.c);
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                (*this)[i][j] -= B[i][j];
            }
        }
        return *this;
    }
    Matrix<T> &operator*=(const Matrix<T> &B) {
        assert(c == B.r);
        vector<vector<T>> C(r, vector<T>(B.c, 0));
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < B.c; j++) {
                for (int k = 0; k < c; k++) {
                    C[i][j] += (*this)[i][k] * B[k][j];
                }
            }
        }
        M.swap(C);
        return (*this);
    }
    Matrix<T> operator+(const Matrix<T> &B) const { return Matrix<T>(*this) += B; }
    Matrix<T> operator-(const Matrix<T> &B) const { return Matrix<T>(*this) -= B; }
    Matrix<T> operator*(const Matrix<T> &B) const { return Matrix<T>(*this) *= B; }

    bool operator==(const Matrix<T> &B) const {
        if(r != B.r) return false;
        if(c != B.c) return false;
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if((*this)[i][j] != B[i][j]) return false;
            }
        }
        return true;
    }
    bool operator!=(const Matrix<T> &B) const {
        return !((*this) == B);
    }

    Matrix<T> t() const {
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

