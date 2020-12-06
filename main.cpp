#include <iostream>
#include <vector>
#include <panel_garch/all>

using namespace std;
 
int main() {
    Matrix<int> m(2, 2);
    m[0][0] = 1;
    m[1][0] = 2;
    m[0][1] = 2;
    m[1][1] = 3;
    Matrix<int> t(3, 1);
    t[0][0] = 1;
    t[1][0] = 2;
    t[2][0] = 3;

    if(!(m != unvech(t))) {
        cout << "unveched successfully." << endl;
    }

    if(t == vech(m)) {
        cout << "veched successfully." << endl;
    }

    cout << Matrix<int>(2, 2, 18) << endl;
}

