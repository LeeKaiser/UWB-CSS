#include <iostream>
#include <sys/time.h>
using namespace std;

int counter;
struct timeval startTime, endTime;
int elapsed(timeval &startTime, timeval &endTime)
{
    return (endTime.tv_sec - startTime.tv_sec) * 1000000 + endTime.tv_sec - startTime.tv_sec;
}

void PrintStringReversal(const string &in)
{
    if (in.size() <= 1)
    {
        counter += 1;
        cout << in << endl;
    }
    else
    {
        counter += 1;
        cout << in.back();
        PrintStringReversal(in.substr(0, in.size() - 1));
    }
}

int main()
{
    string input;
    cout << "put input: ";
    cin >> input;
    int start = gettimeofday(&startTime, 0);
    PrintStringReversal(input);
    int end = gettimeofday(&endTime, 0);
    cout << "counter = " << counter << endl;
    cout << "time = " << elapsed(startTime, endTime) << "microseconds" << endl;
}