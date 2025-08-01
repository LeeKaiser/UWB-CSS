#include <iostream>
using namespace std;

void PrintBinary(int n)
{
    if (n < 2)
    {
        //base case
        cout << n;
    }
    else
    {
        //recursion
        PrintBinary(n/2);
        cout << n % 2;
    }
}

int Binary(int n)
{
    if (n < 2)
    {
        // base case
        return n;
    }
    else
    {
        // recursion
        return Binary (n/2) + (10 * (n % 2));
    }
}

int main()
{
    cout << "binary of 43: " ;
    PrintBinary(43);
    cout << endl;
}