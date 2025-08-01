#include <iostream>
using namespace std;

void myswap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main()
{
    int a = 1;
    int b = 2;
    myswap(&a, &b);

    cout << "a = " << a << " , b = " << b << endl;
    return 0;
}