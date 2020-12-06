#include <iostream>
#include <vector>
#include <panel_garch/all>

using namespace std;
 
int main() {
    /*
     [1, 2, 3]
     [4, 5, 6]
    */
    Matrix<int> m(2, 3);
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            m[i][j] = i * 3 + (j + 1);
        }
    }
    cout << m << endl;
    cout << m.t() << endl;
}

