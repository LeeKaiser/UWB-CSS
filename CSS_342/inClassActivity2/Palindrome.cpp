#include <iostream>
#include <sys/time.h>
using namespace std;

string StringReversal(const string &in);
bool isPal(const string &in);
int counter;
struct timeval startTime, endTime;
int elapsed(timeval &startTime, timeval &endTime)
{
    return (endTime.tv_sec - startTime.tv_sec) * 1000000 + endTime.tv_sec - startTime.tv_sec;
}

string StringReversal(const string &in)
{
    if (in.size() <= 1)
    {
        counter += 1;
        return in;
    }
    else
    {
        counter += 1;
        return in.back() + StringReversal(in.substr(0, in.size() - 1));
    }
}

bool isPal(const string &in)
{
    string check = StringReversal(in);
    if (check == in)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    string input;
    cout << "put input: ";
    cin >> input;
    int start = gettimeofday(&startTime, 0);
    cout << isPal(input) << endl;
    int end = gettimeofday(&endTime, 0);
    cout << "counter = " << counter << endl;
    cout << "time = " << elapsed(startTime, endTime) << "microseconds" << endl;
}