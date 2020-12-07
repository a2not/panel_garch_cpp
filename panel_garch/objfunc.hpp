#pragma once

#include <cassert>
#include <cmath>
#include "panel_garch/matrix"

template <typename T>
double objective_function(int iN, int iT, const Matrix<T> &vLambda, const Matrix<T> &mU, const Matrix<T> &mSig) {
    assert(("vLambda not size (4, 1)", vLambda.r == 4 && vLambda.c == 1));
    assert(("mU not size (iT, iN)", mU.r == iT && mU.c == iN));
    assert(("mSig not size (iN, iN)", mSig.r == iN && mSig.c == iN));
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

    Matrix<T> mK = mSig - mC * mSig * mC - mD * mSig * mD;

    Matrix<T> mH = mSig;

    double score = 0;
    for (int t = 0; t < iT; ++t) {
        Matrix<T> vUt(mU[t]);

        score -= log(mH.det());
        score -= vUt.t() * mH.inv() * vUt;
        
        mH = mK + mC * vUt * vUt.t() * mC + mD * mH * mD;
    }

    score -= (double)iN * iT * log(PI * 2.0);
    score *= 0.5;

    std::cout << "obj func runs successfully: f() = " << score << std::endl;
    return score;
}
