#include <iostream>
using namespace std;

int pow(int n, int a)
{
    if (a == 0)
    {
        return 1;
    }
    else
    {
        return n * pow(n, a - 1);
    }
}

int main()
{
    cout << "pow(4,4) = " << pow(4, 4) << endl;

    return 0;
}