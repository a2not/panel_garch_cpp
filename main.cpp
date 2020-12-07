#include <iostream>
#include <vector>
#include <panel_garch/all>

using namespace std;
 
int main() {
    Matrix<double> m(4, 4, 1);
    m[0][0] = m[1][1] = 5;
    m[0][1] = m[1][0] = m[2][2] = m[3][3] = 4;
    m[3][2] = m[2][3] = 2;
    cout << m.eigenvals() << endl;
}

