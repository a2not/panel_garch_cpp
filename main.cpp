#include <iostream>
#include <vector>
#include <panel_garch/all>

using namespace std;
 
int main() {
    Matrix<int> m(2, 3);
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            m[i][j] = i * 3 + (j + 1);
        }
    }
    cout << m << endl;

    Matrix<int> t(3, 2);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 2; ++j) {
            t[i][j] = i * 2 + j + 7;
        }
    }
    cout << t << endl;

    cout << m * t << endl;
}

