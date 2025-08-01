#include <iostream>
using namespace std;

string const DIGIT_ARRAY = "123456789ABCDEF";

void PrintHexa(int n)
{
    if (n < 16)
    {
        // base case
        cout << DIGIT_ARRAY[n];
    }
    else
    {
        // recursion
        PrintHexa(n / 16);
        PrintHexa(n % 16);
    }
}

int main()
{
    cout << "Hexadecimal of 9999999: ";
    PrintHexa(9999999);
    cout << endl;
}