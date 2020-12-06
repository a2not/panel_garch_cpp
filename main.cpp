#include <iostream>
#include <vector>
#include <panel_garch/all>

using namespace std;
 
int main() {
    Matrix<double> m(2, 2);
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            m[i][j] = i * 2 + (j + 1);
        }
    }
    cout << m << endl;
    cout << m.inv() << endl;
    cout << m * m.inv() << endl;
}

