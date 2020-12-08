#include <iostream>
#include <vector>
#include <panel_garch/all>

using namespace std;
 
int main() {
    Matrix<double> vt(2, 1, 0);
    Matrix<double> va(5, 1, 0);
    Matrix<double> vSig(15, 1, 3);
    Matrix<double> vl(4, 1, 0);
    Matrix<double> mX;
    auto mY = DGP(vt, va, vSig, vl, 5, 5, 0, mX);
    cout << mX << endl;
}

