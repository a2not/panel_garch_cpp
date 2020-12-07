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
    Matrix(const vector<T>& v) {
        r = v.size();
        c = 1;
        M = vector<vector<T>>(r, vector<T>(1));
        for (int i = 0; i < r; ++i) {
            M[i][0] = v[i];
        }
        assert(M.size() == r && M[0].size() == c);
    }

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
    Matrix<T> &operator*=(const T &coef) {
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                (*this)[i][j] *= coef;
            }
        }
        return (*this);
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
    Matrix<T> operator*(const T &coef) const { return Matrix<T>(*this) *= coef; }
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

    Matrix<T> inv() const {
        assert(c == r);
        // Gaussian elimination; O(n ^ 3)
        // initialize resulting matrix as Identity matrix
        Matrix<T> res(c, c, 0);
        for (int i = 0; i < c; ++i) {
            res[i][i] = 1;
        }
        Matrix<T> tmp = Matrix<T>(*this);
        // elimination steps
        for (int i = 0; i < c; ++i) {
            double coef = (double)1.0 / tmp[i][i];
            for (int j = 0; j < c; ++j) {
                tmp[i][j] *= coef;
                res[i][j] *= coef;
            }
            for (int j = 0; j < c; ++j) {
                if(i == j) continue;
                double coef = tmp[j][i];
                for (int k = 0; k < c; ++k) {
                    tmp[j][k] -= tmp[i][k] * coef;
                    res[j][k] -= res[i][k] * coef;
                }
            }
        }
        return res;
    }

    double det() const {
        // if the matrix is not square, vectors must be linearly dependent
        if(c != r) return 0;
        
        // Gaussian elimination; O(n ^ 3)
        Matrix<T> tmp = Matrix<T>(*this);
        const double eps = 1e-9;
        double res = 1;
        for (int i = 0; i < c; ++i) {
            int k = i;
            for (int j = i+1; j < c; ++j) {
                if(abs(tmp[j][i]) > abs(tmp[k][i])) {
                    k = j;
                }
            }
            if(abs(tmp[k][i]) < eps) {
                return 0;
            }
            swap(tmp[i], tmp[k]);
            if(i != k) res = -res;
            res *= tmp[i][i];
            for (int j = i+1; j < c; ++j) {
                tmp[i][j] /= tmp[i][i];
            }
            for (int j = 0; j < c; ++j) {
                if(j != i && abs(tmp[j][i]) > eps) {
                    for (int k = i+1; k < c; ++k) {
                        tmp[j][k] -= tmp[i][k] * tmp[j][i];
                    }
                }
            }
        }
        return res;
    }

    friend std::ostream &operator<<(std::ostream &os, const Matrix<T> &p) {
        return os << p.M;
    }
};

