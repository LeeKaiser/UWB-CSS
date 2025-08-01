#include "intset.h"
#include <iostream>
using namespace std;

int main() 
{
    IntSet A(9 , 21 , 5);
    cout << A << endl;
    IntSet B;
    cin >> B;
    cout << B << endl;
    IntSet C(A);
    cout << C << endl;
    cout << B + A << endl;
    B += A;
    cout << B << endl;
    IntSet D(29,52,1,23,0);
    cout << A * D << endl;
    cout << B * D << endl;
    D *= B;
    cout << D << endl;
    cout << B.isEmpty() << endl;
    IntSet E(9,21,7);
    cout << A - E << endl;
    cout << E - A << endl;
    C = E - A + B ;
    B -= C;
    cout << C << endl;
    cout << B << endl;
}