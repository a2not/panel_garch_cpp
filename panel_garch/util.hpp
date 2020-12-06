#pragma once

#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

struct IoSetup {
    IoSetup() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
        cerr << fixed << setprecision(10);
    }
} iosetup;
template< typename T1, typename T2 >
ostream &operator<<(ostream &os, const pair< T1, T2 >& p) {
    os << p.first << " " << p.second;
    return os;
}
template< typename T1, typename T2 >
istream &operator>>(istream &is, pair< T1, T2 > &p) {
    is >> p.first >> p.second;
    return is;
}
template< typename T >
ostream &operator<<(ostream &os, const vector< T > &v) {
    cout << "[";
    for(int i = 0; i < (int)v.size(); i++) {
        os << v[i] << (i + 1 != (int)v.size() ? ", " : "");
    }
    cout << "]";
    return os;
}
template< typename T >
ostream &operator<<(ostream &os, const vector< vector< T > > &v) {
    cout << "[";
    for(int i = 0; i < (int)v.size(); i++) {
        if(i > 0) cout << " ";
        cout << v[i];
        cout << (i + 1 != (int)v.size() ? ",\n" : "");
    }
    cout << "]";
    return os;
}
template< typename T >
istream &operator>>(istream &is, vector< T > &v) {
    for(T &in : v) is >> in;
    return is;
}

