#pragma once

#include <cassert>
#include <random>
#include "panel_garch/matrix"
#include "panel_garch/unvech"

template <typename T>
Matrix<T> DGP(const Matrix<T> &vTheta, const Matrix<T> &vAlpha,
        const Matrix<T> &vSigma, const Matrix<T> &vLambda,
        int iT, int iN, int iI, 
        Matrix<T> &mX) {
    assert(("vTheta not size (2, 1)", vTheta.r == 2 && vTheta.c == 1));
    T phi = vTheta[0][0];
    T beta = vTheta[1][0];
    assert(("vAlpha not size (iN, 1)", vAlpha.r == iN && vAlpha.c == 1));
    assert(("vLambda not size (4, 1)", vLambda.r == 4 && vLambda.c == 1));
    T gam = vLambda[0][0];
    T rho = vLambda[1][0];
    T varphi = vLambda[2][0];
    T eta = vLambda[3][0];
    assert(("vSigma not size (iN * (iN + 1) / 2, 1)", vSigma.r == iN * (iN + 1) / 2 && vSigma.c == 1));
    auto mSig = unvech(vSigma);
    assert(("mSig not size (iN, iN)", mSig.r == iN && mSig.c == iN));

    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    // Matrix with size (iT * iN), 
    // elements are generated with Uniform dist over [0, 1)
    if (!(mX.r == iT && mX.c == iN)) {
        mX = Matrix<T>(iT, iN, 0);
        for (int i = 0; i < iT; ++i) {
            for (int j = 0; j < iN; ++j) {
                mX[i][j] = distribution(generator);
            }
        }
    }

    // Definition (13)
    Matrix<T> mC(iN, iN, rho), mD(iN, iN, eta);
    for (int i = 0; i < iN; ++i) {
        mC[i][i] += gam - rho;
        mD[i][i] += varphi - eta;
    }

    Matrix<T> mK = mSig - mC * mSig * mC - mD * mSig * mD;

    auto vMy = (vAlpha + 0.5) * (1.0 / (1.0 - phi));
    auto mSy = (mSig + (1.0 / 12.0)) * (1.0 / (1.0 - phi * phi));

    Matrix<T> mY(iT, iN, 0);

    auto mH = mSig;

    for (int t = 0; t < iT; ++t) {
        Matrix<T> vRand(iN, 1, 0);
        for (int i = 0; i < iN; ++i) {
            vRand[i][0] = distribution(generator);
        }
        auto vU = sqrtm(mH) * vRand;

        for (int i = 0; i < iN; ++i) {
            if(t == 0) mY[0][i] = vU[i] + vMy[i];
            else {
                mY[t][i] = vAlpha[i] + (phi * mY[t-1][i]) + (beta * mX[t][i]) + vU[i];
            }
        }

        mH = mK + mC * vU * vU.t() * mC + mD * mH * mD;
    }

    return mY;
}

