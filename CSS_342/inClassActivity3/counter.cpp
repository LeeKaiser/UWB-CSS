#include <iostream>
using namespace std;

int counter;

int main()
{
    int n = 10;
    int sum;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            for (int k = 1; k <= 5; k++)
            {
                sum ++;
                counter = counter + 1;
            }
        }
    }

    cout << "counter = " << counter << endl;
    return 0;
}