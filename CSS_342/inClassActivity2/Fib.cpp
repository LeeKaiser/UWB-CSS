#include <iostream>
#include <sys/time.h>
using namespace std;

int Fib(const int n);
long counter;
struct timeval startTime, endTime;
int elapsed(timeval &startTime, timeval &endTime)
{
    return (endTime.tv_sec - startTime.tv_sec) * 1000000 + endTime.tv_sec - startTime.tv_sec;
}

int main(int argc, char *argv[])
{
    cout << "argc = " << argc << endl;
    cout << "argv[0] = " << argv[0] << endl;
    cout << "argv[1] = " << argv[1] << endl;

    int n;
    n = stoi(argv[1]);
    // cout << "specify a positive int";
    // cin >> n;
    int start = gettimeofday(&startTime, 0);
    cout << "fib(" << n << ")=" << Fib(n) << endl;

    int end = gettimeofday(&endTime, 0);
    cout << "counter =" << counter << endl;
    cout << "time = " << elapsed(startTime, endTime) << "microseconds" << endl;
    return 0;
}

int Fib(const int n)
{
    if (n <= 1)
    {
        return n;
    }
    else
    {
        counter = counter + 3;
        return Fib(n - 1) + Fib(n - 2);
    }
}