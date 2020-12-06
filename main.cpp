#include <iostream>
#include <vector>
#include <panel_garch/all>

using namespace std;
 
int main() {
    Matrix<double> m(2, 2);
    m[0][0] = 3;
    m[0][1] = 8;
    m[1][0] = 4;
    m[1][1] = 6;
    cout << m << endl;
    cout << m.det() << endl;
    cout << m << endl;
}

