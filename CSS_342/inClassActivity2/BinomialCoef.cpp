#include <iostream>
using namespace std;

int BinomialCoef(int k, int n)
{
    // base case
    if (k == 0 || k == n)
    {
        return 1;
    }
    else
    {
        return BinomialCoef(k - 1, n - 1) + BinomialCoef(k - 1, n);
    }
}

int main()
{
    cout << "binomial coef (2,4) = " << BinomialCoef(2, 4) << endl;

    return 0;
}