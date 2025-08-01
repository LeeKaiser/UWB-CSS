#include <iostream>
#include <sys/time.h>
using namespace std;

long counter;
struct timeval startTime, endTime;
int elapsed(timeval &startTime, timeval &endTime)
{
    return (int)((endTime.tv_sec - startTime.tv_sec) * 1000000 + endTime.tv_usec - startTime.tv_usec);
}

int Catalan(const int &number);

int main(int argc, char *argv[])
{
    // testing
    int n;
    n = stoi(argv[1]);
    // start counter
    int start = gettimeofday(&startTime, 0);
    cout << "catalan number of " << n << " is: " << Catalan(n) << endl;
    // finish counter
    int end = gettimeofday(&endTime, 0);
    cout << "counter = " << counter << endl;
    cout << "time = " << elapsed(startTime, endTime) << " microseconds" << endl;

    return 0;
}

int Catalan(const int &number)
{
    // base case
    if (number == 0)
    {
        counter++;
        return 1;
    }

    // recursion
    else if (number > 0)
    {
        counter += 1 + 2;
        int ret = 0;
        int n = number - 1; // n+1 = number
        for (int i = 0; i <= n; i++)
        {
            counter += 2 + 1;
            ret += Catalan(i) * Catalan(n - i);
        }
        return ret;
    }
    else
    {
        throw logic_error("negative input");
    }
}