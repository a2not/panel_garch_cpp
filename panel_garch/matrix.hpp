#pragma once

#include <iostream>
#include <cassert>
#include <cmath>
#include <vector>

using std::vector;

const double eps = 1e-9;
const double PI = acos(-1);

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
        Matrix<T> A = Matrix<T>(*this);
        // elimination steps
        for (int i = 0; i < c; ++i) {
            double coef = (double)1.0 / A[i][i];
            for (int j = 0; j < c; ++j) {
                A[i][j] *= coef;
                res[i][j] *= coef;
            }
            for (int j = 0; j < c; ++j) {
                if(i == j) continue;
                double coef = A[j][i];
                for (int k = 0; k < c; ++k) {
                    A[j][k] -= A[i][k] * coef;
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
        Matrix<T> A = Matrix<T>(*this);
        double res = 1;
        for (int i = 0; i < c; ++i) {
            int k = i;
            for (int j = i+1; j < c; ++j) {
                if(abs(A[j][i]) > abs(A[k][i])) {
                    k = j;
                }
            }
            if(abs(A[k][i]) < eps) {
                return 0;
            }
            swap(A[i], A[k]);
            if(i != k) res = -res;
            res *= A[i][i];
            for (int j = i+1; j < c; ++j) {
                A[i][j] /= A[i][i];
            }
            for (int j = 0; j < c; ++j) {
                if(j != i && abs(A[j][i]) > eps) {
                    for (int k = i+1; k < c; ++k) {
                        A[j][k] -= A[i][k] * A[j][i];
                    }
                }
            }
        }
        return res;
    }

    Matrix<T> eigenvals() const {
        assert(c == r);
        // Jacobi eigenvalue method
        Matrix<T> A = Matrix<T>(*this);
        Matrix<T> B(c, c, 0);
        for (int i = 0; i < c; ++i) B[i][i] = 1;

        for (int k = 0; k < 100; ++k) {
            // find maximum value
            int p = 0, q = 0;
            T maxval = 0;
            for (int i = 0; i < c; ++i) {
                for (int j = i+1; j < c; ++j) {
                    if (maxval < abs(A[i][j])) {
                        maxval = abs(A[i][j]);
                        p = i, q = j;
                    }
                }
            }

            // find θ
            double t = 0;
            if (abs(A[p][p] - A[q][q]) < eps) {
                // iff a_{pp} ＝ a_{qq}: θ = π/4
                t = PI / 4.0;
                if (A[p][p] < 0) t = -t;
            } else {
                // a_{pp} ≠ a_{qq}
                t = atan(2.0 * A[p][q] / (A[p][p] - A[q][q])) / 2.0;
            }

            // Make matrix P with θ, then A = P^t × A × P
            double cosine = cos(t);
            double sine = sin(t);
            // P^t × A
            double t1 = 0, t2 = 0;
            for (int i = 0; i < c; ++i) {
                t1      =  A[p][i] * cosine + A[q][i] * sine;
                t2 = -A[p][i] * sine + A[q][i] * cosine;
                A[p][i] = t1;
                A[q][i] = t2;
                // 固有ベクトル
                t1      =  B[p][i] * cosine + B[q][i] * sine;
                t2      = -B[p][i] * sine + B[q][i] * cosine;
                B[p][i] = t1;
                B[q][i] = t2;
            }
            // A × P
            for (int i = 0; i < c; ++i) {
                t1      =  A[i][p] * cosine + A[i][q] * sine;
                t2      = -A[i][p] * sine + A[i][q] * cosine;
                A[i][p] = t1;
                A[i][q] = t2;
            }

            // 収束判定
            if (maxval < eps) break;
        }

        Matrix<T> res(c, 1, 0);
        for (int i = 0; i < c; ++i) {
            res[i][0] = A[i][i];
        }
        return res;
    }

    double spectral_radius() const {
        auto ev = (*this).eigenvals();
        double res = 0;
        for (int i = 0; i < ev.r; ++i) {
            if(res < abs(ev[i][0])) res = abs(ev[i][0]);
        }
        return res;
    }

    friend std::ostream &operator<<(std::ostream &os, const Matrix<T> &p) {
        return os << p.M;
    }
};

