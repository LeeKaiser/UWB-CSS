#include <iostream>
using namespace std;

void f()
{
    int N = 20;
    // allocate array on heap
    int *z = new int[N];

    for (int i = 0; i < N; i++)
    {
        z[i] = i;
    }

    cout << "z = " << z << endl;

    for (int i = 0; i < N; i++)
    {
        cout << &z[i] << endl;
    }

    delete[] z;     //dealocate memory

}

int* f1(int N)
{
    int *z = new int[N];

    for (int i = 0; i < N; i++)
    {
        z[i] = i;
    }
    return z;
}

int main()
{
    int* p = f1(5);
    for (int i = 0; i < 5; i++)
    {
        cout << *(p+i) << endl;
    }
    delete[] p;
    return 0;
}